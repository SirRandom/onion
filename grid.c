#include <string.h>
#include "o.h"

Grid* cpgrid(Grid* s)
{
#if DEBUG
	printf("CPGRID\n");
#endif
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
	
#if DEBUG
	printf("END CPGRID\n");
#endif
	return d;
}

void rmgrid(Grid* p)
{
#if DEBUG
	printf("RMGRID\n");
#endif
	if(p)
	{
		if(p -> cycstr != NULL && p -> cycstr != cs3333) free(p -> cycstr);
		for(int i = 0; i < p -> sz; free(p -> grid[i++]));
		free(p -> grid);
		free(p);
	}
#if DEBUG
	printf("END RMGRID\n");
#endif
}

static int fwdchk(const char* a, const char* b, ull sa, ull sb, ull l)
{
#if DEBUG
	printf("FWDCHK\n");
#endif
	for(int i = 0, f = sa, k = sb; i < l; ++i)
		if(a[(sa + i) % l] != b[(sb + i) % l])
		{
#if DEBUG
			printf("END FWDCHK\n");
#endif
			return 0;
		}
#if DEBUG
	printf("END FWDCHK\n");
#endif
	return 1;
}

static int bckchk(const char* a, const char* b, ull sa, ull sb, ull l)
{
#if DEBUG
	printf("BCKCHK\n");
#endif
	for(int i = 0; i < l; i++)
	{
		if(a[sa] != b[sb])
		{
#if DEBUG
			printf("END BCKCHK\n");
#endif
			return 0;
		}
		
		if(++sa >= l) sa = 0;
		if(--sb >= l) sb = l - 1;
	}
#if DEBUG
	printf("END BCKCHK\n");
#endif
	return 1;
}

static int cycstreq(const char* a, const char* b)
{
#if DEBUG
	printf("CYCSTREQ\n");
#endif
	ull al = strlen(a), bl = strlen(b);
	
	if(al != bl)
		return 0;
	
	for(ull i = 0; i < al; ++i)
		for(ull j = 0; j < al; ++j)
			if(fwdchk(a, b, i, j, al) || bckchk(a, b, i, j, al))
			{
#if DEBUG
				printf("ENDING CYCSTREQ: 1\n");
#endif
				return 1;
			}
#if DEBUG
	printf("ENDING CYCSTREQ: 0\n");
#endif
	return 0;
}

int eqgrid(Grid* a, Grid* b)
{
#if DEBUG
	printf("EQGRID a=%p b=%p\n", a, b);
#endif
	return (a -> area == b -> area)
	    && (a -> peri == b -> peri)
	    && (a -> surfarea == b -> surfarea)
	    && (a -> cycstrlen == b -> cycstrlen)
	    && cycstreq(cycstr(a), cycstr(b));
}

// These checks are illegal. They do not help.
// They determine grids 323323 and 332332 as inequal.
// && (a -> bounds.n == b -> bounds.n)
// && (a -> bounds.s == b -> bounds.s)
// && (a -> bounds.e == b -> bounds.e)
// && (a -> bounds.w == b -> bounds.w)
