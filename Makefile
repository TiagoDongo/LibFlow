build/main: obj/main.o obj/library.o obj/cJSON.o obj/utils.o obj/user.o
	gcc -o build/main obj/main.o obj/library.o obj/cJSON.o obj/utils.o obj/user.o

obj/main.o: public/main.c src/library.h src/cJSON.h src/data_base.h src/utils.h src/user.h
	gcc -g -c public/main.c -o obj/main.o

obj/library.o: public/modules/library.c src/library.h src/cJSON.h src/data_base.h src/utils.h
	gcc -g -c public/modules/library.c -o obj/library.o

obj/user.o: public/modules/user.c src/user.h src/utils.h src/cJSON.h src/data_base.h
	gcc -g -c public/modules/user.c -o obj/user.o

obj/utils.o: public/modules/utils.c src/utils.h src/cJSON.h src/data_base.h
	gcc -g -c public/modules/utils.c -o obj/utils.o

obj/cJSON.o: public/modules/cJSON.c src/cJSON.h
	gcc -g -c public/modules/cJSON.c -o obj/cJSON.o

run: build/main
	./build/main

random_data: scripts/random_datas.py
	python scripts/random_datas.py

clean_windows:
	@if exist obj\*.o del /Q obj\*.o
	@if exist build\main.exe del /Q build\main.exe
	@if exist data\book_lists\*.json del /Q data\book_lists\*.json
	@if exist data\user_lists\*.json del /Q data\user_lists\*.json

clean_linux:
	rm -f obj/*.o build/main; 
	rm -f data/book_lists/*.json data/user_lists/*.json;

create_dirs:
	@if not exist build mkdir build
	@if not exist data mkdir data
	@if not exist obj mkdir obj
	@if not exist data\user_lists mkdir data\user_lists
	@if not exist data\book_lists mkdir data\book_lists

help:
	@echo "Makefile for Library Management System"
	@echo "Usage:"
	@echo "  make                - Build the project"
	@echo "  make run            - Run the project"
	@echo "  make clean_windows          - Clean object files and executable(windows)"
	@echo "  make clean_linux          - Clean object files and executable(linux)"
	@echo "  make random_data  - Generate random JSON data(for books and users)"
	@echo "  make create_dirs    - Create necessary directories"
	@echo "  make help           - Show this help message"