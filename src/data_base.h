#ifndef DATA_BASE_H_INCLUDED
#define DATA_BASE_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<dirent.h>

/**
 * @brief Estrutura de dados para armazenar informações sobre livros
 * @param *book Tipo de dado que representa um livro na biblioteca.
 */
typedef struct library {
    int book_id;
    char book_name[100];
    char book_autor[100];
    int book_edition;
    int book_available;
    struct library *next;
} *book;

/**
 * @brief Estrutura de dados para armazenar informações sobre usuários 
 * @param *user Tipo de dado que representa um usuário no sistema.
 */
typedef struct users {
    int user_id;
    char user_name[100];
    char user_email[100];
    char user_course[100];
    int user_phone;
    struct users *next;
} *user;

typedef struct transations{
    book book_id;
    user user_id;
    char loan_date[12];
    char devolution_date[12];
    int taxes;
    struct transations *next;
} *loans;

#endif