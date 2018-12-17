#include "o.h"

void qAdd(Queue* q, Grid* g)
{
#if DEBUG
	printf("QADD\n");
	
	if(g > 0xFFFFFFFF)
	{
		int a = 1;
		printf("!! QUEUEADD PANIC: STRANGE GRID !!");
		while(a) Sleep(500);
	}
#endif
	
	for(uint i = 0; i < q -> cap; i++)
	{
		if(q -> backing[i] != NULL && eqgrid(g, q -> backing[i]))
		{
#if DEBUG
			printf("!! REMOVING GRID %p !!", g);
#endif
			rmgrid(g);
			return;
		}
	}
	
#if DEBUG
	printf("After For loop\n");
#endif
	
	if(q -> len == q -> cap)
	{
#if DEBUG
		printf("In the IF statement: \nhead=%u tail=%u len=%u cap=%u\n", q -> head, q -> tail, q -> 
len, q -> cap);
#endif
		q -> tail = q -> cap;
		q -> head = 0;
		q -> cap *= 2;
		q -> backing = reallocz(q -> backing, sizeof(Grid*) * q -> cap);
	}
	
#if DEBUG
	printf("AFTER the IF statement");
#endif
	
	q -> backing[q -> tail++] = g;
	if(q -> tail >= q -> cap) q -> tail = 0;
	q -> len++;
	++v;
}

Grid* qGet(Queue* q)
{
#if DEBUG
	printf("QGET\n");
#endif
	if(!q -> len)
		return NULL;
	
	/*if(q -> backing[q -> head] == 0xabababababababab)
	{
		paq();
		Sleep(INFINITE);
	}*/
	
	Grid* g = q -> backing[q -> head];
	q -> backing[q -> head] = NULL;
	if(++q -> head >= q -> cap) q -> head = 0;
	q -> len--;
	
	return g;
}
