#include "o.h"

static Grid* placet(Grid* g, uint o, uint x, uint y)
{
	Grid* gg = cpgrid(g);
	++gg -> grid[x][y];
	gg -> area += 4;
	gg -> peri += 8;
	gg -> surfarea += 3;
	gg -> cycstrlen += 4;
	
	switch(o)
	{
		case NORTH:
			++gg -> grid[x][y - 1];
			if(y == gg -> bounds.n) --gg -> bounds.n;
			else if(y == gg -> bounds.n - 1) gg -> bounds.n -= 2;
			goto ns;
		
		case SOUTH:
			++gg -> grid[x][y + 1];
			if(y == gg -> bounds.s) ++gg -> bounds.s;
			else if(y == gg -> bounds.s + 1) gg -> bounds.s += 2;
			goto ns;
		
		case EAST:
			++gg -> grid[x + 1][y];
			if(x == gg -> bounds.e) ++gg -> bounds.e;
			else if(x == gg -> bounds.e + 1) gg -> bounds.e += 2;
			goto ew;
		
		case WEST:
			++gg -> grid[x - 1][y];
			if(x == gg -> bounds.w) --gg -> bounds.w;
			else if(x == gg -> bounds.w - 1) gg -> bounds.w -= 2;
			goto ew;
	}
	
ns:++gg -> grid[x - 1][y];
	++gg -> grid[x + 1][y];
	if(x == gg -> bounds.e) ++gg -> bounds.e;
	if(x == gg -> bounds.w) --gg -> bounds.w;
	return gg;
	
ew:++gg -> grid[x][y - 1];
	++gg -> grid[x][y + 1];
	if(y == gg -> bounds.n) --gg -> bounds.n;
	if(y == gg -> bounds.s) ++gg -> bounds.s;
	return gg;
}
