#include"../../src/utils.h"

/**
 * @brief Gera um novo ID para um livro baseado no maior ID presente na lista.
 * Percorre a lista encadeada de livros para encontrar o maior ID e retorna esse valor incrementado em 1.
 * @param book_head Ponteiro para o primeiro livro da lista encadeada.
 * @return int Novo ID para o livro.
 */
int book_id_generator(book book_head){
    int bookID = 0;

    while (book_head != NULL){
        if (book_head->book_id > bookID){
            bookID = book_head->book_id;
        }
        book_head = book_head->next;
    }
    return bookID + 1;
}

/**
 * @brief Gera um novo ID para um usuário baseado no maior ID presente na lista.
 * Percorre a lista encadeada de usuários para encontrar o maior ID e retorna esse valor incrementado em 1.
 * @param user_head Ponteiro para o primeiro usuário da lista encadeada.
 * @return int Novo ID para o usuário.
 */
int user_id_generator(user user_head){
    int userID = 0;

    while (user_head != NULL){
        if (user_head->user_id > userID){
            userID = user_head->user_id;
        }
        user_head = user_head->next;
    }
    return userID + 1;
}

/**
 * @brief Gera o nome de um arquivo para salvar a lista de livros.
 * Conta quantos arquivos com o prefixo "Book_" existem na pasta "data/book_lists" e gera um novo nome.
 * @param file_name Buffer onde o nome do arquivo será armazenado.
 */
void generate_book_filename(char *file_name){
    struct dirent *entry;
    DIR *dir = opendir("data/book_lists");
    if (dir == NULL){
        printf("ERRO: nao foi possivel abrir a pasta 'book_lists'.\n");
        return;
    }
    
    int count = 0;
    while ((entry = readdir(dir)) != NULL){
        if (strstr(entry->d_name, "Book_") && strstr(entry->d_name, ".json")){
            count++;
        }
    }
    closedir(dir);
    sprintf(file_name, "data/book_lists/Book_%d.json", count + 1);
}

/**
 * @brief Gera o nome de um arquivo para salvar a lista de usuários.
 * Conta quantos arquivos com o prefixo "User_" existem na pasta "data/user_lists" e gera um novo nome.
 * @param file_name Buffer onde o nome do arquivo será armazenado.
 */
void generate_user_filename(char *file_name){
    struct dirent *entry;
    DIR *dir = opendir("data/user_lists");
    if (dir == NULL){
        printf("ERRO: nao foi possivel abrir a pasta 'user_lists'.\n");
        return;
    }
    
    int count = 0;
    while ((entry = readdir(dir)) != NULL){
        if (strstr(entry->d_name, "User_") && strstr(entry->d_name, ".json")){
            count++;
        }
    }
    closedir(dir);
    sprintf(file_name, "data/user_lists/User_%d.json", count + 1);
}

/**
 * @brief Busca um livro na lista encadeada com base no ID.
 * Percorre a lista de livros procurando o livro cujo ID seja igual a @p bookID.
 * @param book_head Ponteiro para o primeiro livro da lista encadeada.
 * @param bookID ID do livro a ser procurado.
 * @return book Ponteiro para o livro encontrado ou NULL se não encontrado.
 */
book find_book(book book_head, int bookID){
    while (book_head != NULL){
       if (book_head->book_id == bookID){
            return book_head;
       }
        book_head = book_head->next;
    }
    return NULL;
}

/**
 * @brief Busca um usuário na lista encadeada com base no ID.
 * Percorre a lista de usuários procurando o usuário cujo ID seja igual a @p userID.
 * @param user_head Ponteiro para o primeiro usuário da lista encadeada.
 * @param userID ID do usuário a ser procurado.
 * @return user Ponteiro para o usuário encontrado ou NULL se não encontrado.
 */
user find_user(user user_head, int userID){
    while (user_head != NULL){
        if (user_head->user_id == userID){
             return user_head;
        }
         user_head = user_head->next;
     }
     return NULL;
}