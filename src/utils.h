#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include"data_base.h"

int book_id_generator(book book_head);

int user_id_generator(user user_head);

void generate_book_filename(char *file_name);

void generate_user_filename(char *file_name);

book find_book(book book_head, int bookID);

user find_user(user user_head, int userID);

#endif