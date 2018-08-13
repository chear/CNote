
typedef struct {
	char name[4];
	int checksum;
    unsigned char dbgLevel;
}MultiBoot_T;

#define MSG( F, B...)    {\
if( privMultiBoot ->dbgLevel )\
    printf("%s [%d]: " F,  strrchr(__FILE__, '/')+1, __LINE__, ##B);\
}



typedef void (*DoHandler)(int a); //函数指针定义，后面可以直接使用 DoHandler ，方便
typedef struct handler_s{
    int a ;
    DoHandler callback;
}handler_t; 


static handler_t goHandler;




