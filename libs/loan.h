/**
 * @file loan.h
 * @brief Funções para gerenciamento de empréstimos de livros
 */

#ifndef LOAN_H_INCLUDED
#define LOAN_H_INCLUDED

#include "database.h"

/**
 * @brief Realiza um novo empréstimo.
 * 
 * Cria um novo registro de empréstimo ligando um usuário a um livro através do ID,
 * marcando o livro como indisponível.
 * 
 * @param loan_head Ponteiro para o ponteiro do início da lista de empréstimos.
 * @param book_head Início da lista de livros.
 * @param user_head Início da lista de usuários.
 */
void make_loan(Loan *loan_head, Book book_head, User user_head);

/**
 * @brief Realiza a devolução de um livro emprestado.
 * 
 * Marca o livro como disponível e atualiza o status do empréstimo.
 * 
 * @param loan_head Início da lista de empréstimos.
 * @param book_head Início da lista de livros.
 */
void return_book(Loan *loan_head, Book book_head);

/**
 * @brief Salva a lista de empréstimos em um arquivo JSON.
 * 
 * @param loan_head Início da lista de empréstimos.
 */
void save_loans(Loan loan_head);

/**
 * @brief Carrega a lista de empréstimos de um arquivo JSON.
 * 
 * @param loan_head Ponteiro para o ponteiro do início da lista de empréstimos.
 */
void load_loans(Loan *loan_head);

#endif
