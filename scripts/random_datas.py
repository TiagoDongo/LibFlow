from faker import Faker
import random
import json
import os

fake = Faker('pt-br')

def generate_random_book(book_id):
    return {
        "book_id": book_id,
        "book_name": fake.catch_phrase(),
        "book_autor": fake.name(),
        "book_edition": random.randint(1, 10),
        "book_available": random.choice(["Sim", "Nao"])
    }

def generate_random_user(user_id):
    return {
        "user_id": user_id,
        "user_name": fake.name(),
        "user_email": fake.email()
    }

def book_list_json(filename, num_books):
    books = [generate_random_book(i+1) for i in range(num_books)]
    with open(filename, "w", encoding="utf-8") as file:
        json.dump(books, file, indent=4, ensure_ascii=False)

def user_list_json(filename, num_users):
    users = [generate_random_user(i+1) for i in range(num_users)]
    with open(filename, "w", encoding="utf-8") as file:
        json.dump(users, file, indent=4, ensure_ascii=False)


def generate_multiple_lists(num_lists, num_items_per_list):
    os.makedirs("data", exist_ok=True)
    os.makedirs("data/users", exist_ok=True)

    for i in range(num_lists):
        books_filename = f"data/book_list_{i+1}.json"
        users_filename = f"data/users/user_list_{i+1}.json"
        book_list_json(books_filename, num_items_per_list)
        user_list_json(users_filename, num_items_per_list)

num_lists = 2
num_items_per_list = 20

generate_multiple_lists(num_lists,num_items_per_list)