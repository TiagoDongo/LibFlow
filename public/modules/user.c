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
            
            printf("1nSUCESSO: User | %s | foi removido da lista.\n", current_user->next);
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
