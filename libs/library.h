#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED

#include"database.h"

extern char last_loaded_file[100];
extern  int list_loaded; //0 = falso (não carregado), 1 = verdadeiro (carregado)

void regist_book(Book *book_head);

void delete_book(Book *book_head, int bookID);

void search_book(Book book_head, int bookID);

void list_books(Book book_head);

void save_list_books(Book book_head);

void load_list_book(Book *book_head);

void delete_list_book();

void updates_book(Book *book_head);

int book_id_generator(Book book_head);

void generate_json_book_filename(char *filename);

Book find_book(Book book_head, int bookID);
#endif