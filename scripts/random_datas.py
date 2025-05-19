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


def book_list_json(filename, num_books):
    books = [generate_random_book(i+1) for i in range(num_books)]
    with open(filename, "w", encoding="utf-8") as file:
        json.dump(books, file, indent=4, ensure_ascii=False)

def generate_multiple_lists(num_lists, num_items_per_list):
    if not os.path.exists("data"):
        os.makedirs("data")

    if not os.path.exists("data"):
        os.makedirs("data")

    for i in range(num_lists):
        books_filename = f"data/book_list_{i+1}.json"
        book_list_json(books_filename, num_items_per_list)

num_lists = 2
num_items_per_list = 20

generate_multiple_lists(num_lists,num_items_per_list)