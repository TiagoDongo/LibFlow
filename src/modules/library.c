#include"library.h"
#include"cJSON.h"

void regist_book(Book *book_head){
    Book new_book = (Book)malloc(sizeof(struct library));
    if (new_book == NULL){
        puts("Erro de alocacao");
        return;
    }

    new_book->book_id = book_id_generator(*book_head);

    printf("Digite o nome do livro: ");
    scanf(" %99[^\n]", new_book->book_name);

    printf("Digite o nome do autor do livro: ");
    scanf(" %99[^\n]", new_book->book_autor);

    printf("Digite a edicao do livro: ");
    scanf("%d", &new_book->book_edition);

    new_book->book_available = 1;

    new_book->next_book = NULL;
    if (*book_head == NULL){
        *book_head = new_book;
    }
    else{
        Book current = *book_head;
        while (current->next_book != NULL){
            current = current->next_book;
        }
        current->next_book = new_book;
    }
    printf("SUCESSO: livro '%s' adicionado a biblioteca", new_book->book_name);
}

void delete_book(Book *book_head, int bookID){
    Book current_book = *book_head;
    Book previous_book = NULL;

    if (*book_head == NULL){
        puts("ERROR: biblioteca vazia");
        return;
    }
    
    while (current_book != NULL){
        if (current_book->book_id == bookID){
            if (previous_book == NULL){
                *book_head = current_book->next_book;
            }
            else {
                previous_book->next_book = current_book->next_book;
            }
            printf("\nSUCESSO: livro | %s | foi removido da lista.\n", current_book->book_name);
            free(current_book);
            return;            
        }
        previous_book = current_book;
        current_book = current_book->next_book;
    }
    puts("ERRO: livro nao encontrado");
}

void search_book(Book book_head, int bookID){
    if (book_head == NULL){
        puts("ERRO: biblioteca vazia");
        return;
    }

    while (book_head != NULL){
        if (book_head->book_id == bookID){
            puts("Livro encontrado:");
            printf("ID: %d | Titulo: %s | Autor: %s | Edicao: %d | Disponivel: %s\n\n",
            book_head->book_id, book_head->book_name, book_head->book_autor, book_head->book_edition, (book_head->book_available == 1) ? "Sim" : "Nao");
            return;
        }
        book_head = book_head->next_book;
    }
    puts("ERRO: Livro nao encontrado ou foi removido.");
}

void list_books(Book book_head){
    if (book_head == NULL){
        puts("ERRO: biblioteca vazia");
        return;
    }

    puts("--------------------- LISTA DE LIVROS ---------------------");
    puts("  ID    |   Titulo              |   Autor          |   Edicao   |   Disponivel  ");
    puts("--------------------------------------------------------------------------------");

    while (book_head != NULL){
        printf("  %-6d|  %-20s|  %-15s|  %-8d|  %-12s\n",
            book_head->book_id, book_head->book_name, book_head->book_autor, book_head->book_edition, 
            (book_head->book_available == 1) ? "Sim" : "Nao");

        book_head = book_head->next_book;
    }
}

void updates_book(Book *book_head){
    int bookID, option;

    if (book_head == NULL){
        puts("ERRO: biblioteca vazia.");
        return;
    }

    list_books(*book_head);

    printf("Digite o ID do livro a ser atualizado: ");
    if (scanf("%d", &bookID) != 1){
        printf("ERRO: entrada invalida.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    Book updatingBook = find_book(*book_head, bookID);
    if (updatingBook == NULL){
        puts("ERRO: livro nao encontrado");
        return;
    }

    puts("Informacoes atuais do livro:");
    printf("ID: %d | Titulo: %s | Autor: %s | Edicao: %d | Disponivel: %s\n",
        updatingBook->book_id, updatingBook->book_name, updatingBook->book_autor,
        updatingBook->book_edition, (updatingBook->book_available == 1) ? "Sim" : "Nao");
    
    
    do{
        puts("O que deseja atualizar?");
        puts("1 - Titulo");
        puts("2 - Autor");
        puts("3 - Edicao");
        puts("4 - Concluir atualizacao");
        puts("0 - Cancelar");
        puts("Escolha uma opcao: ");
        if (scanf("%d", &option) != 1) {
            printf("ERRO: Entrada invalida.\n");
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
            strncpy(updatingBook->book_name, newtitle, sizeof(updatingBook->book_name) - 1);
            updatingBook->book_name[sizeof(updatingBook->book_name) - 1] = '\0';
            printf("SUCESSO: Titulo do livro atualizado .\n");
            break;
        }

        case 2:{
            char new_autor[100];
            printf("Digite o novo autor: ");
            fgets(new_autor, sizeof(new_autor), stdin);
            new_autor[strcspn(new_autor, "\n")] = '\0';
            strncpy(updatingBook->book_autor, new_autor, sizeof(updatingBook->book_autor) - 1);
            updatingBook->book_autor[sizeof(updatingBook->book_autor) - 1] = '\0';
            printf("SUCESSO: Autor do livro atualizado.\n");
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
            updatingBook->book_edition = new_edition;
            printf("SUCESSO: Edição do livro atualizada\n");
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

void save_list_books(Book book_head){
    char filename[100];

    if (book_head == NULL){
        puts("ERRO: biblioteca vazia");
        return;
    }

    if (list_loaded && strlen(last_loaded_file) > 0){
        printf("Dejesa sobescrever o ficheiro carregado anteriormente (%s) (s/n): ", last_loaded_file);
        char resposta;
        scanf("%c", &resposta);

        if (resposta == 's' || resposta == 'S'){
            strcpy(filename, last_loaded_file);
        }else{
            generate_json_book_filename(filename);
        }
    }else{
        generate_json_book_filename(filename);
    }

    FILE *file = fopen(filename, "w");
    if (file == NULL){
        printf("ERRO: nao foi possivel abrir o ficheiro JSON.\n");
        return;
    }

    cJSON *json_array = cJSON_CreateArray();

    while (book_head != NULL){
        cJSON *json_book = cJSON_CreateObject();
        cJSON_AddNumberToObject(json_book, "book_id", book_head->book_id);
        cJSON_AddStringToObject(json_book, "book_name", book_head->book_name);
        cJSON_AddStringToObject(json_book, "book_autor", book_head->book_autor);
        cJSON_AddNumberToObject(json_book, "book_edition", book_head->book_edition);
        cJSON_AddStringToObject(json_book, "book_available", book_head->book_available ? "Sim" : "Nao");

        cJSON_AddItemToArray(json_array, json_book);
        book_head = book_head->next_book;
    }
    
    char *json_string = cJSON_Print(json_array);
    fprintf(file, "%s", json_string);
    fclose(file);

    strcpy(last_loaded_file, filename);

    cJSON_Delete(json_array);
    free(json_string);    
}

void load_list_book(Book *book_head){
    if (*book_head != NULL && list_loaded == 0){
        char option;
        printf("AVISO: Existe uma lista atual que ainda nao foi salva.\n");
        printf("Deseja salva-la antes de carregar uma nova? (s/n): ");
        scanf("%c", &option);
        while (getchar() != '\n');
        
        if (option == 's' || option == 'S'){
            save_list_books(*book_head);
            list_loaded = 1;
        }
    }
    
    struct dirent *entry;
    DIR *dir = opendir("data");
    if (dir == NULL){
        printf("ERRO: nao e possivel abrir a pasta 'data'.\n");
        return;
    }

    puts("Listas de livros disponiveis:");
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
        printf("ERRO: A pasta esta vazia.\n");
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
        printf("ERRO: opcao invalida.\n");
        return;
    }

    char filepath[150];
    sprintf(filepath, "data/%s", files[choice - 1]);
    
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
    
    int max_id = 0;
    Book current = *book_head;
    while (current != NULL){
        if (current->book_id > max_id){
            max_id = current->book_id;
        }
        current = current->next_book;
    }

    for (int i = 0; i < cJSON_GetArraySize(json); i++){
        cJSON *json_obj = cJSON_GetArrayItem(json, i);
        Book new_book = malloc(sizeof(struct library));
        if (!new_book){
            printf("ERRO: Falha ao alocar memória para um livro.\n");
            cJSON_Delete(json);
            return;
        }
        
        new_book->book_id = ++max_id;

        strncpy(new_book->book_name, cJSON_GetObjectItem(json_obj, "book_name")->valuestring, sizeof(new_book->book_name) - 1);
        new_book->book_name[sizeof(new_book->book_name) - 1] = '\0';

        strncpy(new_book->book_autor, cJSON_GetObjectItem(json_obj, "book_autor")->valuestring, sizeof(new_book->book_autor) - 1);
        new_book->book_name[sizeof(new_book->book_autor) - 1] = '\0';

        new_book->book_edition = cJSON_GetObjectItem(json_obj, "book_edition")->valueint;

        cJSON *available = cJSON_GetObjectItem(json_obj, "book_available");
        if (available && cJSON_IsString(available)){
            if (strcmp(available->valuestring, "Sim") == 0){
                new_book->book_available = 1;
            }
            else if (strcmp(available->valuestring, "Nao") == 0){
                new_book->book_available = 0;
            }
            else {
                new_book->book_available = -1;
            }
        }
        else {
            new_book->book_available = -1;
        }
        
        new_book->next_book = NULL;

        if (*book_head == NULL){
            *book_head = new_book;
        }
        else {
            Book last = *book_head;
            while (last->next_book != NULL){
                last = last->next_book;
            }
            last->next_book = new_book;
        }
    }
    
    cJSON_Delete(json);
    list_loaded = 1;
    printf("SUCESSO: Lista carregada do ficheiro | %s |.\n", files[choice - 1]);    
}

void delete_list_book(){
    struct dirent *entry;
    DIR *dir = opendir("data");

    if (dir == NULL){
        puts("ERRO: nao e possivel abrir a pasta 'data'");
        return;
    }

    puts("Listas de livros disponiveis:");
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
        printf("ERRO: A pasta esta vazia\n");
        return;
    }

    int choice;
    printf("Seleciona a lista que deseja deletar(1-%d): ", count);
    if (scanf("%d", &choice) != 1) {
        printf("Entrada invalida.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');
    
    if (choice < 1 || choice > count) {
        printf("ERRO: Opcao invalida.\n");
        return;
    }

    char filepath[150];
    sprintf(filepath, "data/%s", files[choice - 1]);

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

int book_id_generator(Book book_head){
    int bookID = 0;

    while (book_head != NULL){
        if (book_head->book_id > bookID){
            bookID = book_head->book_id;
        }
        book_head = book_head->next_book;
    }
    return bookID + 1;
}

void generate_json_book_filename(char *filename){
    struct dirent *entry;
    DIR *dir = opendir("data");
    if (dir == NULL){
        printf("ERRO: nao foi possivel abrir a pasta 'data'.\n");
        return;
    }
    
    int max_index = 0;
    while ((entry = readdir(dir)) != NULL){
        if (strstr(entry->d_name, "Book_") && strstr(entry->d_name, ".json")){
            int current_index = 0;

            if (sscanf(entry->d_name, "Book_%d.json", &current_index) == 1){
                if (current_index > max_index){
                    max_index = current_index;
                }
            }
        }
    }
    closedir(dir);
    sprintf(filename, "data/Book_%d.json", max_index + 1);
}

Book find_book(Book book_head, int bookID){
    while (book_head != NULL){
       if (book_head->book_id == bookID){
            return book_head;
       }
        book_head = book_head->next_book;
    }
    return NULL;
}