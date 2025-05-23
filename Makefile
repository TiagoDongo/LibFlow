SRC = src/*.c src/modules/*.c
INCLUDES = -Ilibs

all: build/main

build/main: $(wildcard $(SRC))
	@gcc -o build/main $(SRC) $(INCLUDES)

run: dirs build/main
	@cls || clear
	@./build/main

script:
	@python scripts/random_datas.py

dirs:
	-@mkdir build
	-@mkdir data
	@python -c "import os; os.makedirs(os.path.join('data', 'users'), exist_ok=True)"

clean:
	-@if exist data\*.json del /q data\*.json || rm -f data/*.json
	-@if exist build\main.exe del /q build\main.exe || rm -f build/main
	-@if exist data rmdir /s /q data || rm -rf data
	-@if exist build rmdir /s /q build || rm -rf build

help:
	@echo "Makefile do Libflow"
	@echo "Como Usar:"
	@echo "make 			- Compila o projeto"
	@echo "make run 		- Compila e Executa o projeto"
	@echo "make scripts 		- Executa os scripts python da pasta scripts"
	@echo "make dirs 		- Cria os diretorios necessarios"
	@echo "make clean" 		- Deleta o executavel e os JSONs bem como seus diretorios
	@echo "make help 		- Mostra esta mensagem"