#include"../src/data_base.h"
#include"../src/library.h"
#include"../src/user.h"
#include"../src/utils.h"
#include"../src/cJSON.h"

int main() {
    book book_head = NULL;
    int choice;

    // Garante que a pasta existe
    system("mkdir -p data/book_lists");
    system("mkdir -p data/user_lists");

    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Cadastrar Livro\n");
        printf("2. Remover Livro\n");
        printf("3. Buscar Livro\n");
        printf("4. Listar Livros\n");
        printf("5. Salvar Lista em JSON\n");
        printf("6. Carregar Lista de JSON\n");
        printf("7. Deletar Lista de JSON\n");
        printf("8. Atualizar Livro\n");
        printf("9. Carregar Todas as Listas\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);
        while (getchar() != '\n'); // Limpa o buffer

        switch (choice) {
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
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (choice != 0);

    // Liberar memória ao sair (opcional)
    book current = book_head;
    while (current != NULL) {
        book temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}