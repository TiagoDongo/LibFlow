#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include"data_base.h"

void regist_user(user *user_head);

void delete_user(user *user_head);

void search_user(user user_head);

void list_users(user user_head);

void save_list_user(user user_head);

void load_list_user(user *user_head);

void delete_list_user();

void update_user(user *user_head);

void load_all_users_list(user *user_head);

#endif