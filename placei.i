#include "o.h"

#define isOobY(g, y)		(y >= g -> sz)
#define isOobX(g, x)		(x >= g -> sz)

static Grid* placei(Grid* g, uint o, uint x, uint y)
{
	Grid* gg = cpgrid(g);
	++gg -> grid[x][y];
	gg -> area += 2;
	
	switch(o)
	{
		case NORTH:
			++gg -> grid[x][y - 1];
			if(y == gg -> bounds.n) --gg -> bounds.n;
			if(isOobY(g, y + 2) || is_0(gg, x, y + 2))
				goto fwd;
			goto ret;
		
		case SOUTH:
			++gg -> grid[x][y + 1];
			if(y == gg -> bounds.s) ++gg -> bounds.s;
			if(isOobY(g, y - 2) || is_0(gg, x, y - 2))
				goto fwd;
			goto ret;
		
		case EAST:
			++gg -> grid[x + 1][y];
			if(x == gg -> bounds.e) ++gg -> bounds.e;
			if(isOobX(g, x + 2) || is_0(gg, x + 2, y))
				goto fwd;
			goto ret;
		
		case WEST:
			++gg -> grid[x - 1][y];
			if(x == gg -> bounds.w) --gg -> bounds.w;
			if(isOobX(g, x - 2) || is_0(gg, x - 2, y))
				goto fwd;
			goto ret;
	}
fwd:
	++gg -> surfarea;
ret:
	return gg;
}
