#include <stdio.h>
#include <sys/time.h>
#include <time.h>


#define MAX(x,y) (x)>(y)?(x):(y)

int getMfgMode(){

    return  -1;
}

int main (int argc, char **argv){

    int a=4,b=1;
    int c=0;
    char * vendor;
    int ret =0;
    if (argc = 1){
        strncpy(vendor , (char*)argv[1], sizeof(vendor));
        ret =  strncmp (vendor , "chwl" ,4);
        printf("ret = %d \r\n");
        if (!(strncmp (vendor , "chwl" ,4)==0) && !( strncmp (vendor , "ahsr" ,4) ==0) && (!(strncmp (vendor , "twcw" ,4)==0 )))
              printf("vendor error \r\n");
    } 
#if 0
    unsigned int delete_time = 1509;
    unsigned int ms = 498437;
    unsigned int sec =  1562752329;
    struct timeval bom;
    bom.tv_sec = sec;
    bom.tv_usec = ms;
    if(bom.tv_usec > delete_time %1000 * 1000){
        bom.tv_usec -= delete_time %1000*1000;
    }else {
        bom.tv_sec -= 1;
        bom.tv_usec = bom.tv_usec + 1000000 - delete_time %1000*1000;
    }
    bom.tv_sec -= delete_time /1000 ;

    printf("  chear:  %u, %u   --delete_time = %d \n",sec, ms, delete_time);

    printf("  chear:  %u, %u\n",bom.tv_sec, bom.tv_usec);

    
    printf ("mfg = %d\n",getMfgMode()) ;
    if (!getMfgMode()){
        printf (" yes \n");
    } else {
        printf(" no \n");
    }

GOTO1:
    printf("goto 1 \n");
GOTO2:
    printf("goto 2 \n");



//    printf(" %u,   %u\n",sec * 1000 , ms/1000);
//
//    c=a---b;
//    printf(" a---b = %d \n",c);
//
//    a=4,b=1;
//    c = 0;
//    c= a - --b;
//    printf(" a - -- b = %d \n",c);
//
//    a=4,b=1;
//    c= 0;
//    c = a-- -b ;
//    printf(" a-- - b =%d \n",c);
//
//
//    unsigned int ui_reg_val = 0;
//
//    ui_reg_val |= 0x1; 
//    printf (" ui_reg_val = %x \n", ui_reg_val);
// 
//    ui_reg_val &= ~0x2;
//    printf (" ui_reg_val = %x \n", ui_reg_val);
//
//    ui_reg_val &= ~(0xff<<16);
//    printf (" ui_reg_val = %x \n", ui_reg_val);
//
//    ui_reg_val |= (0xeb) <<16;   
//    printf (" ui_reg_val = %x \n", ui_reg_val);
//
//
//
//    ui_reg_val = 0x1;
//    ui_reg_val |= (0xeb);
//    printf ("1.  ui_reg_val = %x \n", ui_reg_val);
//
//    ui_reg_val = ui_reg_val << 16;
//    printf ("2.  ui_reg_val = %x \n", ui_reg_val);


    printf ("get result %d \n", MAX(1!=1,1!=2));
#endif    
    return 0;
}



