#include <sys/types.h> 
#include <sys/wait.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <errno.h> 
int main() { 
    pid_t pc, pr;       
    pc = fork(); 
    if ( pc < 0  ) /* 如果出错 */ 
    { 
        printf("create child prcocess error: %s\n", strerror(errno)); 
        exit(1); 
    } 
    else if ( pc == 0 ) /* 如果是子进程 */ 
    { 
        printf("I am child process with pid %d \n", getpid()); 
        sleep(3);/* 睡眠3秒钟 */ 
        exit(0); 
    } 
    else /* 如果是父进程 */ 
    { 
        printf("Now in parent process, pid = %d\n", getpid()); 
        printf("I am waiting child process to exit.\n"); 
        pr = wait(NULL); /* 在这里等待子进程结束 */ 
        if ( pr > 0  ) /*子进程正常返回*/ 
        {
            printf("I catched a child process with pid of %d\n", pr);

        } 
        else /*出错*/ 
        {
            printf("error: %s\n.\n", strerror(errno));

        } 
    } 
    exit(0); 
}


