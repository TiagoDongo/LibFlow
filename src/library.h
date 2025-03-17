#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED

#include"data_base.h"

void regist_book(book *book_head);

void delete_book(book *book_head);

void search_book(book book_head);

void list_books(book book_head);

void save_list_books(book book_head);

void load_list_book(book *book_head);

void delete_list_book();

void updates_book(book *book_head);

void load_all_book_lists(book *book_head);

#endif