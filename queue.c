#include "o.h"

void qAdd(Queue* q, Grid* g)
{
	if(q -> len == q -> cap)
	{
		q -> tail = q -> 0;
		q -> head = q -> cap;
		q -> backing = realloc(q -> backing, q -> cap *= 2);
	}
	
	// SUCH WORK NEEDS THIS FUNCTION
}

Grid* qGet(Queue* q)
{
	if(q -> head == q -> tail)
		return NULL;
	
	Grid* g = q -> backing[head];
	q -> backing[q -> head++] = NULL;
	q -> len--;
	return g;
	
	// SUCH MODULAR CHECKING ON HEAD NEEDS THIS FUNCTION
}
