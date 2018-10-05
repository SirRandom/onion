#include "o.h"

void rmgrid(Grid* p)
{
	if(p -> cycstr != NULL && p -> cycstr != "3333") free(p -> cycstr);
	for(uint i = 0; i < p -> sz; free(p -> grid[i++]));
	free(p -> grid);
	free(p);
}
