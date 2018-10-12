#include "o.h"

void print(Grid* g)
{
	FILE* f;
	if(f = fopen(cycstr(g), "w"))
	{
		fprintf(
			f,
			"cycstr    %s\n"
			"cycstrlen %u\n"
			"perimeter %u\n"
			"surfarea  %u\n"
			"bounds.n  %u\n"
			"bounds.s  %u\n"
			"bounds.e  %u\n"
			"bounds.w  %u\n"
			"area      %u\n",
			cycstr(g),
			g -> cycstrlen,
			g -> peri,
			g -> surfarea,
			g -> bounds.n,
			g -> bounds.s,
			g -> bounds.e,
			g -> bounds.w,
			g -> area
		);
		for(uint y = 0; y < g -> sz; y++)
		{
			for(uint x = 0; x < g -> sz; x++)
				fprintf(f, "%1u", g -> grid[x][y]);
			fprintf(f, "\n");
		}
		fprintf(f, "\n");
		fclose(f);
	}
	else DebugBreak();
}
