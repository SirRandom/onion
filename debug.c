#include "o.h"

void pg(Grid* g)
{
	printf("Grid@%p: \"%s\"\n", g, (g -> cycstr)? g -> cycstr : "NULL");
	
	printf("\n   ");
	SetConsoleTextAttribute(hconout, 0x0C);
	for(uint i = 0; i < g -> sz; i++)
		printf("%d", i / 10);
	printf("\n   ");
	for(uint i = 0; i < g -> sz; i++)
		printf("%d", i % 10);
	printf("\n");
	SetConsoleTextAttribute(hconout, 0x07);
	for(uint y = 0; y < g -> sz; y++)
	{
		SetConsoleTextAttribute(hconout, 0x0C);
		printf("%2d ", y);
		SetConsoleTextAttribute(hconout, 0x07);
		for(uint x = 0; x < g -> sz; x++)
		{
			if(g -> grid[x][y])	SetConsoleTextAttribute(hconout, 0x0A);
			else						SetConsoleTextAttribute(hconout, 0x08);
			printf("%d", g -> grid[x][y]);
			SetConsoleTextAttribute(hconout, 0x07);
		}
		printf("\n");
	}
}

void pq(Queue* q)
{
	printf(
		"Queue %p\n"
		"  head %u   tail %u  cap %u  len %u\n\nGrids:\n",
		q, q -> head, q -> tail, q -> cap, q -> len
	);
	
	for(uint i = 0; i < q -> cap; i++)
	{
		if(i && i % 4 == 0)
			printf("\n");
		
		if(q -> backing[i])
			printf("   Grid %p", q -> backing[i]);
		else
			printf("   No Grid              ");
	}
	printf("\n\n");
}

void paq(void)
{
	for(int i = 0; i < 5; i++)
	{
		if(i == active_queue)
		{
			SetConsoleTextAttribute(hconout, 0x0A);
			printf(" [ ACTIVE QUEUE ] \n");
		}
		else
			SetConsoleTextAttribute(hconout, 0x08);
		pq(queues[i]);
		SetConsoleTextAttribute(hconout, 0x07);
	}
}
