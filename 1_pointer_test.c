#include <stdio.h>
#include "1_pointer_test.h"

#define MAX_LEN 10
unsigned char *RxPacket[MAX_LEN];

static MultiBoot_T globalMultiBoot;
MultiBoot_T *privMultiBoot = &globalMultiBoot;

int main (int argc, char **argv){
    unsigned char id[4]={0x00,0x00,0x00,0x14}  ;
    unsigned char *base = &id;            
    unsigned long *result = base+3;
    unsigned long val = *(char*)base<24 | *(char*)(base+1)<<16 | *(char*)(base+2)<<8 | *(char*)(base+3);
    unsigned long val2= *((long*)base);
    
    unsigned long *val3 = (long *)base;
    unsigned long val4 = 0x10;


#if 1
    for(int i=0;i<MAX_LEN;i++){
        RxPacket[i] = NULL;
    }
#endif


    setPacket(20,base+1);

    printf("\n starting! ");
    printf("\n base = %d" , *(char*)base);
    printf("\n base + 1 = %d" , *((char*)base + 1));
    printf("\n base + 2 = %d" , *((char*)base + 2));
    printf("\n base + 3 = %d" , *((char*)base + 3));
    printf("\n result = 0x%x" , *result); 
    printf("\n val  = %d " , val); 
    printf("\n val2 = %d ", val2);

    printf("\n base=>val= %d , val3=>val = %d ", *base,*val3);
    printf("\n base=>addr= %p , val3=>addr = %p ", base,val3);
    printf("\n base=>size= %d , val3=>size = %d ", sizeof(base) , sizeof(val3));
    printf("\n val4 %x , %x ", val4, &val4);

    return 0 ;
}



int setPacket(int num, volatile unsigned char *addr){
    RxPacket[num] = addr;
    return 0;
}
