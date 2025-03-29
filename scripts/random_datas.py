import json
import random
import os
from faker import Faker

fake = Faker('en')

def generate_random_book(book_id):
    return {
        "book_id": book_id,
        "book_name": fake.catch_phrase(),
        "book_autor": fake.name(),
        "book_edition": random.randint(1, 10),
        "book_available": random.choice(["Yes", "No"])
    }

def generate_random_user(user_id):
    return {
        "user_id": user_id,
        "user_name": fake.name(),
        "user_email": fake.email(),
        "user_phone": fake.phone_number(),
        "user_course": fake.random_element(elements=("Engineering", "Medicine", "Law", "Business Administration", "Computer Science","Architecture"))
    }

def random_book_json(filename, num_books):
    books = [generate_random_book(i + 1) for i in range(num_books)]
    with open(filename, "w", encoding="utf-8") as file:
        json.dump(books, file, indent=4, ensure_ascii=False)

def random_user_json(filename, num_users):
    users = [generate_random_user(i + 1) for i in range(num_users)]
    with open(filename, "w", encoding="utf-8") as file:
        json.dump(users, file, indent=4, ensure_ascii=False)
def generate_multiple_lists(num_lists, num_books_per_list, num_users_per_list):
    if not os.path.exists("data"):
        os.makedirs("data")

    if not os.path.exists("data/book_lists"):
        os.makedirs("data/book_lists")

    if not os.path.exists("data/user_lists"):
        os.makedirs("data/user_lists")

    for i in range(num_lists):
        books_filename = f"data/book_lists/random_books_list_{i + 1}.json"
        random_book_json(books_filename, num_books_per_list)

        users_filename = f"data/user_lists/random_users_list_{i + 1}.json"
        random_user_json(users_filename, num_users_per_list)

num_lists = 3  
num_books_per_list = 10  
num_users_per_list = 10 

generate_multiple_lists(num_lists, num_books_per_list, num_users_per_list)