all:mk1 mk2

.PHONY:all clean


mk1:1_pointer_test.o
#	gcc -c 1_pointer_test.c	 
	gcc -o 1_pointer_test 1_pointer_test.o 
	ls -la ./
	./1_pointer_test.exe

mk2:2_callback_handler_test.o
	gcc -o 2_callback_handler_test 2_callback_handler_test.o 
	ls -la ./
	./2_callback_handler_test.exe


clean:
	rm -f main *.o *.exe
