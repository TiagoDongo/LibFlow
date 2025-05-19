#include <stdio.h>
#include <stdlib.h>
#include "library.h"

char last_loaded_file[100] = "";
int list_loaded = 0;

int main() {
    Book book_head = NULL;
    int opcao, id;

    do {
        printf("\n===== MENU BIBLIOTECA =====\n");
        printf("1. Registrar livro\n");
        printf("2. Listar livros\n");
        printf("3. Buscar livro por ID\n");
        printf("4. Atualizar livro\n");
        printf("5. Remover livro\n");
        printf("6. Salvar lista de livros\n");
        printf("7. Carregar lista de livros\n");
        printf("8. Deletar lista de livros (JSON)\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida!\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (opcao) {
            case 1:
                regist_book(&book_head);
                break;
            case 2:
                list_books(book_head);
                break;
            case 3:
                printf("Digite o ID do livro: ");
                scanf("%d", &id);
                while (getchar() != '\n');
                search_book(book_head, id);
                break;
            case 4:
                updates_book(&book_head);
                break;
            case 5:
                printf("Digite o ID do livro a remover: ");
                scanf("%d", &id);
                while (getchar() != '\n');
                delete_book(&book_head, id);
                break;
            case 6:
                save_list_books(book_head);
                break;
            case 7:
                load_list_book(&book_head);
                break;
            case 8:
                delete_list_book();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    // Libera memória dos livros
    while (book_head != NULL) {
        Book temp = book_head;
        book_head = book_head->next_book;
        free(temp);
    }

    return 0;
}