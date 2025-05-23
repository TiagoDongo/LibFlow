#include"client.h"
#include"cJSON.h"
#include"utils.h"

void regist_user(User *user_head){
    User new_user = (User)malloc(sizeof(struct users));
    if (new_user == NULL){
        printf("Erro de alocacao.\n");
        return;
    }
    
    new_user->user_id = id_generator(*user_head, TYPE_USER);

    puts("\n----- Registro de Usuarios -----\n");

    printf("Digite o nome do usuario: ");
    fgets(new_user->user_name, sizeof(new_user->user_name), stdin);
    new_user->user_name[strcspn(new_user->user_name, "\n")] = '\0';

    printf("Digite o email do usuario: ");
    fgets(new_user->user_email, sizeof(new_user->user_email), stdin);
    new_user->user_email[strcspn(new_user->user_email, "\n")] = '\0';

    new_user->next = NULL;
    if (*user_head == NULL){
        *user_head = new_user;
    }
    else {
        User current = *user_head;
        while (current->next != NULL){
            current = current->next;
        }
        current->next = new_user;
    }
    printf("\nSUCESSO: Usuario '%s' foi registado\n", new_user->user_name);
}

void delete_user(User *user_head, int userID){
    User current_user = *user_head;
    User previous_user = NULL;

    if (*user_head == NULL){
        puts("ERROR: registro de usuarios vazia");
        return;
    }
    
    while (current_user != NULL){
        if (current_user->user_id == userID){
            if (previous_user == NULL){
                *user_head = current_user->next;
            }
            else {
                previous_user->next = current_user->next;
            }
            printf("\nSUCESSO: usuario | %s | foi removido dos registros.\n", current_user->user_name);
            free(current_user);
            return;            
        }
        previous_user = current_user;
        current_user = current_user->next;
    }
    puts("ERRO: usuario nao encontrado");
    
}

void save_list_user(User user_head){
    char filename[100];

    if (user_head == NULL){
        puts("ERRO: registro de usuarios vazia");
        return;
    }

    if (list_loaded && strlen(last_loaded_file) > 0){
        printf("Dejesa sobescrever o ficheiro carregado anteriormente (%s) (s/n): ", last_loaded_file);
        char resposta;
        scanf("%c", &resposta);

        if (resposta == 's' || resposta == 'S'){
            strcpy(filename, last_loaded_file);
        }else{
            generate_json_filename(filename, TYPE_USER);
        }
    }else{
        generate_json_filename(filename, TYPE_USER);
    }

    FILE *file = fopen(filename, "w");
    if (file == NULL){
        printf("ERRO: nao foi possivel abrir o ficheiro JSON.\n");
        return;
    }

    cJSON *user_array = cJSON_CreateArray();

    while (user_head != NULL){
        cJSON *json_user = cJSON_CreateObject();
        cJSON_AddNumberToObject(json_user, "user_id", user_head->user_id);
        cJSON_AddStringToObject(json_user, "user_name", user_head->user_name);
        cJSON_AddStringToObject(json_user, "user_email", user_head->user_email);

        cJSON_AddItemToArray(user_array, json_user);
        user_head = user_head->next;
    }

    char *user_json_string = cJSON_Print(user_array);
    fprintf(file, "%s", user_json_string);
    fclose(file);

    strcpy(last_loaded_file, filename);

    cJSON_Delete(user_array);
    free(user_json_string);
}

void load_list_user(User *user_head){
    if (*user_head != NULL && list_loaded == 0){
        char option;
        printf("AVISO: Existe uma lista atual que ainda nao foi salva.\n");
        printf("Deseja salva-la antes de carregar uma nova? (s/n): ");
        scanf("%c", &option);
        while (getchar() != '\n');
        
        if (option == 's' || option == 'S'){
            save_list_user(*user_head);
            list_loaded = 1;
        }
    }
    
    struct dirent *entry;
    DIR *dir = opendir("data/users");
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
        printf("ERRO: diretorio vazia.\n");
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
    sprintf(filepath, "data/users/%s", files[choice - 1]);
    
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
    User current = *user_head;
    while (current != NULL){
        if (current->user_id > max_id){
            max_id = current->user_id;
        }
        current = current->next;
    }

    for (int i = 0; i < cJSON_GetArraySize(json); i++){
        cJSON *json_obj = cJSON_GetArrayItem(json, i);
        User new_user = malloc(sizeof(struct users));
        if (!new_user){
            printf("ERRO: Falha ao alocar memória para um usuario.\n");
            cJSON_Delete(json);
            return;
        }
        
        new_user->user_id = ++max_id;

        strncpy(new_user->user_name, cJSON_GetObjectItem(json_obj, "user_name")->valuestring, sizeof(new_user->user_name) - 1);
        new_user->user_name[sizeof(new_user->user_name) - 1] = '\0';

        strncpy(new_user->user_email, cJSON_GetObjectItem(json_obj, "user_email")->valuestring, sizeof(new_user->user_email) - 1);
        new_user->user_email[sizeof(new_user->user_email) - 1] = '\0';
        
        new_user->next = NULL;

        if (*user_head == NULL){
            *user_head = new_user;
        }
        else {
            User last = *user_head;
            while (last->next != NULL){
                last = last->next;
            }
            last->next = new_user;
        }
    }
    
    cJSON_Delete(json);
    list_loaded = 1;
    printf("SUCESSO: Lista carregada do ficheiro | %s |.\n", files[choice - 1]);    
}