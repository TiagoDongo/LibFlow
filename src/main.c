#include "utils.h"
#include "library.h"
#include "client.h"
#include "loan.h"
#include "libflow.h"

char last_loaded_file[100] = "";
int list_loaded = 0;

int main()
{
    Book book_head = NULL;
    User user_head = NULL;
    Loan loan_head = NULL;
    int opcao, tipo, id;

    do
    {
        puts("\n==== LibFlow ====");
        puts("1 - Registrar");
        puts("2 - Realizar emprestimo");
        puts("3 - Devolver livro");
        puts("4 - Salvar listas");
        puts("5 - Carregar listas");
        puts("6 - Listar entidades");
        puts("7 - Buscar entidade por ID");
        puts("8 - Remover entidade");
        puts("9 - Deletar arquivo de lista");
        puts("0 - Sair");
        opcao = validated_int_input("Escolha uma opcao: ");

        switch (opcao)
        {
        case 1:{
            puts("O que deseja registar? 1-Livro 2-Usuario");
            tipo = validated_int_input("Opcao: ");
            if (tipo == 1){ 
                regist_book(&book_head);
            }else if (tipo == 2){ 
                regist_user(&user_head);
            }else{
                puts("Tipo invalido.");
            }
            break;
        }

        case 2:
            make_loan(&loan_head, book_head, user_head);
            break;

        case 3:
            return_book(&loan_head, book_head);
            break;

        case 4:{
            puts("Salvar qual lista? 1-Livros  2-Usuarios  3-Emprestimos");
            tipo = validated_int_input("Opcao: ");
            if (tipo == 1){
                save_list_books(book_head);
            }else if (tipo == 2){
                save_list_user(user_head);
            }else if (tipo == 3){
                save_loans(loan_head);
            }else{
                puts("Tipo invalido.");
            }
            break;
        }

        case 5:{
            puts("Carregar qual lista? 1-Livros  2-Usuarios  3-Emprestimos");
            tipo = validated_int_input("Opcao: ");
            if (tipo == 1){
                load_list_book(&book_head);
            }else if (tipo == 2){
                load_list_user(&user_head);
            }else if (tipo == 3){
                load_loans(&loan_head);
            }else{
                puts("Tipo invalido.");
            }
            break;
        }

        case 6:{
            puts("Listar qual entidade? 1-Livros  2-Usuarios");
            tipo = validated_int_input("Opcao: ");
            if (tipo == 1){
                list_entities(book_head, TYPE_BOOK);
            }else if (tipo == 2){
                list_entities(user_head, TYPE_USER);
            }else{
                puts("Tipo invalido.");
            }
            break;
        }

        case 7:{
            puts("Buscar qual entidade? 1-Livros  2-Usuarios");
            tipo = validated_int_input("Opcao: ");
            id = validated_int_input("Digite o ID: ");
            if (tipo == 1){
                search_entity(book_head, id, TYPE_BOOK);
            }else if (tipo == 2){
                search_entity(user_head, id, TYPE_USER);
            }else{
                puts("Tipo invalido.");
            }
            break;
        }

        case 8:{
            puts("Remover qual entidade? 1-Livros  2-Usuarios");
            tipo = validated_int_input("Opcao: ");
            id = validated_int_input("Digite o ID: ");
            if (tipo == 1)
                delete_entity((void **)&book_head, id, TYPE_BOOK);
            else if (tipo == 2)
                delete_entity((void **)&user_head, id, TYPE_USER);
            else
                puts("Tipo invalido ou nao suportado.");
            break;
        }

        case 9:{
            puts("Deletar arquivo de qual lista? 1-Livros  2-Usuarios  3-Emprestimos");
            tipo = validated_int_input("Opcao: ");
            if (tipo == 1)
                delete_list(TYPE_BOOK);
            else if (tipo == 2)
                delete_list(TYPE_USER);
            else if (tipo == 3)
                delete_list(TYPE_LOAN);
            else
                puts("Tipo invalido.");
            break;
        }

        case 0:
            puts("Saindo...");
            break;

        default:
            puts("Opcao invalida.");
        }
    } while (opcao != 0);

    freedom(user_head, book_head);
    while (loan_head != NULL)
    {
        Loan temp = loan_head;
        loan_head = loan_head->next;
        free(temp);
    }

    return 0;
}