#include <stdio.h>
#include "header.h"

#define MAX_LEN 10
unsigned char *RxPacket[MAX_LEN];
typedef unsigned int unint;

static MultiBoot_T globalMultiBoot;
MultiBoot_T *privMultiBoot = &globalMultiBoot;

int setPacket(int num, volatile unsigned char *addr);


#define TEST_1 0 
#define TEST_2 0
#define TEST_3 0 
int main (int argc, char **argv){

    const unint k = 4;
    /* 'const int *p = int const *p', 'const' symbol defines the value of this variable can not be changed  */
    const int *p1;
    int const *p2;
    const int * const pi;
    p1 = &k;
    p2 = &k;


//    /*
//     * Description for the pointer type and symbol priority within C
//     *
//     * 
//     * Ref:
//     * https://en.cppreference.com/w/c/language/operator_precedence
//     * https://en.wikipedia.org/wiki/Operators_in_C_and_C%2B%2B
//     */
//    int p;              // p is integer variable .
//    int *p;             // p is a pointer variable and point to a integaer .
//    int p[3];           // 首先从P 处开始,先与[]结合,说明P 是一个数组,然后与int 结合,说明数组里的元素是整型的,所以P 是一个由整型数据组成的数组
//    int *p[3];          // 首先从P 处开始,先与[]结合,因为其优先级比*高,所以P 是一个数组,然后再与*结合,说明数组里的元素是指针类型,然后再与int 结合,说明指针所指向的内容的类型是整型的,所以P 是一个由返回整型数据的指针所组成的数组
//    int (*p)[3];        // 首先从P 处开始,先与*结合,说明P 是一个指针然后再与[]结合(与"()"这步可以忽略,只是为了改变优先级),说明指针所指向的内容是一个数组,然后再与int 结合,说明数组里的元素是整型的.所以P 是一个指向由整型数据组成的数组的指针
//    int **p;            // 首先从P 开始,先与*结合,说是P 是一个指针,然后再与*结合,说明指针所指向的元素是指针,然后再与int 结合,说明该指针所指向的元素是整型数据.由于二级指针以及更高级的指针极少用在复杂的类型中,所以后面更复杂的类型我们就不考虑多级指针了,最多只考虑一级指针.
//    int p(int);         // 从P 处起,先与()结合,说明P 是一个函数,然后进入()里分析,说明该函数有一个整型变量的参数,然后再与外面的int 结合,说明函数的返回值是一个整型数据
//    int (*p)(int);      // 从P 处开始,先与指针结合,说明P 是一个指针,然后与()结合,说明指针指向的是一个函数,然后再与()里的int 结合,说明函数有一个int 型的参数,再与最外层的int 结合,说明函数的返回类型是整型,所以P 是一个指向有一个整型参数且返回类型为整型的函数的指针
//    int *(*p(int))[3];  //可以先跳过,不看这个类型,过于复杂从P 开始,先与()结合,说明P 是一个函数,然后进入()里面,与int 结合,说明函数有一个整型变量参数,然后再与外面的*结合,说明函数返回的是一个指针,,然后到最外面一层,先与[]结合,说明返回的指针指向的是一个数组,然后再与*结合,说明数组里的元素是指针,然后再与int 结合,说明指针指向的内容是整型数据.所以P 是一个参数为一个整数据且返回一个指向由整型指针变量组成的数组的指针变量的函数.


#if (TEST_1)
    /*
     * 
     */
    unsigned char id[4]={0x00,0x00,0x00,0x14}  ;
    unsigned char *base = &id;            
    unsigned long *result = base+3;
    unsigned long val = *(char*)base<24 | *(char*)(base+1)<<16 | *(char*)(base+2)<<8 | *(char*)(base+3);
    unsigned long val2= *((long*)base);
    
    unsigned long *val3 = (long *)base;
    unsigned long val4 = 0x10;

        
    privMultiBoot->dbgLevel = 1;
    MSG("find", "tab" );            
#if 1
    for(int i=0;i<MAX_LEN;i++){
        RxPacket[i] = NULL;
    }
#endif

    setPacket(5,base+1);

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
#endif

#if (TEST_2)
    /*
     * Test 2
     *  '&a' equal '**a'
     */
    int a[] = {1,2,3,4,5,6};
    int *ptr=(int*)(&a +1) ;
    printf (" %d , %d \n", *(a+1),*(ptr-1));
#endif


#if TEST_3
    int val = 0;
    int *p;
    val = p;

#endif
    return 0 ;
}



int setPacket(int num, volatile unsigned char *addr){
    RxPacket[num] = addr;
    return 0;
}
