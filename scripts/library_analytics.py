import json

def library_analytics(books_file, users_file):
    try:
        # Carrega livros
        with open(books_file, "r") as f:
            books = json.load(f)
        
        # Carrega usuários
        with open(users_file, "r") as f:
            users = json.load(f)

        stats = {
            "total_books": len(books),
            "available_books": sum(1 for b in books if b["book_available"] == "Sim"),
            "total_users": len(users)
        }

        print("📊 Estatísticas da Biblioteca:")
        for key, value in stats.items():
            print(f"{key.replace('_', ' ').title()}: {value}")

    except FileNotFoundError as e:
        print(f"❌ Arquivo não encontrado: {e.filename}")
    except json.JSONDecodeError:
        print("❌ Erro ao decodificar JSON. Verifique o formato do arquivo.")
    except KeyError as e:
        print(f"❌ Chave ausente no JSON: {e}")

# Uso (sem empréstimos)
if __name__ == "__main__":
    library_analytics(
        "data/book_lists/random_books_list_1.json",
        "data/user_lists/random_users_list_1.json"
    )