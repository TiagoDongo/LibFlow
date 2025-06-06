#include"utils.h"

int id_generator(void *head, DataType type){
    int maxID = 0;

    while (head != NULL){
        int currentID = 0;

        switch (type){
            case TYPE_BOOK:
                currentID = ((struct library *)head)->book_id;
                head = ((struct library *)head)->next;
                break;

            case TYPE_USER:
                currentID = ((struct users *)head)->user_id;
                head = ((struct users *)head)->next;
                break;

            case TYPE_LOAN:
                currentID = ((struct loan *)head)->loan_id;
                head = ((struct loan *)head)->next;
                break;

            default:
                return -1;
                break;
        }

        if (currentID > maxID){
            maxID = currentID;
        }
    }
    return maxID + 1;
}

void *find_entity(void *head_list, int entityID, DataType type){
    switch (type) {
        case TYPE_BOOK: {
            Book current_book = (Book)head_list;
            while (current_book != NULL){
                if (current_book->book_id == entityID){
                    return current_book;
                }
                current_book = current_book->next;
            }
            break;
        }
        case TYPE_USER: {
            User current_user = (User)head_list;
            while (current_user != NULL){
                if (current_user->user_id == entityID){
                    return current_user;
                }
                current_user = current_user->next;
            }
            break;
        }
        case TYPE_LOAN: {
            Loan current_loan = (Loan)head_list;
            while (current_loan != NULL){
                if (current_loan->loan_id == entityID){
                    return current_loan;
                }
                current_loan = current_loan->next;
            }
            break;
        }
        default:
            return NULL;
    }
    return NULL;
}

const char *get_type_prefix(DataType type){
    switch (type){
        case TYPE_BOOK: return "Book_";

        case TYPE_USER: return "User_";

        case TYPE_LOAN: return "Loan_";
        
        default: return NULL;
    }
}

void generate_json_filename(char *filename, DataType type){
    const char *prefix = get_type_prefix(type);

    if (prefix == NULL){
        printf("ERRO: tipo de dado desconhecido.\n");
        return;
    }

    const char *dir_path;
    switch (type){
    case TYPE_BOOK: dir_path = "data"; break;

    case TYPE_USER: dir_path = "data/users"; break;

    case TYPE_LOAN: dir_path = "data/loans"; break;

    default:
        printf("ERRO: tipo de dado invalido.\n");
        break;
    }

    struct dirent *entry;
    DIR *dir = opendir(dir_path);
    if (dir == NULL){
        printf("ERRO: nao foi possivel abrir a pasta '%s'.\n", dir_path);
        return;
    }

    int max_index = 0;
    char pattern[64];
    snprintf(pattern, sizeof(pattern), "%s%d.json", prefix);

    while ((entry = readdir(dir)) != NULL){
        int current_index = 0;
        if (strstr(entry->d_name, prefix) && strstr(entry->d_name, ".json")){
            if (sscanf(entry->d_name, pattern, &current_index) == 1){
                if (current_index > max_index){
                    max_index = current_index;
                }
            }
        }
    }
    
    closedir(dir);


    snprintf(filename,FILENAME_MAX,"%s/%s%d.json",dir_path ,prefix, max_index + 1);

}


int validated_int_input(const char *prompt){
    int value, result;
    char c;

    do{
        printf("%s", prompt);
        result = scanf("%d", &value);

        while ((c = getchar()) != '\n' && c != EOF);
        
        if (result != 1 || value < 0){
            printf("ERRO: Entrada invalida. Por favor digite um numero inteiro nao negativo.\n");
        }
    } while (result != 1 || value < 0);

    return value;
}