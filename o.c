#include "o.h"

#define gettime(name)	ull name; QueryPerformanceCounter((LARGE_INTEGER*) &name)
#define seconds(ta, tb)	((double) ((tb) - (ta)) / ctrfreq)

char* cs3333 = "3333";
HANDLE heap;
ull ctrfreq;
Queue* queues[5];

//Grid* r[RC_MAX];
//uint v = 0;

static Grid* init(uint sz)
{
	heap = GetProcessHeap();
	QueryPerformanceFrequency((LARGE_INTEGER*) &ctrfreq);
	
	for(uint i = 0; i < 5; i++)
	{
		queues[i] = mallocz(sizeof(Queue));
		queues[i] -> backing = malloc(sizeof(Grid*) * QUEUE_INCREMENT);
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

/*static void rc(Grid* g)
{
	if(v < RC_MAX)
	{
		for(uint i = 0; i < v; ++i)
		{
			if(eqgrid(g, r[i]))
			{
				rmgrid(g);
				return;
			}
		}
		r[v++] = g;
		
		for(uint y = 1; y < g->sz - 1; ++y)
		{
			for(uint x = 1; x < g->sz - 1; ++x)
			{
				if(is0(g, x, y))
				{
					Grid* gg = add(g, x, y);
					if (gg != NULL)
						rc(gg);
				}
			}
		}
	}
	else
		rmgrid(g);
}*/

static void bf(Grid* g)
{
	
}

int main(int argc, char** argv)
{
	bf(init(argc > 1 ? atoi(argv[1]) : 13u));
	
	uint i;
	for(i = 0; i < v; i++)
		print(r[i], cycstr(r[i]));

	return 0;
}
