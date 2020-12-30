#include "stdio.h"

struct A{
	int a;
	char b;
	short c;
} struA;

struct B{
	char b;
	int a;
	short c';
} struB;


struct C{
    int a;
    char b;
    short c;
}__attribute__((aligned(4))) struC;

struct C{
    int a;
    char b;
    short c;
}__attribute__((aligned(8))) struC;


int main (int argc, char **argv){
	printf("sizeof(int) = %d , sizeof(char) = %d , sizeof(short) = %d", sizeof(int), sizeof(char),sizeof(short));
	
	printf("sizeof(A) = %d , sizof(B) = %d", sizeof(A), sizeof(B));
	
	return 0;
}