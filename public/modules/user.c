#include"../../src/user.h"
#include"../../src/cJSON.h"
#include"../../src/utils.h"

/**
 * @brief Registra um novo Utilizador na biblioteca
 * @param user_head Ponteiro para o ponteiro do primeiro utilizador da lista encadeada
 */
void regist_user(user *user_head){
    user new_user = (user)malloc(sizeof(struct users));
    if (new_user == NULL){
        printf("ERRO: alocacao falhou.\n");
        return; 
    }
    
    //user id
    new_user->user_id = user_id_generator(*user_head);

    //user name
    printf("Digite o nome do utilizador: ");
    scanf(" %99[^\n]", new_user->user_name);

    //user email
    printf("Digite o email do utilizador: ");
    scanf(" %99[^\n]", new_user->user_email);

    //user phone
    printf("Digite o telefone do utilizador: ");
    scanf("%d", &new_user->user_phone);

    //user course
    printf("Digite o curso do utilizador: ");
    scanf(" %99[^\n]", new_user->user_course);

    new_user->next = NULL;
    if (*user_head == NULL){
        *user_head = new_user;
    }
    else{
        user current_user = *user_head;
        while (current_user->next != NULL){
            current_user = current_user->next;
        }
        current_user->next = new_user;
    }
    printf("\nSUCESSO: User | %s | foi registado.\n", new_user->user_name);
}

/**
 * @brief Remove um Utilizador na biblioteca atravez do ID fornecido
 * @param user_head Ponteiro para o ponteiro do primeiro utilizador da lista encadeada
 */
void delete_user(user *user_head){
    int userID;
    user current_user = *user_head;
    user previous_user = NULL;

    if (*user_head == NULL){
        printf("ERRO: biblioteca vazia.\n");
        return;
    }
    
    printf("\nDigite o ID do usuario a ser removido: ");
    scanf("%d",&userID);

    while (current_user != NULL){
        if (current_user->user_id == userID){
            if (previous_user == NULL){
                *user_head = current_user->next;
            }
            else{
                previous_user->next = current_user->next;
            }
            
            printf("\nSUCESSO: User | %s | foi removido da lista.\n", current_user->user_name);
            free(current_user);
            return;
        }
        previous_user = current_user;
        current_user = current_user->next;
    }
    printf("ERRO: Usuario nao encontrado ou ja removido.\n");  
}

/**
 * @brief Procura um Utilizador na biblioteca atravez do seu ID
 * @param user_head Ponteiro para o primeiro usuario da lista encadeada
 */
void search_user(user user_head){
    int userID;

    if (user_head == NULL){
        printf("\nERRO: biblioteca vazia\n");
        return;
    }

    printf("\nDigite o ID do livro que esta a procura: ");
    scanf("%d", &userID);

    while (user_head != NULL){
        if (user_head->user_id == userID){
            printf("\nUsuario encontrado:\n");
            printf("ID: %d | Nome: %s | Email: %s | Telefone: %d | Curso: %s\n\n", user_head->user_id, user_head->user_name, user_head->user_email,user_head->user_phone, user_head->user_course);
            return;
        }
        user_head = user_head->next;
    }
    printf("ERRO: Usuario nao encontrado ou foi removido");
}

/**
 * @brief Lista todos os Utilizadores armazenados na biblioteca
 * @param user_head Ponteiro para o primeiro usuario da lista encadeada
 */
void list_users(user user_head){
    if (user_head == NULL){
        printf("\nERRO: biblioteca vazia\n");
        return;
    }
    
    printf("\n--------------------- LISTA DE USUARIOS ---------------------\n");
    printf("  ID    |   Titulo              |   Autor          |   Edicao   |   Disponivel  \n");
    printf("-----------------------------------------------------------------------------------------\n");

    user current_user = user_head;
    while (current_user != NULL){
        printf(" %-6d| %-20s| %-20s| %-8d| %-12s\n",
            current_user->user_id, current_user->user_name, current_user->user_email, current_user->user_phone, 
            current_user->user_course );

        current_user = current_user->next;
    }
}

/**
 * @brief Gera o nome do arquivo JSON para salvar a lista de usuarios
 * @param file_name Ponteiro para armazenar o nome do arquivo gerado
 */
void save_list_user(user user_head){
    if(user_head == NULL){
        printf("\nERRO: biblioteca vazia\n");
        return;
    }

    //gera o nome do .json
    char file_name[150];
    generate_user_filename(file_name);

    FILE *file = fopen(file_name, "w");
    if (file == NULL){
        printf("ERRO: nao foi possivel abrir o JSON.\n");
        return;
    }

    cJSON *json_array = cJSON_CreateArray();
    user current_user = user_head;
    while (current_user != NULL){
        cJSON *json_user = cJSON_CreateObject();
        
        cJSON_AddNumberToObject(json_user, "user_id", current_user->user_id);
        cJSON_AddStringToObject(json_user, "user_name", current_user->user_name);
        cJSON_AddStringToObject(json_user, "user_email", current_user->user_email);
        cJSON_AddNumberToObject(json_user, "user_phone", current_user->user_phone);
        cJSON_AddStringToObject(json_user, "user_course", current_user->user_course);

        cJSON_AddItemToArray(json_array, json_user);
        current_user = current_user->next;
    }
    char *json_string = cJSON_Print(json_array);
    fprintf(file, "%s", json_string);
    fclose(file);

    printf("\nSUCESSO: lista de usuarios salva em | %s |.\n", file_name);
    cJSON_Delete(json_array);
    free(json_string);
}

/**
 * @brief Carrega a lista de usuarios de um arquivo JSON
 * @param user_head Ponteiro para o primeiro usuario da lista encadeada
 */
void load_list_user(user *user_head){
    struct dirent *entry;
    DIR *dir = opendir("data/user_lists");
    if (dir == NULL) {
        printf("\nERRO: Não foi possível abrir a pasta 'user_lists'.\n");
        return;
    }

    printf("Listas de usuarios disponiveis:\n");
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
    sprintf(filepath, "data/user_lists/%s", files[choice - 1]);

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
    user current = *user_head;
    while (current != NULL) {
        if (current->user_id > max_id) {
            max_id = current->user_id;
        }
        current = current->next;
    }

    for(int i = 0; i < cJSON_GetArraySize(json); i++){
        cJSON *json_obj = cJSON_GetArrayItem(json, i);
        user new_user = (user)malloc(sizeof(struct users));
        if (!new_user) {
            printf("ERRO: Falha ao alocar memória para um usuario.\n");
            cJSON_Delete(json);
            return;
        }

        new_user->user_id = ++max_id;
        
        strncpy(new_user->user_name, cJSON_GetObjectItem(json_obj,"user_name")->valuestring, sizeof(new_user->user_name) - 1);
        new_user->user_name[sizeof(new_user->user_name) - 1] = '\0';

        strncpy(new_user->user_email, cJSON_GetObjectItem(json_obj,"user_email")->valuestring, sizeof(new_user->user_email) - 1);
        new_user->user_email[sizeof(new_user->user_email) - 1] = '\0';

        new_user->user_phone = cJSON_GetObjectItem(json_obj, "user_phone")->valueint;

        strncpy(new_user->user_course, cJSON_GetObjectItem(json_obj,"user_course")->valuestring, sizeof(new_user->user_course) - 1);
        new_user->user_course[sizeof(new_user->user_course) - 1] = '\0';

        new_user->next = NULL;

        if (*user_head == NULL){
            *user_head = new_user;
        }
        else{
            user current_user = *user_head;
            while (current_user->next != NULL){
                current_user = current_user->next;
            }
        }        
    }
    cJSON_Delete(json);
    printf("SUCESSO: lista carregada do ficheiro | %s |.\n", files[choice - 1]);
}

void delete_list_user(){
    struct dirent *entry;
    DIR *dir = opendir("data/user_lists");
    if (dir == NULL){
        printf("\nERRO: Não foi possível abrir a pasta 'user_lits'.\n");
        return;
    }

    printf("Listas de Usuarios disponiveis:\n");    
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
        printf("Nenhum ficheiro JSON encontrado na pasta 'user_lists'.\n");
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
    sprintf(filepath, "data/user_lists/%s", files[choice - 1]);

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

void update_user(user *user_head){
    if (*user_head == NULL){
        printf("ERRO: biblioteca de usuarios vazia.\n");
        return;
    }

    list_users(*user_head);

    int userID;
    printf("\nDigite o Id do usuario que quer atualizar: ");
    if (scanf("%d", &userID) != 1){
        printf("ERRO: entrada invalida.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    user updateUser = find_user(*user_head, userID);
    if (updateUser == NULL){
        printf("ERRO: usuario nao consta na lista.\n");
        return;
    }
    
    printf("informacoes atuais do livro:\n");
    printf("ID: %d | Nome: %s | Email: %s | Telefone: %d | Curso: %s\n",
        updateUser->user_id, updateUser->user_name, updateUser->user_email,
        updateUser->user_phone, updateUser->user_course);
    int option;
    do{
        printf("\nO que deseja atualizar?\n");
        printf("1 - Nome\n");
        printf("2 - Email\n");
        printf("3 - Curso\n");
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
            char newName[100];
            printf("Digite o novo nome: ");
            fgets(newName, sizeof(newName), stdin);
            newName[strcspn(newName, "\n")] = '\0';
            strncpy(updateUser->user_name, newName, sizeof(updateUser->user_name) - 1);
            updateUser->user_name[sizeof(updateUser->user_name) - 1] = '\0';
            printf("Nome atualizado com sucesso.\n");
            break;
        }

        case 2:{
            char new_email[100];
            printf("Digite o novo email: ");
            fgets(new_email, sizeof(new_email), stdin);
            new_email[strcspn(new_email, "\n")] = '\0';
            strncpy(updateUser->user_email, new_email, sizeof(updateUser->user_email) - 1);
            updateUser->user_email[sizeof(updateUser->user_email) - 1] = '\0';
            printf("Email atualizado com sucesso.\n");
            break;
        }

        case 3:{
            char new_course[100];
            printf("Digite o novo curso: ");
            fgets(new_course, sizeof(new_course), stdin);
            new_course[strcspn(new_course, "\n")] = '\0';
            strncpy(updateUser->user_course, new_course, sizeof(updateUser->user_course) - 1);
            updateUser->user_course[sizeof(updateUser->user_course) - 1] = '\0';
            printf("Curso atualizado com sucesso.\n");
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

void load_all_users_list(user *user_head){
    if (*user_head == NULL) {
        printf("ERRO: biblioteca de usuarios vazia\n");
        return;
    }

    struct dirent *entry;
    DIR *dir = opendir("data/user_lists");
    if (dir == NULL) {
        printf("ERRO: Não foi possível abrir a pasta 'user_lists'.\n");
        return;
    }

    int max_id = 0;
    user current = *user_head;
    while (current != NULL){
        if (current->user_id > max_id){
            max_id = current->user_id;
        }
        current = current->next;
    }

    while ((entry = readdir(dir)) != NULL){
        if (strstr(entry->d_name, ".json")){
            char filepath[150];
            sprintf(filepath, "data/user_lists/%s", entry->d_name);

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

                user new_user = malloc(sizeof(struct users));
                if (!new_user) {
                    printf("ERRO: Falha ao alocar memória para um usuario.\n");
                    cJSON_Delete(json);
                    fclose(file);
                    return;
                }

                // Preenchendo os dados do livro
                new_user->user_id = ++max_id;

                strncpy(new_user->user_name, cJSON_GetObjectItem(book_obj, "user_name")->valuestring, sizeof(new_user->user_name) - 1);
                new_user->user_name[sizeof(new_user->user_name) - 1] = '\0';

                strncpy(new_user->user_email, cJSON_GetObjectItem(book_obj, "user_email")->valuestring, sizeof(new_user->user_email) - 1);
                new_user->user_email[sizeof(new_user->user_email) - 1] = '\0';

                new_user->user_phone = cJSON_GetObjectItem(book_obj, "user_phone")->valueint;

                strncpy(new_user->user_course, cJSON_GetObjectItem(book_obj, "user_course")->valuestring, sizeof(new_user->user_course) - 1);
                new_user->user_course[sizeof(new_user->user_course) - 1] = '\0';

                new_user->next = NULL;
                if (*user_head == NULL){
                    *user_head = new_user;
                }
                else{
                    user current = *user_head;
                    while (current->next != NULL){
                        current = current->next;
                    }
                    current->next = new_user;
                }
            }
            cJSON_Delete(json);
        }
    }
    closedir(dir); 
    printf("SUCESSO: Todas as listas foram carregadas.\n");
}