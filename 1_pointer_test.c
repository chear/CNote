

/*
typeof struct{
	char name[4];
	int checksum;
}MultiBoot_T;
*/


int main (int argc, char **argv){
    char id[4]={0x00,0x00,0x00,0x14}  ;
    char *base = &id;    

    long *result = base+3;

    long val = *(char*)base<24 | *(char*)(base+1)<<16 | *(char*)(base+2)<<8 | *(char*)(base+3);

    printf("\n starting! ");
    printf("\n base = %d" , *(char*)base);
    printf("\n base + 1 = %d" , *((char*)base + 1));
    printf("\n base + 2 = %d" , *((char*)base + 2));
    printf("\n base + 3 = %d" , *((char*)base + 3));
    printf("\n result = 0x%x" , *result); 
    printf("\n val = %d " , val); 

    return 0 ;
}

