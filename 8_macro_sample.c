#include <stdio.h>
#include <stdlib.h>


/* mean of "(void)(&_x == &_y)" , used to make warning message when x and y with not same types.
 */
#define MAX(x,y) ({         \
        typeof(x) _x = x;   \
        typeof(y) _y = y;   \
        (void)(&_x == &_y); \
        x>y?x:y;            \
        })


#define offsetof(TYPE, MEMBER) ((size_t)&((TYPE *)0)->MEMBER) 
#define container_of(ptr,type, member) ({                           \
            const  typeof( ((type *)0)->member ) *__mptr = (ptr);   \
            (type *)( (char *)__mptr - offsetof(type,member) );    \
        })


struct Student {
    int age;
    int num;
    int math;
};

int main (int argc, char **argv){
    
    int i = 2;
    int j = 6;
    printf("max :%d \n", MAX(i,j));

    struct Student stu={20,10001,99} ;
    int *p = &stu.math;
    struct Student *stu_ptr = NULL;
    stu_ptr = container_of( p, struct Student ,math);

    printf ("%p \n",stu_ptr);
    printf ("age : %d \n", stu_ptr->age);
    printf ("num : %d \n", stu_ptr->num);

    return 0;
}
