dun_program: main.o gen_dun.o 
	gcc main.o gen_dun.o -o dun_program

main.o: main.c dun_utils.h
	gcc -Werror -Wall -ggdb main.c -c

gen_dun.o: gen_dun.c dun_utils.h
	gcc -Wall -Werror -ggdb gen_dun.c -c

clean:
	rm *.o dun_program