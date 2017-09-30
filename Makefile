dun_program: characters.o gen_dun.o 
	gcc characters.o gen_dun.o -o dun_program

characters.o: characters.c dun_utils.h
	gcc -Werror -Wall -ggdb characters.c -c

distances.o: distances.c dun_utils.h
	gcc -Werror -Wall -ggdb distances.c -c

gen_dun.o: gen_dun.c dun_utils.h
	gcc -Wall -Werror -ggdb gen_dun.c -c

clean:
	rm *.o dun_program