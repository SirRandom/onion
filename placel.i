#include "o.h"

static Grid* placel(Grid* g, uint o, uint x, uint y)
{
	Grid* gg = cpgrid(g);
	++gg -> grid[x][y];
	gg -> ord += 3;
	gg -> edges += 4;
	gg -> fwdcells += 2;
	gg -> cycstrlen += 2;
	
	switch(o)
	{
		case NORTHEAST:
			++gg -> grid[x + 1][y];
			++gg -> grid[x][y - 1];
			if(y == gg -> bounds.n) --gg -> bounds.n;
			if(x == gg -> bounds.e) ++gg -> bounds.e;
			break;
		
		case SOUTHWEST:
			++gg -> grid[x - 1][y];
			++gg -> grid[x][y + 1];
			if(y == gg -> bounds.s) ++gg -> bounds.s;
			if(x == gg -> bounds.w) --gg -> bounds.w;
			break;
		
		case SOUTHEAST:
			++gg -> grid[x + 1][y];
			++gg -> grid[x][y + 1];
			if(y == gg -> bounds.s) ++gg -> bounds.s;
			if(x == gg -> bounds.e) ++gg -> bounds.e;
			break;
		
		case NORTHWEST:
			++gg -> grid[x - 1][y];
			++gg -> grid[x][y - 1];
			if(y == gg -> bounds.n) --gg -> bounds.n;
			if(x == gg -> bounds.w) --gg -> bounds.w;
			break;
	}
	
	return gg;
}
