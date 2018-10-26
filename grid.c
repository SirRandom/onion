#include <string.h>
#include "o.h"

Grid* cpgrid(Grid* s)
{
	Grid* d = malloc(sizeof(Grid));
	
	d -> cycstr = NULL;
	d -> cycstrlen = s -> cycstrlen;
	d -> grid = malloc(sizeof(byte*) * s -> sz);
	for(int i = 0; i < s -> sz; ++i)
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

void rmgrid(Grid* p)
{
	if(p -> cycstr != NULL && p -> cycstr != cs3333) free(p -> cycstr);
	for(int i = 0; i < p -> sz; free(p -> grid[i++]));
	free(p -> grid);
	free(p);
}

static int fwdchk(const char* a, const char* b, ull sa, ull sb, ull l)
{
	for(int i = 0, f = sa, k = sb; i < l; ++i)
		if(a[(sa + i) % l] != b[(sb + i) % l])
			return 0;
	return 1;
}

static int bckchk(const char* a, const char* b, ull sa, ull sb, ull l)
{
	for(int i = 0; i < l; i++)
	{
		if(a[sa] != b[sb])
			return 0;
		
		if(++sa >= l) sa = 0;
		if(--sb >= l) sb = l - 1;
	}
	return 1;
}

static int cycstreq(const char* a, const char* b)
{
	ull al = strlen(a), bl = strlen(b);
	
	if(al != bl)
		return 0;
	
	for(ull i = 0; i < al; ++i)
		for(ull j = 0; j < al; ++j)
			if(fwdchk(a, b, i, j, al) || bckchk(a, b, i, j, al))
				return 1;
	return 0;
}

int eqgrid(Grid* a, Grid* b)
{
	int _0 = (a -> area == b -> area);
	int _1 = (a -> peri == b -> peri);
	int _2 = (a -> surfarea == b -> surfarea);
	int _3 = (a -> cycstrlen == b -> cycstrlen);
	int _4 = cycstreq(cycstr(a), cycstr(b));
	
	return _0 && _1 && _2 && _3 && _4;
}

// These checks are illegal. They do not help.
// They determine grids 323323 and 332332 as inequal.
// && (a -> bounds.n == b -> bounds.n)
// && (a -> bounds.s == b -> bounds.s)
// && (a -> bounds.e == b -> bounds.e)
// && (a -> bounds.w == b -> bounds.w)
