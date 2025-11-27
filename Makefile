SRC = src/*.c src/modules/*.c
INCLUDES = -Ilibs
EXE = build/main

.PHONY: all run scripts script dirs clean help test

all: $(EXE)

$(EXE): dirs $(wildcard $(SRC))
	@gcc -o $(EXE) $(SRC) $(INCLUDES)

run: $(EXE)
	@cls || clear
	@./$(EXE)

scripts: dirs
	@pip install Faker
	@python scripts/random_datas.py

dirs:
	@python -c "import os; os.makedirs('build', exist_ok=True)"
	@python -c "import os; os.makedirs('data', exist_ok=True)"
	@python -c "import os; os.makedirs(os.path.join('data', 'users'), exist_ok=True)"
	@python -c "import os; os.makedirs(os.path.join('data', 'loans'), exist_ok=True)"

clean:
	-@if exist data\*.json del /q data\*.json || rm -f data/*.json
	-@if exist build\main.exe del /q build\main.exe || rm -f build/main
	-@if exist data rmdir /s /q data || rm -rf data
	-@if exist build rmdir /s /q build || rm -rf build

help:
	@echo "Makefile do Libflow"
	@echo "Como Usar:"
	@echo "make             - Compila o projeto"
	@echo "make run         - Compila e Executa o projeto"
	@echo "make scripts     - Executa os scripts python da pasta scripts"
	@echo "make dirs        - Cria os diretorios necessarios"
	@echo "make clean       - Deleta o executavel e os JSONs bem como seus diretorios"
	@echo "make help        - Mostra esta mensagem"

test: all
	@./$(EXE)