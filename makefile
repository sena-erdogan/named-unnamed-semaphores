all:
	gcc -c -g hw3named.c -ansi -Wall -std=gnu99
	gcc -o hw3named hw3named.o -lm -Wall -lrt -lpthread
	gcc -c -g hw3unnamed.c -ansi -Wall -std=gnu99
	gcc -o hw3unnamed hw3unnamed.o -lm -Wall -lrt -lpthread

clean:
	rm -rf *o hw3named
	rm -rf *o hw3unnamed
