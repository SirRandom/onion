#include "o.h"

Grid* cpgrid(Grid* s)
{
	Grid* d = malloc(sizeof(Grid));
	
	d -> cycstr = NULL;
	d -> cycstrlen = s -> cycstrlen;
	d -> grid = malloc(sizeof(byte*) * s -> sz);
	for(uint i = 0; i < s -> sz; ++i)
	{
		d -> grid[i] = malloc(sizeof(byte) * s -> sz);
		memcpy(d -> grid[i], s -> grid[i], sizeof(byte) * s -> sz);
	}
	
	d -> peri = s -> peri;
	d -> surfarea = s -> surfarea;
	d -> bounds.n = s -> bounds.n;
	d -> bounds.s = s -> bounds.s;
	d -> bounds.e = s -> bounds.e;
	d -> bounds.w = s -> bounds.w;
	d -> area = s -> area;
	d -> sz = s -> sz;
	return d;
}
