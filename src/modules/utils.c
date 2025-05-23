#include"utils.h"

int id_generator(void *head, DataType type){
    int maxID = 0;

    while (head != NULL){
        int currentID = 0;

        switch (type){
            case TYPE_BOOK:
                currentID = ((struct library *)head)->book_id;
                head = ((struct library *)head)->next_book;
                break;

            case TYPE_USER:
                currentID = ((struct users *)head)->user_id;
                head = ((struct users *)head)->next;
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
    if (type == TYPE_BOOK){
        Book current_book = (Book)head_list;
        while (current_book != NULL){
        if (current_book->book_id == entityID){
                return current_book;
        }
            current_book = current_book->next_book;
        }
    } 
    else if (type == TYPE_USER){
        User current_user = (User)head_list;
        while (current_user != NULL){
        if (current_user->user_id == entityID){
                return current_user;
        }
            current_user = current_user->next;
        }
    }
    
    return NULL;
    
}

const char *get_type_prefix(DataType type){
    switch (type){
        case TYPE_BOOK: return "Book_";

        case TYPE_USER: return "User_";
        
        default: return NULL;
    }
}

void generate_json_filename(char *filename, DataType type){
    const char *prefix = get_type_prefix(type);

    if (prefix == NULL){
        printf("ERRO: tipo de dado desconhecido.\n");
        return;
    }

    const char *dir_path = (type == TYPE_USER) ? "data/users" : "data";
    struct dirent *entry;
    DIR *dir = opendir(dir_path);
    if (dir == NULL){
        printf("ERRO: nao foi possivel abrir a pasta '%s'.\n", dir_path);
        return;
    }

    int max_index = 0;
    char name_format[100];
    snprintf(name_format, sizeof(name_format), "%s%d.json", prefix);

    while ((entry = readdir(dir)) != NULL){
        int current_index = 0;
        if (strstr(entry->d_name, prefix) && strstr(entry->d_name, ".json")){
            if (sscanf(entry->d_name, name_format, &current_index) == 1){
                if (current_index > max_index){
                    max_index = current_index;
                }
            }
        }
    }
    
    closedir(dir);

    if (type == TYPE_USER) {
        sprintf(filename, "data/users/%s%d.json", prefix, max_index + 1);
    } else {
        sprintf(filename, "data/%s%d.json", prefix, max_index + 1);
    }

}

void freedom(User user_head, Book book_head){
    while (user_head != NULL) {
        User temp = user_head;
        user_head = user_head->next;
        free(temp);
    }
    while (book_head != NULL) {
        Book temp = book_head;
        book_head = book_head->next_book;
        free(temp);
    }
}