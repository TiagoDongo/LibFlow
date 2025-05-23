#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include"database.h"

int id_generator(void *head, DataType type);

void *find_entity(void *head_list, int entityID, DataType type);

void generate_json_filename(char *filename, DataType type);

const char *get_type_prefix(DataType type);

void freedom(User user_head, Book book_head);

#endif