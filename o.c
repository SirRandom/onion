#include "o.h"

#define gettime(name)		ull name; QueryPerformanceCounter((LARGE_INTEGER*) &name)
#define seconds(ta, tb)		((double) ((tb) - (ta)) / ctrfreq)
#define output_and_kill(x)	(print(x), rmgrid(x))

char* cs3333 = "3333";
HANDLE heap;
ull ctrfreq;
Queue* queues[5];
int running = 1;

static Grid* init(uint sz)
{
	heap = GetProcessHeap();
	QueryPerformanceFrequency((LARGE_INTEGER*) &ctrfreq);
	
	for(uint i = 0; i < 5; i++)
	{
		queues[i] = mallocz(sizeof(Queue));
		queues[i] -> backing = mallocz(sizeof(Grid*) * QUEUE_INCREMENT);
		queues[i] -> cap = QUEUE_INCREMENT;
	}
	
	Grid* g = malloc(sizeof(Grid));
	uint i;
	
	g -> cycstr = cs3333;
	g -> cycstrlen = 4;
	
	g -> grid = malloc(sizeof(byte*) * sz);
	for(i = 0; i < sz; g -> grid[i++] = mallocz(sizeof(byte) * sz));
	
	g -> peri = 12;
	g -> surfarea = 4;
	
	i = sz / 2;
	
	g -> bounds.n =
	g -> bounds.w = i - 1;
	g -> bounds.s =
	g -> bounds.e = i + 1;
	g -> area = 5;
	g -> sz = sz;
	
	g -> grid[i][i] =
	g -> grid[i + 1][i] =
	g -> grid[i - 1][i] =
	g -> grid[i][i + 1] =
	g -> grid[i][i - 1] = 1;
	
	return g;
}

static void bf(Grid* g)
{
	uint current = 0, p;
	Grid *gg, *ggg;
	
	qAdd(queues[current], g);
	while(running)
	{
		while(queues[current] -> len)
		{
			gg = qGet(queues[current]);
			
			for(uint scan_y = 1; scan_y < gg -> sz - 1; scan_y++)
				for(uint scan_x = 1; scan_x < gg -> sz - 1; scan_x++)
					if(ggg = add(gg, scan_x, scan_y, &p))
						qAdd(queues[(current + p) % 5], ggg);
			
			output_and_kill(gg);
		}
		
		current = (current + 1) % 5;
	}
	
	for(uint i = 0; i < 5; i++)
	{
		if(queues[i] -> len)
			while(queues[i] -> len)
				output_and_kill(qGet(queues[i]));
		
		free(queues[i] -> backing);
		free(queues[i]);
	}
}

int main(int argc, char** argv)
{
	bf(init(argc > 1 ? atoi(argv[1]) : 13u));
	return 0;
}
