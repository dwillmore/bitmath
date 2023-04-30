#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint64_t transpose64R(uint64_t a)
{
	uint64_t ta;
    	ta = ((a & 0xF0F0F0F000000000) >> 36) | 
	     ((a & 0x000000000F0F0F0F) << 36) | 
	      (a & 0x0F0F0F0FF0F0F0F0);
	ta = (ta & 0x3333CCCC3333CCCC) |
	    ((ta & 0xCCCC0000CCCC0000) >> 18) |
	    ((ta & 0x0000333300003333) << 18);
    	ta = (ta & 0x55AA55AA55AA55AA) | 
	    ((ta & 0xAA00AA00AA00AA00) >> 9) | 
	    ((ta & 0x0055005500550055) << 9);
   	return(ta);
}

uint64_t transpose64L(uint64_t a)
{
	uint64_t ta;
    	ta = ((a & 0x0F0F0F0F00000000) >> 28) | 
	     ((a & 0x00000000F0F0F0F0) << 28) | 
	      (a & 0xF0F0F0F00F0F0F0F);
	ta = (ta & 0xCCCC3333CCCC3333) |
	    ((ta & 0x3333000033330000) >> 14) |
	    ((ta & 0x0000CCCC0000CCCC) << 14);
    	ta = (ta & 0xAA55AA55AA55AA55) | 
	    ((ta & 0x5500550055005500) >> 7) | 
	    ((ta & 0x00AA00AA00AA00AA) << 7);
   	return(ta);
}

uint64_t transpose32R(uint64_t a)
{
	uint32_t ah, al;
	uint32_t ta, tb;
	uint64_t ret;

	ah = (a >> 32) & 0xFFFFFFFF;
	al = a & 0xFFFFFFFF;

	ta= (ah & 0x0F0F0F0F)       | ((al & 0x0F0F0F0F) << 4);
	tb=((ah & 0xF0F0F0F0) >> 4) |  (al & 0xF0F0F0F0);
	ta=(ta & 0x3333CCCC) | 
	  ((ta & 0xCCCC0000) >> 18) | 
	  ((ta & 0x00003333) << 18);
	tb=(tb & 0x3333CCCC) | 
	  ((tb & 0xCCCC0000) >> 18) | 
	  ((tb & 0x00003333) << 18);
	ta=(ta & 0x55AA55AA) | 
	  ((ta & 0xAA00AA00) >>  9) | 
	  ((ta & 0x00550055) <<  9);
	tb=(tb & 0x55AA55AA) | 
	  ((tb & 0xAA00AA00) >>  9) | 
	  ((tb & 0x00550055) <<  9);
	ret=((uint64_t)ta << 32) | tb;
	return(ret);
}

uint64_t transpose32L(uint64_t a)
{
	uint32_t ah, al;
	uint32_t ta, tb;
	uint64_t ret;

	ah = (a >> 32) & 0xFFFFFFFF;
	al = a & 0xFFFFFFFF;

	ta= (ah & 0xF0F0F0F0)       | ((al & 0xF0F0F0F0) >> 4);
	tb=((ah & 0x0F0F0F0F) << 4) |  (al & 0x0F0F0F0F);
	ta=(ta & 0xCCCC3333) | 
	  ((ta & 0x33330000) >> 14) | 
	  ((ta & 0x0000CCCC) << 14);
	tb=(tb & 0xCCCC3333) | 
	  ((tb & 0x33330000) >> 14) | 
	  ((tb & 0x0000CCCC) << 14);
	ta=(ta & 0xAA55AA55) | 
	  ((ta & 0x55005500) >>  7) | 
	  ((ta & 0x00AA00AA) <<  7);
	tb=(tb & 0xAA55AA55) | 
	  ((tb & 0x55005500) >>  7) | 
	  ((tb & 0x00AA00AA) <<  7);
	ret=((uint64_t)ta << 32) | tb;
	return(ret);
}

void main()
{
	uint64_t a= 0xff00000000000000;

	printf("a=0x%016lX\n", a);
	for(int x=63; x>=0; x--)
		printf("%c%s", a&((uint64_t)1<<x)?'1':'0', x&7?"":"\n");

	a=transpose64L(a);

	printf("a=0x%016lX\n", a);
	for(int x=63; x>=0; x--)
		printf("%c%s", a&((uint64_t)1<<x)?'1':'0', x&7?"":"\n");

	exit(0);
}
