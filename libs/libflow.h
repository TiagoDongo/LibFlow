/**
 * @file libflow.h
 * @brief Funções principais de controle de menus e fluxo do sistema.
 */

#ifndef LIBFLOW_H_INCLUDED
#define LIBFLOW_H_INCLUDED

#include "database.h"

/**
 * @brief Libera toda a memória alocada para usuários e livros.
 * @param user_head Início da lista de usuários.
 * @param book_head Início da lista de livros.
 */
void freedom(User user_head, Book book_head);

/**
 * @brief Remove uma entidade (usuário ou livro) da lista encadeada.
 * @param head Ponteiro para o ponteiro do início da lista.
 * @param entityID ID da entidade a ser removida.
 * @param type Tipo da entidade (usuário ou livro).
 */
void delete_entity(void **head, int entityID, DataType type);

/**
 * @brief Busca e exibe uma entidade (usuário ou livro) pelo ID.
 * @param head Ponteiro para o início da lista.
 * @param entityID ID da entidade a ser buscada.
 * @param type Tipo da entidade (usuário ou livro).
 */
void search_entity(void *head, int entityID, DataType type);

/**
 * @brief Lista todas as entidades (usuários ou livros) presentes na lista.
 * @param head Ponteiro para o início da lista.
 * @param type Tipo da entidade (usuário ou livro).
 */
void list_entities(void *head, DataType type);

/**
 * @brief Apaga um JSON de uma entidade (Livro, Usuario ou Empréstimo)
 * @param type Tipo da entidade (usuário, livro ou empréstimo).
 */
void delete_list(DataType type);

#endif