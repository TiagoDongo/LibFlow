/**
 * @file library.h
 * @brief Funções para gerenciamento de livros da biblioteca.
 */

#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED

#include"database.h"

/**
 * @brief Registra um novo livro na biblioteca.
 * @param book_head Ponteiro para o ponteiro do início da lista de livros.
 */
void regist_book(Book *book_head);

/**
 * @brief Remove um livro da biblioteca pelo ID.
 * @param book_head Ponteiro para o ponteiro do início da lista de livros.
 * @param bookID ID do livro a ser removido.
 */
void delete_book(Book *book_head, int bookID);

/**
 * @brief Busca um livro pelo ID.
 * @param book_head Início da lista de livros.
 * @param bookID ID do livro a ser buscado.
 */
void search_book(Book book_head, int bookID);

/**
 * @brief Lista todos os livros cadastrados.
 * @param book_head Início da lista de livros.
 */
void list_books(Book book_head);

/**
 * @brief Salva a lista de livros em um arquivo JSON.
 * @param book_head Início da lista de livros.
 */
void save_list_books(Book book_head);

/**
 * @brief Carrega uma lista de livros de um arquivo JSON.
 * @param book_head Ponteiro para o ponteiro do início da lista de livros.
 */
void load_list_book(Book *book_head);

/**
 * @brief Deleta um arquivo de lista de livros.
 */
void delete_list_book();

/**
 * @brief Atualiza informações de um livro.
 * @param book_head Ponteiro para o ponteiro do início da lista de livros.
 */
void updates_book(Book *book_head);

#endif