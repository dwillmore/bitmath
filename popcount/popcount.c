#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint32_t popcount64(uint64_t a)
{
	uint64_t tmp;

	tmp = ((a   & 0xAAAAAAAAAAAAAAAA) >> 1) + 
	       (a   & 0x5555555555555555);
	tmp = ((tmp & 0xCCCCCCCCCCCCCCCC) >> 2) + 
	       (tmp & 0x3333333333333333);
	tmp = ((tmp & 0xF0F0F0F0F0F0F0F0) >> 4) +
	       (tmp & 0x0F0F0F0F0F0F0F0F);
	tmp = ((tmp & 0xFF00FF00FF00FF00) >> 8) +
	       (tmp & 0x00FF00FF00FF00FF);
	tmp = ((tmp & 0xFFFF0000FFFF0000) >> 16) +
	       (tmp & 0x0000FFFF0000FFFF);
	tmp = ((tmp & 0xFFFFFFFF00000000) >> 32) +
	       (tmp & 0x00000000FFFFFFFF);
	return((uint32_t)tmp);
}

uint32_t popcount32(uint32_t a)
{
	uint32_t tmp;

	tmp = ((a   & 0xAAAAAAAA) >> 1) + 
	       (a   & 0x55555555);
	tmp = ((tmp & 0xCCCCCCCC) >> 2) + 
	       (tmp & 0x33333333);
	tmp = ((tmp & 0xF0F0F0F0) >> 4) +
	       (tmp & 0x0F0F0F0F);
	tmp = ((tmp & 0xFF00FF00) >> 8) +
	       (tmp & 0x00FF00FF);
	tmp = ((tmp & 0xFFFF0000) >> 16) +
	       (tmp & 0x0000FFFF);
	return(tmp);
}

void main()
{
	uint64_t a = 0xffffffffffffffff;
	uint32_t b = 0xffffffff;
	uint32_t ret;

	printf("a=0x%016lX\n", a);
	for(int x=63; x>=0; x--)
		printf("%c%s", a&((uint64_t)1<<x)?'1':'0', x?"":"\n");

	ret = popcount64(a);

	printf("ret=%02d\n", ret);

	printf("\nb=0x%08X\n", b);
	for(int x=31; x>=0; x--)
		printf("%c%s", a&((uint64_t)1<<x)?'1':'0', x?"":"\n");

	ret = popcount32(b);

	printf("ret=%02d\n", ret);

	exit(0);
}
