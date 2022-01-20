#include <stdio.h>
#include <pthread.h>
#include "header.h"


handler_t  *handler = &goHandler;
char flag = 0x00;

void* callback_thread(void *p1)//此处用的是一个线程
{
    //do something
    handler_t* p = (handler_t*)p1 ;
    while(1)
    {
        printf("GetCallBack print! \n");
        sleep(3);//延时3秒执行callback函数
        p->callback(p->a);//函数指针执行函数，这个函数来自于应用层B
	
        /*
		  if (timeHandler && (( get_timer(0) - timeStart ) > timeDelta)) {
              thand_f *x;                                             
              x = timeHandler;                                                                                                          
              timeHandler = (thand_f *)0;                             
              (*x)();                                                 
        
          }           
		*/
		
    }
}


//留给应用层B的接口函数
extern SetCallBackFun(int a, DoHandler callback)
{
    printf("SetCallBackFun print! \n");
    handler_t *p = malloc(sizeof(handler_t)) ;
    p->a  = 10;
    p->callback = callback;

    //创建线程
    pthread_t thing1;
    pthread_create(&thing1,NULL,callback_thread,(void *) p);
    pthread_join(thing1,NULL);
    
}


void fCallBack(int a)       // 应用者增加的函数，此函数会在A中被执行
{
    //do something
    printf("a = %d\n",a);
    printf("fCallBack print! \n");
}


int doHandler(){

commmon:
    flag = 1;
    printf("goto common flag!\n");


    if ( !flag ) {
        printf("flag its null !!!\n");

    }
}



int main (int argc, char **argv){
    SetCallBackFun(4,fCallBack);
    return 0;
}

