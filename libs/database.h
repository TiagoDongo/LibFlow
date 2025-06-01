/**
 * @file database.h
 * @brief Define estruturas de dados e variáveis globais para o gerenciamento de livros e usuários em uma biblioteca.
 *
 * Este arquivo contém as definições das estruturas utilizadas para armazenar informações de livros e usuários,
 * além de variáveis globais para controle do estado do carregamento dos dados.
 */

#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#include<time.h>

/**
 * @var last_loaded_file
 * @brief Nome do último arquivo de dados carregado.
 */
extern char last_loaded_file[100];

/**
 * @var list_loaded
 * @brief Indica se a lista de dados foi carregada (0 = não carregada, 1 = carregada).
 */
extern int list_loaded;

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
    struct library *next;  /**< Ponteiro para o próximo livro na lista */
} *Book;

/**
 * @struct users
 * @brief Estrutura para armazenar dados de um usuário.
 *
 * Contém informações como ID, nome, e-mail e ponteiro para o próximo usuário.
 */
typedef struct users {
    int user_id;                /**< Identificador único do usuário */
    char user_name[100];        /**< Nome do usuário */
    char user_email[100];       /**< E-mail do usuário */
    struct users *next;         /**< Ponteiro para o próximo usuário na lista */
} *User;

/**
 * @enum DataType
 * @brief Enumeração para diferenciar tipos de dados
 */
typedef enum {
    TYPE_BOOK,  /**< Tipo livro */
    TYPE_USER,  /**< Tipo usuário */
    TYPE_LOAN,  /**< Tipo empréstimo */
} DataType;

/**
 * @struct Loan
 * @brief Estrutura para representar um empréstimo de livro
 * Contém informações sobre o livro emprestado, o usuario, datas de emprstimo/devolução e status.
 */
typedef struct loan {
    int loan_id;    /**< Identificador único do empréstimo */
    int user_id;    /**< Identificador do usuario que fez o empréstimo */
    int book_id;    /**< Identificador livro empréstado */
    char loan_date[11];    /**< Data de empréstimo (formato: YYYY-MM-DD) */
    int returned;   /**< Status: 1 = devolvido, 0 = em andamento*/
    struct loan *next;  /**< Ponteiro para o próximo empréstimo */
} *Loan;

#endif