#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include"database.h"

void regist_user(User *user_head);

void delete_user(User *user_head, int userID);

void save_list_user(User user_head);

void load_list_user(User *user_head);

#endif