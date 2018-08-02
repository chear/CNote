all:mk1

mk1:
	gcc -c 1_pointer_test.c	 
	gcc -o 1_pointer_test 1_pointer_test.o 
	ls -la ./
	./1_pointer_test.exe


clean:
	rm -f main *.o *.exe
