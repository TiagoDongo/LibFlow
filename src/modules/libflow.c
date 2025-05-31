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
        book_head = book_head->next_book;
        free(temp);
    }
}

void book_menu(Book *book_head) {
    int option, id;

    do {
        printf("\n===== GERENCIAMENTO DE LIVROS =====\n");
        printf("1. Registrar livro\n");
        printf("2. Listar livros\n");
        printf("3. Buscar livro por ID\n");
        printf("4. Atualizar livro\n");
        printf("5. Remover livro\n");
        printf("6. Salvar lista de livros\n");
        printf("7. Carregar lista de livros\n");
        printf("8. Deletar lista de livros (JSON)\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &option) != 1) {
            printf("Entrada inválida!\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (option) {
            case 1: {
                int n;
                printf("Quantos livros deseja registrar: ");
                if (scanf("%d", &n) != 1 || n <= 0) {
                    printf("Entrada invalida!\n");
                    while (getchar() != '\n');
                    continue;
                }
                while (getchar() != '\n');
                puts("\n----- Registro de Livros -----\n");
                for (int i = 0; i < n; i++) {
                    regist_book(book_head);
                }
                break;
            }

            case 2:
                list_books(*book_head);
                break;

            case 3:
                printf("Digite o ID do livro: ");
                if (scanf("%d", &id) != 1) {
                    printf("Entrada invalida!\n");
                    while (getchar() != '\n');
                    continue;
                }
                while (getchar() != '\n');
                search_book(*book_head, id);
                break;

            case 4:
                updates_book(book_head);
                break;

            case 5: {
                int count;
                printf("Quantos livros deseja remover: ");
                if (scanf("%d", &count) != 1 || count <= 0) {
                    printf("Entrada invalida!\n");
                    while (getchar() != '\n');
                    continue;
                }
                while (getchar() != '\n');
                for (int i = 0; i < count; i++) {
                    printf("Digite o ID do livro: ");
                    if (scanf("%d", &id) != 1) {
                        printf("Entrada invalida!\n");
                        while (getchar() != '\n');
                        continue;
                    }
                    while (getchar() != '\n');
                    delete_book(book_head, id);
                }
                break;
            }

            case 6:
                save_list_books(*book_head);
                break;

            case 7:
                load_list_book(book_head);
                break;

            case 8:
                delete_list_book();
                break;

            case 0:
                printf("Voltando ao menu principal...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (option != 0);
}

void user_menu(User *user_head) {
    int option, id;

    do {
        printf("\n===== GERENCIAMENTO DE USUARIOS =====\n");
        printf("1. Registrar usuario\n");
        printf("2. Remover usuario\n");
        printf("3. Salvar lista de usuarios\n");
        printf("4. Carregar lista de usuarios\n");
        printf("5. Deletar lista de usuarios (JSON)\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &option) != 1) {
            printf("Entrada invalida!\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (option) {
            case 1: {
                int n;
                printf("Quantos usuarios deseja registrar: ");
                if (scanf("%d", &n) != 1 || n <= 0) {
                    printf("Entrada invalida!\n");
                    while (getchar() != '\n');
                    continue;
                }
                while (getchar() != '\n');
                puts("\n----- Registro de Usuarios -----\n");
                for (int i = 0; i < n; i++) {
                    regist_user(user_head);
                }
                break;
            }

            case 2: {
                int count;
                printf("Quantos usuarios deseja remover: ");
                if (scanf("%d", &count) != 1 || count <= 0) {
                    printf("Entrada invalida!\n");
                    while (getchar() != '\n');
                    continue;
                }
                while (getchar() != '\n');
                for (int i = 0; i < count; i++) {
                    printf("Digite o ID do usuario: ");
                    if (scanf("%d", &id) != 1) {
                        printf("Entrada invalida!\n");
                        while (getchar() != '\n');
                        continue;
                    }
                    while (getchar() != '\n');
                    delete_user(user_head, id);
                }
                break;
            }
            
            case 3:
                save_list_user(*user_head);
                break;
                
                case 4:
                load_list_user(user_head);
                break;
                
                case 5:
                printf("\nPor implementar\n");
                break;
                
                case 0:
                printf("Voltando ao menu principal...\n");
                break;
                
                default:
                printf("Opcao invalida!\n");
            }
        } while (option != 0);
    }
    
    
    void loan_menu(Loan *loan_head, Book *book_head, User *user_head) {
        int option;
        do {
            printf("\n===== GERENCIAMENTO DE EMPRESTIMOS =====\n");
            printf("1. Realizar emprestimo\n");
            printf("2. Devolver livro\n");
            printf("3. Salvar emprestimos\n");
            printf("4. Carregar emprestimos\n");
            printf("0. Voltar ao menu principal\n");
            printf("Escolha uma opcao: ");
    
            if (scanf("%d", &option) != 1) {
                printf("Entrada invalida!\n");
                while (getchar() != '\n');
                continue;
            }
            while (getchar() != '\n');
    
            switch (option) {
                case 1:
                    make_loan(loan_head, *book_head, *user_head);
                    break;
                case 2:
                    return_book(loan_head, *book_head);
                    break;
                case 3:
                    save_loans(*loan_head);
                    break;
                case 4:
                    load_loans(loan_head);
                    break;
                case 0:
                    printf("Voltando ao menu principal...\n");
                    break;
                default:
                    printf("Opcao invalida!\n");
            }
        } while (option != 0);
    }

void main_menu(Book *book_head, User *user_head) {
        int option;
    static Loan loan_head = NULL; // Mantém a lista de empréstimos

    do {
        printf("\n------ LIBFLOW MENU ------\n");
        printf("1. Gerenciar Livros\n");
        printf("2. Gerenciar Usuarios\n");
        printf("3. Gerenciar Emprestimos\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &option) != 1) {
            printf("Entrada inválida!\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (option) {
            case 1:
                book_menu(book_head);
                break;
            case 2:
                user_menu(user_head);
                break;
            case 3:
                loan_menu(&loan_head, book_head, user_head);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (option != 0);
}