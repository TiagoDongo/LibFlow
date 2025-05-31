#include"utils.h"
#include"cJSON.h"
#include"loan.h"

void make_loan(Loan *loan_head, Book book_head, User user_head){
    int bookID = validated_int_input("Digite o ID do livro a ser emprestado: ");
    int userID = validated_int_input("Digite o ID do usuario: ");
    
    Book book_ptr = (Book)find_entity(book_head, bookID, TYPE_BOOK);
    if (book_ptr == NULL) {
        printf("Livro com ID %d não encontrado.\n", bookID);
        return;
    }

    User user_ptr = (User)find_entity(user_head, userID, TYPE_USER);
    if (user_ptr == NULL) {
        printf("Usuário com ID %d não encontrado.\n", userID);
        return;
    }

    if (book_ptr->book_available == 0){
        printf("Livro '%s' esta indisponivel para emprestimo.\n", book_ptr->book_name);
        return;
    }
    
    Loan new_loan = (Loan)malloc(sizeof(struct loan));
    if (new_loan == NULL){
        puts("Erro de alocacao");
        return;
    }

    new_loan->loan_id = id_generator(*loan_head, TYPE_LOAN);
    new_loan->book_id = bookID;
    new_loan->user_id = userID;
    new_loan->returned = 0;

    time_t time_now = time(NULL);
    struct tm *tm_info = localtime(&time_now);
    strftime(new_loan->loan_date, sizeof(new_loan->loan_date), "%Y-%m-%d", tm_info);

    new_loan->next = *loan_head;
    *loan_head = new_loan;

    book_ptr->book_available = 0;

    printf("SUCESSO: empréstimo criado!\n");
}


void return_book(Loan *loan_head, Book book_head){
    int loanId = validated_int_input("Digite o Id do emprestimo para devolucao: ");

    Loan current = *loan_head;

    while (current != NULL) {
        if (current->loan_id == loanId) {
            if (current->returned == 1) {
                printf("ATENÇÃO: Empréstimo ID %d já foi devolvido.\n", loanId);
                return;
            }

            Book book_ptr = (Book)find_entity(book_head, current->book_id, TYPE_BOOK);
            if (book_ptr != NULL) {
                book_ptr->book_available = 1;
                current->returned = 1;

                printf("[INFO] SUCESSO: livro \"%s\" (ID %d) devolvido.\n", book_ptr->book_name, book_ptr->book_id);
            } else {
                printf("ATENÇÃO: Livro do empréstimo ID %d não encontrado na base de dados.\n", loanId);
                printf("[INFO] Empréstimo marcado como devolvido mesmo sem atualizar livro.\n");
                current->returned = 1;
            }
            return;
        }
        current = current->next;
    }
    printf("ERRO: emprestimo com ID %d nao encontrado.\n", loanId);
}

void save_loans(Loan loan_head){
    char filename[100];

    if (loan_head == NULL){
        puts("ERRO: nenhum emprestimo registado no sistema");
        return;
    }

    if (list_loaded && strlen(last_loaded_file) > 0){
        printf("Dejesa sobescrever o ficheiro carregado anteriormente (%s) (s/n): ", last_loaded_file);
        char resposta;
        scanf("%c", &resposta);

        if (resposta == 's' || resposta == 'S'){
            strcpy(filename, last_loaded_file);
        }else{
            generate_json_filename(filename, TYPE_LOAN);
        }
    }else{
        generate_json_filename(filename, TYPE_LOAN);
    }
    
    FILE *file = fopen(filename, "w");
    if (file == NULL){
        printf("ERRO: nao foi possivel abrir o ficheiro JSON.\n");
        return;
    }

    cJSON *loan_array = cJSON_CreateArray();

    while (loan_head != NULL){
        cJSON *json_loan = cJSON_CreateObject();

        cJSON_AddNumberToObject(json_loan, "loan_id", loan_head->loan_id);
        cJSON_AddNumberToObject(json_loan, "book_id", loan_head->book_id);
        cJSON_AddNumberToObject(json_loan, "user_id", loan_head->user_id);
        cJSON_AddStringToObject(json_loan, "loan_date", loan_head->loan_date);
        cJSON_AddBoolToObject(json_loan, "returned", loan_head->returned);

        cJSON_AddItemToArray(loan_array, json_loan);
        loan_head = loan_head->next;
    }
    char *loan_string = cJSON_Print(loan_array);
    fprintf(file, "%s", loan_string);
    fclose(file);

    strcpy(last_loaded_file, filename);

    cJSON_Delete(loan_array);
    free(loan_string);
}

void load_loans(Loan *loan_head){
    if (*loan_head != NULL && list_loaded == 0){
        char option;
        printf("AVISO: Existe uma lista atual que ainda nao foi salva.\n");
        printf("Deseja salva-la antes de carregar uma nova? (s/n): ");
        scanf("%c", &option);
        while (getchar() != '\n');
        
        if (option == 's' || option == 'S'){
            save_loans(*loan_head);
            list_loaded = 1;
        }
    }

    struct dirent *entry;
    DIR *dir = opendir("data/loans");
    if (dir == NULL){
        printf("ERRO: nao e possivel abrir a pasta 'data/loans'.\n");
        return;
    }

    puts("Listas de Emprestimos disponiveis:");
    char files[50][100];
    int count = 0;

    while ((entry = readdir(dir)) != NULL){
        if (strstr(entry->d_name, ".json")){
            printf("[%d] %s\n", count+1, entry->d_name);
            strncpy(files[count], entry->d_name, sizeof(files[count]) - 1);
            files[count][sizeof(files[count]) - 1] = '\0';
            count++;
        }
    }
    closedir(dir);

    if (count == 0){
        printf("ERRO: diretorio vazio.\n");
        return;
    }

    int choice = validated_int_input("Escolha uma lista a ser carregada: ");

    if (choice < 1 || choice > count){
        printf("ERRO: opcao invalida.\n");
        return;
    }

    char filepath[150];
    sprintf(filepath, "data/loans/%s", files[choice - 1]);

    FILE *file = fopen(filepath, "r");
    if (file == NULL){
        printf("ERRO: nao e possivel abrir '%s'\n", filepath);
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    char *buffer = malloc(fileSize + 1);
    if (!buffer){
        printf("ERRO: falha ao alocar memoria para leitura do JSON\n");
        fclose(file);
        return;
    }

    fread(buffer, 1, fileSize, file);
    buffer[fileSize] = '\0';
    fclose(file);

    cJSON *json = cJSON_Parse(buffer);
    free(buffer);

    if (!json){
        printf("ERRO: falha ao analisar o JSON.\n");
        return;
    }

    if (!cJSON_IsArray(json)){
        printf("ERRO: o JSON nao e um array.\n");
        cJSON_Delete(json);
        return;
    }

    Loan temp;
    while (*loan_head) {
        temp = *loan_head;
        *loan_head = (*loan_head)->next;
        free(temp);
    }
    
    int max_id = 0;
    for (int i = 0; i < cJSON_GetArraySize(json); i++){
        cJSON *jsonOBJ = cJSON_GetArrayItem(json, i);
        Loan new_loan = malloc(sizeof(struct loan));
        if (!new_loan){
            printf("ERRO: Falha ao alocar memória para um emprestimo.\n");
            cJSON_Delete(json);
            return;
        }

        new_loan->loan_id = cJSON_GetObjectItem(jsonOBJ, "loan_id")->valueint;
        new_loan->book_id = cJSON_GetObjectItem(jsonOBJ, "book_id")->valueint;
        new_loan->user_id = cJSON_GetObjectItem(jsonOBJ, "user_id")->valueint;

        const char *loan_date = cJSON_GetObjectItem(jsonOBJ, "loan_date")->valuestring;
        strncpy(new_loan->loan_date, loan_date, sizeof(new_loan->loan_date));
        new_loan->loan_date[sizeof(new_loan->loan_date) - 1] = '\0';

        cJSON *returned_item = cJSON_GetObjectItem(jsonOBJ, "returned");
        new_loan->returned = cJSON_IsTrue(returned_item) ? 1 : 0;

        new_loan->next = *loan_head;
        *loan_head = new_loan;

        if (new_loan->loan_id > max_id){
            max_id = new_loan->loan_id;
        }
    }
    
    cJSON_Delete(json);
    list_loaded = 1;
    strncpy(last_loaded_file, filepath, sizeof(last_loaded_file));
    last_loaded_file[sizeof(last_loaded_file) - 1 ] = '\0';

    printf("SUCESSO: %d empréstimo(s) carregado(s) de '%s'.\n", cJSON_GetArraySize(json), filepath);
}