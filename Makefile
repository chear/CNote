.PHONY:all clean
CFLAGS=-ansi -Wall -pedantic -std=c99 
LFLAGS=-lm 
CC=gcc

%.o:%.c
	$(CC) $(CFLAGS) -o %@ -c %<

all:1_

1_:1_pointer_test.o
	$(CC) $(CFLAGS) -o 1_pointer_test 1_pointer_test.o

1_pointer_test.o:1_pointer_test.c
	$(CC) $(CFLAGS) -c 1_pointer_test.c



#all:mk1 mk2
#
#mk1:1_pointer_test.o
#	gcc -std=c99 -c 1_pointer_test.c 
#	gcc -o 1_pointer_test 1_pointer_test.o 
##	./1_pointer_test.exe
#	chmod 777 ./1_pointer_test
#	./1_pointer_test
#
#mk2:2_callback_handler_test.o
#	gcc -o 2_callback_handler_test 2_callback_handler_test.o 
#	ls -la ./
#	./2_callback_handler_test.exe
#
#

clean:
	rm -f main *.o *.exe *.exe.stackdump  1_pointer_test
