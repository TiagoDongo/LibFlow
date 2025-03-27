#include "../src/data_base.h"
#include "../src/library.h"
#include "../src/user.h"
#include "../src/utils.h"
#include "../src/cJSON.h"

int main()
{
    book book_head = NULL;
    user user_head = NULL;
    int choice;

    // Garante que a pasta existe
    system("mkdir -p data/book_lists");
    system("mkdir -p data/user_lists");

    do
    {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Cadastrar Livro\n");
        printf("2. Remover Livro\n");
        printf("3. Buscar Livro\n");
        printf("4. Listar Livros\n");
        printf("5. Salvar Lista de Livros em JSON\n");
        printf("6. Carregar Lista de Livros de JSON\n");
        printf("7. Deletar Lista de Livros de JSON\n");
        printf("8. Atualizar Livro\n");
        printf("9. Carregar Todas as Listas de Livros\n");
        printf("10. Cadastrar Usuário\n");
        printf("11. Remover Usuário\n");
        printf("12. Buscar Usuário\n");
        printf("13. Listar Usuários\n");
        printf("14. Salvar Lista de Usuários em JSON\n");
        printf("15. Carregar Lista de Usuários de JSON\n");
        printf("16. Deletar Lista de Usuários de JSON\n");
        printf("17. Atualizar Usuário\n");
        printf("18. Carregar Todas as Listas de Usuários\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);
        while (getchar() != '\n')
            ; // Limpa o buffer

        switch (choice)
        {
        case 1:
            regist_book(&book_head);
            break;
        case 2:
            delete_book(&book_head);
            break;
        case 3:
            search_book(book_head);
            break;
        case 4:
            list_books(book_head);
            break;
        case 5:
            save_list_books(book_head);
            break;
        case 6:
            load_list_book(&book_head);
            break;
        case 7:
            delete_list_book();
            break;
        case 8:
            updates_book(&book_head);
            break;
        case 9:
            load_all_book_lists(&book_head);
            break;
        case 10:
            regist_user(&user_head);
            break;
        case 11:
            delete_user(&user_head);
            break;
        case 12:
            search_user(user_head);
            break;
        case 13:
            list_users(user_head);
            break;
        case 14:
            save_list_user(user_head);
            break;
        case 15:
            load_list_user(&user_head);
            break;
        case 16:
            delete_list_user();
            break;
        case 17:
            update_user(&user_head);
            break;
        case 18:
            load_all_users_list(&user_head);
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (choice != 0);

    // Liberar memória ao sair (opcional)
    book current_book = book_head;
    while (current_book != NULL)
    {
        book temp = current_book;
        current_book = current_book->next;
        free(temp);
    }

    user current_user = user_head;
    while (current_user != NULL)
    {
        user temp = current_user;
        current_user = current_user->next;
        free(temp);
    }

    return 0;
}