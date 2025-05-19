#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>

/**
 * @file database.h
 * @brief Define estruturas de dados para armazenar informações de livros e usuários na biblioteca.
 */

/**
 * @struct library
 * @brief Estrutura para armazenar dados de um livro.
 *
 * Contém informações como ID, nome, autor, edição, disponibilidade e ponteiro para o próximo livro.
 */
typedef struct library {
    int book_id;                /**< Identificador único do livro */
    char book_name[100];        /**< Nome do livro */
    char book_autor[100];       /**< Autor do livro */
    int book_edition;           /**< Edição do livro */
    int book_available;         /**< Disponibilidade do livro (1 disponível, 0 emprestado) */
    struct library *next_book;  /**< Ponteiro para o próximo livro na lista */
}*Book;

#endif