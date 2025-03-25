#include"../../src/library.h"
#include"../../src/cJSON.h"
#include"../../src/utils.h"

/**
 * @brief Registra um novo livro na biblioteca
 * @param book_head Ponteiro paro o ponteiro do primeiro livro da lista encadeada
 */
void regist_book(book *book_head){
    book new_book = (book)malloc(sizeof(struct library));
    if (new_book == NULL){
        printf("ERRO: alocacao falhou.\n");
        return;
    }
    
    //book id
    new_book->book_id = book_id_generator(*book_head);

    //book name
    printf("Digite o nome do livro: ");
    scanf(" %99[^\n]", new_book->book_name);

    //book autor
    printf("Digite o nome do autor do livro: ");
    scanf(" %99[^\n]", new_book->book_autor);

    //book edition
    printf("Digite a edicao do livro: ");
    scanf("%d", &new_book->book_edition);

    //book avaliable
    new_book->book_available = 1;

    new_book->next = NULL;

    if (*book_head == NULL){
        *book_head = new_book;
    }
    else{
        book current = *book_head;
        while (current->next != NULL){
            current = current->next;
        }
        current->next = new_book;
    }
    
    printf("\nSUCESSO: livro | %s | foi adicionado a lista.\n", new_book->book_name);
}

/**
 * @brief Remove um  livro da biblioteca com base no ID fornecido
 * @param book_head Ponteiro paro o ponteiro do primeiro livro da lista encadeada
 */
void delete_book(book *book_head){
    int bookID;
    book current_book = *book_head;
    book previous_book = NULL;

    if (*book_head == NULL){
        printf("ERRO: biblioteca vazia.\n");
        return;
    }

    printf("\nDigite o ID do livro a ser removido: ");
    scanf("%d",&bookID);

    while (current_book != NULL){
        if (current_book->book_id == bookID){
            if (previous_book == NULL){
                *book_head = current_book->next;
            }
            else{
                previous_book->next = current_book->next;
            }
            
            printf("\nSUCESSO: livro | %s | foi removido da lista.\n", current_book->book_name);
            free(current_book);
            return;
        }
        previous_book = current_book;
        current_book = current_book->next;
    }
    printf("ERRO: livro nao encontrado ou ja removido.\n");    
}

/**
 * @brief Procura um livro na biblioteca pelo ID e exibe suas informações
 * @param book_head Ponteiro para o primeiro livro da lista encadeada.
 */
void search_book(book book_head){
    int bookID;

    if (book_head == NULL){//verifica se a biblioteca está vazia
        printf("\nERRO: biblioteca vazia\n");
        return;
    }

    printf("\nDigite o ID do livro que esta a procura: "); //pede o ID do livro a ser procurado
    scanf("%d", &bookID);

    while (book_head != NULL){//percorre a lista
        if (book_head->book_id == bookID){//caso encontre o livro imprime os dados do livro
            printf("\nLivro encontrado:\n");
            printf("ID: %d | Titulo: %s | Autor: %s | Edicao: %d | Disponivel: %s\n\n",
            book_head->book_id, book_head->book_name, book_head->book_autor, book_head->book_edition, (book_head->book_available == 1) ? "Sim" : "Nao");
            return;
        }
        book_head = book_head->next;//avança para o próximo livro
    }
    printf("\nERRO: Livro nao encontrado ou foi removido.\n");
}

/**
 * @brief Lista todos os livros armazenados na biblioteca.
 * @param book_head Ponteiro para o primeiro livro da lista encadeada.
 */
void list_books(book book_head){
    if (book_head == NULL){
        printf("\nERRO: biblioteca vazia\n");
        return;
    }

    printf("\n--------------------- LISTA DE LIVROS ---------------------\n");
    printf("  ID    |   Titulo              |   Autor          |   Edicao   |   Disponivel  \n");
    printf("-----------------------------------------------------------------------------------------\n");

    book current = book_head;
    while (current != NULL){
        printf("  %-6d|  %-20s|  %-15s|  %-8d|  %-12s\n",
            current->book_id, current->book_name, current->book_autor, current->book_edition, 
            (current->book_available == 1) ? "Sim" : "Nao");//imprime os dados do livro

        current = current->next;//avança para o próximo livro
    }
}

/**
 * @brief Salva a lista livros num ficheiro JSON
 * @param book_head Ponteiro para o primeiro livro da lista encadeada.
 */
void save_list_books(book book_head){
    if (book_head == NULL){
        printf("\nERRO: biblioteca vazia\n");
        return;
    }

    //gera o nome do .json
    char file_name[150];
    generate_book_filename(file_name);
    
    FILE *file = fopen(file_name, "w");
    if (file == NULL){//verificação da abertura do ficheiro
        printf("ERRO: nao foi possivel abrir o JSON.\n");
        return;
    }

    cJSON *json_array = cJSON_CreateArray(); //cria um vetor para guardar objetos/livros
    book current = book_head;

    while (current != NULL){
        cJSON *json_book = cJSON_CreateObject(); //cria um objeto para armazenar dados de um livro
        cJSON_AddNumberToObject(json_book, "book_id", current->book_id); //id do livro
        cJSON_AddStringToObject(json_book, "book_name", current->book_name); //nome do livro
        cJSON_AddStringToObject(json_book, "book_autor", current->book_autor); //autor do livro
        cJSON_AddNumberToObject(json_book, "book_edition", current->book_edition);//edição do livro
        cJSON_AddStringToObject(json_book, "book_available", (current->book_available) ? "Sim" : "Nao");//disponiblidade do livro em forma de string

        cJSON_AddItemToArray(json_array, json_book); //adicioa o objeto criado ao array/vetor
        current = current->next;//avança para o proximo livro
    }
    char *json_string = cJSON_Print(json_array);//converte o array para string

    fprintf(file, "%s", json_string);//escreve a string no json
    fclose(file);

    printf("\nSUCESSO: lista de livros salva em | %s |.\n", file_name);

    cJSON_Delete(json_array);
    free(json_string);
}

/**
 * @brief Carrega uma lista(JSON) escolhido pelo utilizador nno fim da lista atual
 * @param book_head Ponteiro para o primeiro livro da lista encadeada.
 */
void load_list_book(book *book_head){
    struct dirent *entry;
    DIR *dir = opendir("data/book_lists");

    if (dir == NULL){
        printf("ERRO: Não foi possível abrir a pasta 'data/book_lists'.\n");
        return;
    }

    printf("Listas de Livos disponiveis:\n");
    char files[50][100];
    int count = 0;

    while ((entry = readdir(dir)) != NULL){
        if (strstr(entry->d_name, ".json")){
            printf("[%d] %s\n", count + 1, entry->d_name);
            strncpy(files[count], entry->d_name, sizeof(files[count]) - 1);
            files[count][sizeof(files[count]) - 1] = '\0';
            count++;
        }
    }
    closedir(dir);

    if (count == 0){
        printf("ERRO: pasta esta vazia.\n");
        return;
    }
    
    int choice;
    printf("Escolha uma lista a ser carregado(1-%d): ", count);
    if (scanf("%d", &choice) != 1){
        printf("Entrada invalida.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    if (choice < 1 || choice > count){
        printf("opcao invalida.\n");
        return;
    }

    char filepath[150];
    sprintf(filepath, "data/book_lists/%s", files[choice - 1]);
    
    FILE *file = fopen(filepath, "r");
    if (file == NULL){
        printf("ERRO: nao e possivel abrir '%s'\n", filepath);
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);
    
    char *buffer = malloc(file_size + 1);
    if (!buffer){
        printf("ERRO: falha ao alocar memoria para leitura do JSON\n");
        fclose(file);
        return;
    }

    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';
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

    int max_id = 0;
    book current = *book_head;
    while (current != NULL) {
        if (current->book_id > max_id) {
            max_id = current->book_id;
        }
        current = current->next;
    }

    for (int i = 0; i < cJSON_GetArraySize(json); i++){
        cJSON *json_obj = cJSON_GetArrayItem(json, i);
        book new_book = malloc(sizeof(struct library));
        if (!new_book){
            printf("ERRO: Falha ao alocar memória para um livro.\n");
            cJSON_Delete(json);
            return;
        }

        //dados do livro(s)
        new_book->book_id = ++max_id;

        strncpy(new_book->book_name, cJSON_GetObjectItem(json_obj, "book_name")->valuestring, sizeof(new_book->book_name) - 1);
        new_book->book_name[sizeof(new_book->book_name) - 1] = '\0';

        strncpy(new_book->book_autor, cJSON_GetObjectItem(json_obj, "book_autor")->valuestring, sizeof(new_book->book_autor) - 1);
        new_book->book_autor[sizeof(new_book->book_autor) - 1] = '\0';

        new_book->book_edition = cJSON_GetObjectItem(json_obj, "book_edition")->valueint;

        cJSON *available_book = cJSON_GetObjectItem(json_obj, "book_available");
        if (available_book && cJSON_IsString(available_book)){
            if (strcmp(available_book->valuestring, "Sim") == 0){
                new_book->book_available = 1;
            }
            else if (strcmp(available_book->valuestring, "Nao") == 0){
                new_book->book_available = 0;
            }
            else{
                new_book->book_available = -1;
            }
        }
        else{
            new_book->book_available = -1;
        }
        
        new_book->next = NULL;

        if (*book_head == NULL){
            *book_head = new_book;
        }
        else{
            book current = *book_head;
            while (current->next != NULL){
                current = current->next;
            }
            current->next = new_book;
        }
    }
    cJSON_Delete(json);
    printf("SUCESSO: Lista carregada do ficheiro | %s |.\n", files[choice - 1]);    
}

/**
 * @brief Apaga uma lista(JSON) escolhido pelo utilizador da pasta "data/book_lists"
 */
void delete_list_book(){
    struct dirent *entry;
    DIR *dir = opendir("data/book_lists");

    if (dir == NULL) {
        printf("\nERRO: Não foi possível abrir a pasta 'book_lists'.\n");
        return;
    }

    printf("Listas de livros disponiveis:\n");    
    char files[50][100];
    int count = 0;

    while ((entry = readdir(dir)) != NULL){
        if (strstr(entry->d_name, ".json")){
            printf("[%d] %s\n", count + 1, entry->d_name);
            strncpy(files[count], entry->d_name, sizeof(files[count]) - 1);
            files[count][sizeof(files[count]) - 1] = '\0';
            count++;
        }
    }
    closedir(dir);

    if (count == 0) {
        printf("Nenhum ficheiro JSON encontrado na pasta 'book_lists'.\n");
        return;
    }

    int choice;
    printf("Escolha uma lista a ser deletado(1-%d): ", count);
    if (scanf("%d", &choice) != 1) {
        printf("Entrada invalida.\n");
        while (getchar() != '\n');  // Limpar buffer do teclado
        return;
    }
    while (getchar() != '\n');// para evitar entrada duplicada

    if (choice < 1 || choice > count) {
        printf("Opcao invalida.\n");
        return;
    }

    char filepath[150];
    sprintf(filepath, "data/book_lists/%s", files[choice - 1]);

    char confirm;
    printf("Tem certeza que deseja deletar '%s'? (s/n): ", files[choice - 1]);
    scanf(" %c", &confirm);
    if (confirm != 's' && confirm != 'S') {
        printf("Operacao cancelada.\n");
        return;
    }
    if (remove(filepath) == 0) {
        printf("SUCESSO: Arquivo '%s' deletado.\n", files[choice - 1]);
    } 
    else {
        printf("ERRO: Não foi possível deletar o ficheiro '%s'.\n", files[choice - 1]);
    }
}

/**
 * @brief Atualiza as informações de um livro atravez do ID fornecido
 * @note So é possivel atualizar o nome do livro, autor e edição do mesmo
 * @param book_head Ponteiro paro o ponteiro do primeiro livro da lista encadeada
 */
void updates_book(book *book_head){
    if (book_head == NULL){
        printf("ERRO: biblioteca vazia.\n");
        return;
    }

    list_books(*book_head);

    int bookID;
    printf("\nDigite o Id do livro que quer atualizar: ");
    if (scanf("%d", &bookID) != 1){
        printf("ERRO: entrada invalida.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    book updateBook = find_book(*book_head, bookID);
    if (updateBook == NULL){
        printf("ERRO: livro nao consta na lista.\n");
        return;
    }
    
    printf("informacoes atuais do livro:\n");
    printf("ID: %d | Titulo: %s | Autor: %s | Edicao: %d | Disponivel: %s\n",
        updateBook->book_id, updateBook->book_name, updateBook->book_autor,
        updateBook->book_edition, (updateBook->book_available == 1) ? "Sim" : "Nao");
    int option;
    do{
        printf("\nO que deseja atualizar?\n");
        printf("1 - Titulo\n");
        printf("2 - Autor\n");
        printf("3 - Edicao\n");
        printf("4 - Concluir atualizacao\n");
        printf("0 - Cancelar\n");
        printf("Escolha uma opcao: ");
        if (scanf("%d", &option) != 1) {
            printf("Entrada invalida.\n");
            while (getchar() != '\n');
            return;
        }
        while (getchar() != '\n'); 

        switch (option){
        case 1:{
            char newtitle[100];
            printf("Digite o novo titulo: ");
            fgets(newtitle, sizeof(newtitle), stdin);
            newtitle[strcspn(newtitle, "\n")] = '\0';
            strncpy(updateBook->book_name, newtitle, sizeof(updateBook->book_name) - 1);
            updateBook->book_name[sizeof(updateBook->book_name) - 1] = '\0';
            printf("Titulo atualizado com sucesso.\n");
            break;
        }

        case 2:{
            char new_autor[100];
            printf("Digite o novo autor: ");
            fgets(new_autor, sizeof(new_autor), stdin);
            new_autor[strcspn(new_autor, "\n")] = '\0';
            strncpy(updateBook->book_autor, new_autor, sizeof(updateBook->book_autor) - 1);
            updateBook->book_autor[sizeof(updateBook->book_autor) - 1] = '\0';
            printf("Autor atualizado com sucesso.\n");
            break;
        }

        case 3:{
            int new_edition;
            printf("Digite a nova edição: ");
            if (scanf("%d", &new_edition) != 1) {
                printf("Edição inválida.\n");
                while (getchar() != '\n');
                return;
            }
            while (getchar() != '\n');
            updateBook->book_edition = new_edition;
            printf("Edição atualizada com sucesso.\n");
            break;
        }

        case 4:
            printf("Atualização concluida.\n");
            break;

        case 0:
            printf("Atualização cancelada.\n");
            break;
    
        default:
            printf("ERRO: opcao invalida.\n");
            break;
        }
    } while (option != 0 && option != 4);
}

/**
 * @brief Carrega todas as listas(JSON's) da pasta "data/book_lists"
 * @param book_head Ponteiro paro o ponteiro do primeiro livro da lista encadeada
 */
void load_all_book_lists(book *book_head){
    if (*book_head == NULL) {
        printf("ERRO: biblioteca vazia\n");
        return;
    }

    struct dirent *entry;
    DIR *dir = opendir("data/book_lists");
    if (dir == NULL) {
        printf("ERRO: Não foi possível abrir a pasta 'book_lists'.\n");
        return;
    }

    int max_id = 0;
    book current = *book_head;
    while (current != NULL){
        if (current->book_id > max_id){
            max_id = current->book_id;
        }
        current = current->next;
    }

    while ((entry = readdir(dir)) != NULL){
        if (strstr(entry->d_name, ".json")){
            char filepath[150];
            sprintf(filepath, "data/book_lists/%s", entry->d_name);

            FILE *file = fopen(filepath, "r");
            if (file == NULL){
                printf("ERRO: Não foi possível abrir o %s\n", filepath);
                return;
            }

            fseek(file, 0, SEEK_END);
            long file_size = ftell(file);
            rewind(file);

            char *buffer = malloc(file_size + 1);
            if (!buffer){
                printf("ERRO: Não foi possível alocar memória para o buffer\n");
                fclose(file);
                continue;
            }

            fread(buffer, 1, file_size, file);
            buffer[file_size] = '\0';
            fclose(file);

            cJSON *json = cJSON_Parse(buffer);
            free(buffer);

            if(!json){
                printf("ERRO: falha ao analizar o JSON '%s'.\n", entry->d_name);
                continue;
            }
            if (!cJSON_IsArray(json)){
                printf("ERRO: o JSON '%s' não é um array.\n", entry->d_name);
                cJSON_Delete(json);
                continue;
            }
            
            for (int i = 0; i < cJSON_GetArraySize(json); i++) {
                cJSON *book_obj = cJSON_GetArrayItem(json, i);

                book new_book = malloc(sizeof(struct library));
                if (!new_book) {
                    printf("ERRO: Falha ao alocar memória para um livro.\n");
                    cJSON_Delete(json);
                    fclose(file);
                    return;
                }

                // Preenchendo os dados do livro
                new_book->book_id = ++max_id;

                strncpy(new_book->book_name, cJSON_GetObjectItem(book_obj, "book_name")->valuestring, sizeof(new_book->book_name) - 1);
                new_book->book_name[sizeof(new_book->book_name) - 1] = '\0';

                strncpy(new_book->book_autor, cJSON_GetObjectItem(book_obj, "book_autor")->valuestring, sizeof(new_book->book_autor) - 1);
                new_book->book_autor[sizeof(new_book->book_autor) - 1] = '\0';

                new_book->book_edition = cJSON_GetObjectItem(book_obj, "book_edition")->valueint;

                cJSON *avaliable_json = cJSON_GetObjectItem(book_obj, "book_available");
                if (avaliable_json && cJSON_IsString(avaliable_json)) {
                    if (strcmp(avaliable_json->valuestring, "Sim") == 0) {
                        new_book->book_available = 1;
                    } 
                    else if (strcmp(avaliable_json->valuestring, "Nao") == 0) {
                        new_book->book_available = 0;
                    } 
                    else {
                        new_book->book_available = -1;
                    }
                } 
                else {
                    new_book->book_available = -1;
                }

                new_book->next = NULL;
                if (*book_head == NULL){
                    *book_head = new_book;
                }
                else{
                    book current = *book_head;
                    while (current->next != NULL){
                        current = current->next;
                    }
                    current->next = new_book;
                }
            }
            cJSON_Delete(json);
        }
    }
    closedir(dir); 
    printf("SUCESSO: Todas as listas foram carregadas.\n");
}