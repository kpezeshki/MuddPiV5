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
    while (1) 
    {
			i = i + 1;
			*(int *)0x20000008 = 1;
    }
		return 0;
}