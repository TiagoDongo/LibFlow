#include"libflow.h"

char last_loaded_file[100] = "";
int list_loaded = 0;

int main() {
    Book book_head = NULL;
    User user_head = NULL;

    freedom(user_head, book_head);

    return 0;
}