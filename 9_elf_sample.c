#include <stdio.h>
#include <sys/time.h>
#include <time.h>

static void Return();
static void Return2();
static void Return3();
static void Return4();

int main (int argc, char **argv){

#ifdef RETURN_1
    printf("running Return\n");
    Return();
#endif

#ifdef RETURN_2
    printf("running Return2 fun\n");
    Return2();
#endif

#ifdef RETURN_3
    printf("running Return3 fun\n");
    Return3();
#endif

#ifdef RETURN_4
    printf("running Return4 fun\n");
    Return4();
#endif
   return 0;
} 



void Return (){
    return;
}


void Return2 (){
    return 1;
}


void Return3 (){
    return -1;
}


void Return4 (){
    return 0;
}
