build/main: obj/main.o obj/library.o obj/cJSON.o obj/utils.o src/user.o
	gcc -o build/main obj/main.o obj/library.o obj/cJSON.o obj/utils.o src/user.o

obj/main.o: public/main.c src/library.h src/cJSON.h src/data_base.h src/utils.h src/user.o
	gcc -g -c public/main.c -o obj/main.o

obj/library.o: public/modules/library.c src/library.h src/cJSON.h src/data_base.h src/utils.h
	gcc -g -c public/modules/library.c -o obj/library.o

obj/user.o: public/modules/user.c src/user.h src/utils.h src/cJSON.h src/data_base
	gcc -g -c public/modules/user.c -o obj/user.o

obj/utils.o: public/modules/utils.c src/utils.h src/cJSON.h src/data_base.h 
	gcc -g -c public/modules/utils.c -o obj/utils.o

obj/cJSON.o: public/modules/cJSON.c src/cJSON.h
	gcc -g -c public/modules/cJSON.c -o obj/cJSON.o

run:
	./build/main

clean:
	rm -f obj/*.o build/main

wclean:
	if exist obj\*.o del /Q obj\*.o
	if exist build\main.exe del /Q build\main.exe
	if exist data\book_lists\*.json del /Q data\book_lists\*.json
	if exist data\user_lists\*.json del /Q data\user_lists\*.json

scripts:
	python scripts/library_analytics.py
	python scripts/random_datas.py
	python scripts/validate_jsons.py