#include <sys/types.h>
#include <sys/file.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

#define LOCK_FILE "/var/lock/myLock/"

int32 singleton(void);


int main(int argc, char *argv[]) {

    if(singleton() ) {
        printf("hi_appm is running.\n");
        return -1;
    }



    return 0;
}



int32 singleton(void) {
    int32 i_rv; 
    int32 i_fd; 
 
    i_fd = open(LOCK_FILE, O_WRONLY|O_CREAT);
    i_rv = flock(i_fd, LOCK_EX|LOCK_NB);
    if (i_rv == -1) 
    {
//        hi_os_close(i_fd);
    }

    return i_rv; 
}

