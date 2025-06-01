/**
 * @file utils.h
 * @brief Funções utilitárias para manipulação de listas e arquivos.
 */

#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include "database.h"

/**
 * @brief Gera um novo ID para entidade (livro ou usuário).
 * @param head Ponteiro para o início da lista.
 * @param type Tipo da entidade (livro ou usuário).
 * @return Novo ID gerado.
 */
int id_generator(void *head, DataType type);

/**
 * @brief Busca uma entidade pelo ID (livro ou usuário).
 * @param head_list Ponteiro para o início da lista.
 * @param entityID ID da entidade a ser buscada.
 * @param type Tipo da entidade.
 * @return Ponteiro para a entidade encontrada ou NULL.
 */
void *find_entity(void *head_list, int entityID, DataType type);

/**
 * @brief Gera um nome de arquivo JSON para salvar listas.
 * @param filename Buffer para armazenar o nome do arquivo gerado.
 * @param type Tipo da entidade.
 */
void generate_json_filename(char *filename, DataType type);

/**
 * @brief Retorna o prefixo do tipo para nomes de arquivos.
 * @param type Tipo da entidade.
 * @return Prefixo correspondente.
 */
const char *get_type_prefix(DataType type);

/**
 * @brief Solicita ao usuário um número inteiro validado.
 * @param prompt Mensagem exibida ao usuário para entrada de dados.
 * @return Valor inteiro inserido pelo usuário validade.
 */
int validated_int_input(const char *prompt);

#endif