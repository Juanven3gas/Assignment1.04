dun_program: characters.o gen_dun.o priority_queue.o
	gcc characters.o gen_dun.o priority_queue.o -o dun_program

characters.o: characters.c dun_utils.h priority_queue.h
	gcc -Werror -Wall -ggdb characters.c -c

distances.o: distances.c dun_utils.h
	gcc -Werror -Wall -ggdb distances.c -c

gen_dun.o: gen_dun.c dun_utils.h
	gcc -Wall -Werror -ggdb gen_dun.c -c

priority_queue.o: priority_queue.c priority_queue.h
	gcc -Wall -Werror -ggdb priority_queue.c -c

clean:
	rm *.o dun_program