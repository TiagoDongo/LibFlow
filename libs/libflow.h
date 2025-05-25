/**
 * @file libflow.h
 * @brief Funções principais de controle de menus e fluxo do sistema.
 */

#ifndef LIBFLOW_H_INCLUDED
#define LIBFLOW_H_INCLUDED

#include"database.h"

/**
 * @brief Libera toda a memória alocada para usuários e livros.
 * @param user_head Início da lista de usuários.
 * @param book_head Início da lista de livros.
 */
void freedom(User user_head, Book book_head);

/**
 * @brief Sub-Menu de gerenciamento de livros.
 * @param book_head Ponteiro para o ponteiro do início da lista de livros.
 */
void book_menu(Book *book_head);

/**
 * @brief Sub-Menu de gerenciamento de usuários.
 * @param user_head Ponteiro para o ponteiro do início da lista de usuários.
 */
void user_menu(User *user_head);

/**
 * @brief Menu principal do sistema.
 * @param book_head Ponteiro para o ponteiro do início da lista de livros.
 * @param user_head Ponteiro para o ponteiro do início da lista de usuários.
 */
void main_menu(Book *book_head, User *user_head);

#endif