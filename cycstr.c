#include "o.h"

static char cycch(Grid* g, int x, int y)
{
#if DEBUG
	printf("CYCCH");
#endif
	byte n, s, e, w = e = s = n = 0;
	if(y > 0) n = g -> grid[x][y - 1];
	if(y < g -> sz - 1) s = g -> grid[x][y + 1];
	if(x < g -> sz - 1) e = g -> grid[x + 1][y];
	if(x > 0) w = g -> grid[x - 1][y];
	byte sum = n + s + e + w;
	
	if(sum == 2 && ((n && s) || (e && w)))
		return '1';
	return '4' - sum;
}

char* cycstr(Grid* g)
{
#if DEBUG
	printf("CYCSTR");
#endif
	if(g -> cycstr == NULL)
	{
		int x, y, ix, iy, dx = 1, dy = 1, i = 0, t;
		char c;
		
		g -> cycstr = mallocz(sizeof(char) * g -> cycstrlen + 1);
		
		for(y = 0; y < g -> sz; y++)
			for(x = 0; x < g -> sz; x++)
				if(g -> grid[x][y])
					goto found;
found:
		ix = x++;
		iy = y++;
		g -> cycstr[i++] = '3';
		
		while(ix != x || iy != y)
		{
			switch(c = cycch(g, x, y))
			{
				case '1':
					t = -dx;
					dx = dy;
					dy = t;
					break;
				case '2': break;
				case '3':
					t = -dy;
					dy = dx;
					dx = t;
					break;
				default:
#if DEBUG
					printf("REACHED DEFAULT CASE IN CYCSTR (c == \'%c\')\n", c);
#endif
					break;
			}
			
			g -> cycstr[i++] = c;
			x += dx;
			y += dy;
		}
	}
	
	return g -> cycstr;
}
