/*
 * GccApplication1.c
 *
 * Created: 11/9/2018 10:41:16 PM
 * Author : kaveh
 */ 


//#include "sam.h"


int main(void)
{
    int i = 0;
    *(int *)0x20000000 = 1;
    *(int *)0x20000008 = 2;
    *(int *)0x2000000c = 3;
    for(i = 0; i < 10; i++) {
      *(int *)0x2000000e = i;
    }
}
