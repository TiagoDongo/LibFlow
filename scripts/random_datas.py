import json
import random
import os
from faker import Faker

fake = Faker('pt-BR')

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
        "user_email": fake.email(),
        "user_phone": fake.phone_number(),
        "user_course": fake.random_element(elements=("Engenharia", "Medicina", "Direito", "Administracao", "Ciencia da Computacao","Arquitetura"))
    }

def random_book_json(filename, num_books):
    books = [generate_random_book(i + 1) for i in range(num_books)]
    with open(filename, "w", encoding="utf-8") as file:
        json.dump(books, file, indent=4, ensure_ascii=False)
    print(f"Arquivo '{filename} gerado com sucesso!")

def random_user_json(filename, num_users):
    users = [generate_random_user(i + 1) for i in range(num_users)]
    with open(filename, "w", encoding="utf-8") as file:
        json.dump(users, file, indent=4, ensure_ascii=False)
    print(f"Arquivo '{filename}' gerado com sucesso!")

def generate_multiple_lists(num_lists, num_books_per_list, num_users_per_list):
    if not os.path.exists("data"):
        os.makedirs("data")
        print("Pasta 'data' criada.")

    if not os.path.exists("data/book_lists"):
        os.makedirs("data/book_lists")
        print("Pasta 'book_lists' criada.")

    if not os.path.exists("data/user_lists"):
        os.makedirs("data/user_lists")
        print("Pasta 'user_lists' criada.")

    for i in range(num_lists):
        books_filename = f"data/book_lists/random_books_list_{i + 1}.json"
        generate_random_book(books_filename, num_books_per_list)

        users_filename = f"data/user_lists/random_users_list_{i + 1}.json"
        generate_random_user(users_filename, num_users_per_list)

num_lists = 3  
num_books_per_list = 5  
num_users_per_list = 5 

generate_multiple_lists(num_lists, num_books_per_list, num_users_per_list)