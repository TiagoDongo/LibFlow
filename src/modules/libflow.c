#include"utils.h"
#include"library.h"
#include"client.h"
#include"loan.h"
#include"libflow.h"

void freedom(User user_head, Book book_head){
    while (user_head != NULL) {
        User temp = user_head;
        user_head = user_head->next;
        free(temp);
    }
    while (book_head != NULL) {
        Book temp = book_head;
        book_head = book_head->next;
        free(temp);
    }
}

void delete_entity(void **head, int entityID, DataType type){
    if (*head == NULL){
        puts("ERRO: lista vazia");
        return;
    }
    
    void *current = *head;
    void *previous = NULL;

    while (current != NULL){
        int currentId = -1;
        void *next = NULL;

        switch (type){
            case TYPE_BOOK:
                currentId = ((Book)current)->book_id;
                next = ((Book)current)->next;
                break;
            
            case TYPE_USER:
                currentId = ((User)current)->user_id;
                next = ((User)current)->next;
                break;

            default:
                puts("ERRO: tipo de dado desconhecido");
                return;
        }

        if (currentId == entityID){
            if (previous == NULL){
                *head = next;
            }else{
                if (type == TYPE_BOOK){
                    ((Book)previous)->next = next;
                }else if (type == TYPE_USER){
                    ((User)previous)->next = next;
                }
            }
            
            if (type == TYPE_BOOK) {
                printf("\nSUCESSO: | %s | foi removido da lista.\n", ((Book)current)->book_name);
            } else if (type == TYPE_USER) {
                printf("\nSUCESSO: | %s | foi removido da lista.\n", ((User)current)->user_name);
            }
            
            free(current);
            return;
        }
        previous = current;
        current = next;
    }
    puts("ERRO: item nao encontrado na lista.");
}

void search_entity(void *head, int entityID, DataType type){
    if (head == NULL){
        puts("\nERRO: lista vazia\n");
        return;
    }
    
    while (head != NULL){
        int currentId = -1;
        void *next = NULL;

        switch (type){
            case TYPE_BOOK:{
                Book current = (Book)head;
                currentId = current->book_id;
                next = current->next;

                if (currentId == entityID) {
                    puts("\nLivro encontrado:");
                    printf("ID: %d | Titulo: %s | Autor: %s | Edicao: %d | Disponivel: %s\n\n",
                           current->book_id, current->book_name, current->book_autor,
                           current->book_edition, (current->book_available ? "Sim" : "Nao"));
                    return;
                }
                break;
            }

            case TYPE_USER: {
                User current = (User)head;
                currentId = current->user_id;
                next = current->next;

                if (currentId == entityID) {
                    puts("\nUsuario encontrado:");
                    printf("ID: %d | Nome: %s | Email: %s\n\n",
                           current->user_id, current->user_name, current->user_email);
                    return;
                }
                break;
            }
            default:
                puts("ERRO: tipo de dado desconhecido");
                break;
        }
        head = next;
    }
    puts("ERRO: item nao encontrado ou foi removido.\n");
}

void list_entities(void *head, DataType type){
    if (head == NULL){
        puts("ERRO: lista vazia\n");
        return;
    }

    switch (type) {
        case TYPE_BOOK: {
            puts("--------------------- LISTA DE LIVROS ---------------------");
            puts("  ID    |   Titulo              |   Autor          |   Edicao   |   Disponivel  ");
            puts("--------------------------------------------------------------------------------");

            while (head != NULL) {
                Book current = (Book)head;
                printf("  %-6d|  %-20s|  %-15s|  %-8d|  %-12s\n",
                       current->book_id, current->book_name, current->book_autor,
                       current->book_edition, current->book_available ? "Sim" : "Nao");
                head = current->next;
            }
            break;
        }

        case TYPE_USER: {
            puts("--------------------- LISTA DE USUARIOS ---------------------");
            puts("  ID    |   Nome                |   Email");
            puts("-------------------------------------------------------------");

            while (head != NULL) {
                User current = (User)head;
                printf("  %-6d|  %-20s|  %-30s\n",
                       current->user_id, current->user_name, current->user_email);
                head = current->next;
            }
            break;
        }

        default:
            puts("ERRO: tipo de dado desconhecido");
            break;
    }
}

void delete_list(DataType type){
    const char *dirPath;

    switch (type){
        case TYPE_BOOK: dirPath = "data"; break;
        case TYPE_USER: dirPath = "data/users"; break;
        case TYPE_LOAN: dirPath = "data/loans"; break;
        default: puts("ERRO: tipo de dado desconhecido."); return;
    }

    DIR *dir = opendir(dirPath);
    if (dir == NULL){
        printf("ERRO: nao e possivel abrir a pasta '%s'\n", dirPath);
        return;
    }

    struct dirent *entry;
    char files[50][100];
    int count = 0;

    switch (type){
        case TYPE_BOOK: puts("Listas de Livros Disponiveis:"); break;
        case TYPE_USER: puts("Listas de Usuarios Disponiveis:"); break;
        case TYPE_LOAN: puts("Listas de Emprestimos Disponiveis:"); break;
    }
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
        printf("ERRO: diretorio vazio\n");
        return;
    }

    int choice = validated_int_input("Selecione a lista que deseja deletar: ");
    if (choice < 1 || choice > count) {
        printf("ERRO: Opcao invalida.\n");
        return;
    }

    char filePath[256];
    snprintf(filePath, sizeof(filePath), "%s/%s", dirPath, files[choice - 1]);

    char confirm[4];
    printf("Tem certeza que deseja deletar '%s'? (s/n): ", files[choice - 1]);
    fgets(confirm, sizeof(confirm), stdin);
    if (confirm[0] != 's' && confirm[0] != 'S') {
        puts("Operacao cancelada.");
        return;
    }

    if (remove(filePath) == 0) {
        printf("SUCESSO: Arquivo '%s' deletado.\n", files[choice - 1]);
    } else {
        printf("ERRO: Nao foi possível deletar o arquivo '%s'.\n", files[choice - 1]);
    }
}