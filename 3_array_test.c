#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (){
    int a[5] = {0};
    int i;
    for (i = 1 ;i <= 5 ; i++)
        a[i] = i*2;

    for (i = 1 ;i <= 5 ; i++)
        printf(" a[%d] = %d  \n",i, a[i]);

    /* 'str1[]' working fine , but '*str' not work, 
     * because '*str' did not malloc , it just point on stack, can not change any think within it.
     */
    char *str = "hellow the name";
    char str1[] = "0x30 0x30 0x30 0x30 0x30 0x30 0x30 0x30 0x33 0x37";
    char *p;
    p = NULL;  
    p = strtok(str1, " ");   
    while(p){
        printf("p= %s\n",p);
        p = strtok(NULL, " ");
    }

    /* compile success, but can not run */
    char *result = NULL;
    result = strtok(str, " ");
    while( result != NULL )
    {
        puts(result);
        result = strtok(NULL, " ");
    }
    printf("Program Finished\n\n");
    return 0;
}
