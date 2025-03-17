import json
import os

def validate_json_files(directory):
    if not os.path.exists(directory):
        print(f"❌ Diretório não encontrado: {directory}")
        return

    for filename in os.listdir(directory):
        if filename.endswith(".json"):
            filepath = os.path.join(directory, filename)
            try:
                with open(filepath, "r", encoding="utf-8") as file:
                    data = json.load(file)
                    # Validação básica de estrutura (opcional)
                    if isinstance(data, list):
                        print(f"✅ {filename}: JSON válido (lista com {len(data)} itens)")
                    else:
                        print(f"⚠️  {filename}: JSON válido, mas não é uma lista")
            except json.JSONDecodeError as e:
                print(f"❌ {filename}: Erro de sintaxe JSON (linha {e.lineno})")
            except UnicodeDecodeError:
                print(f"❌ {filename}: Codificação inválida (use UTF-8)")
            except Exception as e:
                print(f"❌ {filename}: Erro inesperado - {str(e)}")

# Uso seguro
if __name__ == "__main__":
    validate_json_files("data/book_lists")
    validate_json_files("data/user_lists")