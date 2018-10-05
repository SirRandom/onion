#include "o.h"

void qAdd(Queue* q, Grid* g)
{
	if(q -> len == q -> cap)
	{
		q -> tail = q -> cap;
		q -> head = 0;
		q -> backing = realloc(q -> backing, q -> cap *= 2);
	}
	
	q -> backing[q -> tail++] = g;
}

Grid* qGet(Queue* q)
{
	if(q -> head == q -> tail)
		return NULL;
	
	Grid* g = q -> backing[head];
	q -> backing[q -> head] = NULL;
	if(++q -> head > q -> cap) q -> head = 0
	q -> len--;
	return g;
}
