#include "o.h"

static char cycch(Grid* g, uint x, uint y)
{
	byte n, s, e, w = e = s = n = 0;
	if(y) n = g -> grid[x][y - 1];
	if(y < g -> sz - 1) s = g -> grid[x][y + 1];
	if(x < g -> sz - 1) e = g -> grid[x + 1][y];
	if(x) w = g -> grid[x - 1][y];
	byte sum = n + s + e + w;
	
	if(sum == 2 && ((n && s) || (e && w)))
		return '1';
	return '4' - sum;
}

char* cycstr(Grid* g)
{
	if(g -> cycstr == NULL)
	{
		g -> cycstr = malloc(sizeof(char) * g -> cycstrlen + 1);
		uint x, y, ix, iy, i = y = x = 0;
		int t, dx = 1, dy = 1;
		char c;
		
		for(; y < g -> sz; y++)
			for(x = 0; x < g -> sz; x++)
				if(is_1(g, x, y))
					goto found;
found:
		ix = x;
		iy = y;
		
		g -> cycstr[i++] = cycch(g, x++, y++);
loop:
		g -> cycstr[i++] = c = cycch(g, x, y);
		
		switch(c)
		{
			case '1':
				//ccw
				t = -dx;
				dx = dy;
				dy = t;
				break;
			case '3':
				//cw
				t = -dy;
				dy = dx;
				dx = t;
				break;
			}
		
		x += dx;
		y += dy;
		
		if(ix == x && iy == y)
			g -> cycstr[i] = '\0';
		else
			goto loop;
	}
	
	return g -> cycstr;
}
