/**
 * @file client.h
 * @brief Funções para gerenciamento de usuários (clientes) do sistema.
 */

#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include"database.h"

/**
 * @brief Registra um novo usuário na lista
 * @param user_head Ponteiro para o ponteiro do início da lista de usuários
 */
void regist_user(User *user_head);

/**
 * @brief Remove um usuário na lista pelo ID
 * @param user_head Ponteiro para o ponteiro do início da lista de usuários
 * @param userID ID do usuário a ser removido
 */
void delete_user(User *user_head, int userID);

/**
 * @brief Salva a lista de usuários em um arquivo JSON.
 * @param user_head Inicio da lista de usuários.
 */
void save_list_user(User user_head);

/**
 * @brief Carrega uma lista de usuários de um arquivo JSON
 * @param user_head Ponteiro para o ponteiro do início da lista de usuários
 */
void load_list_user(User *user_head);

#endif