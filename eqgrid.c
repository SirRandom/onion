#include <string.h>
#include "o.h"

static int fwdchk(const char* a, const char* b, ull sa, ull sb, ull l)
{
	for(uint i = 0, f = sa, k = sb; i < l; ++i)
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
	return (a -> ord == b -> ord)
		 && (a -> edges == b -> edges)
		 && (a -> fwdcells == b -> fwdcells)
		 && (a -> cycstrlen == b -> cycstrlen)
		 && cycstreq(cycstr(a), cycstr(b));
}

// These checks are illegal. They do not help.
// They determine grids 323323 and 332332 as inequal.
// && (a -> bounds.n == b -> bounds.n)
// && (a -> bounds.s == b -> bounds.s)
// && (a -> bounds.e == b -> bounds.e)
// && (a -> bounds.w == b -> bounds.w)
