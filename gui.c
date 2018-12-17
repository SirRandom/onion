#include "o.h"

char buf[WIN_X + 1];
DWORD u;

char* digits(unsigned x)
{
	static char buf[16];
	int i = 0, j = 0, t;
	
	while(x)
	{
		buf[i++] = (x % 10) + '0';
		x /= 10;
	}
	
	buf[i] = 0;
	while(j < i/2)
	{
		t = buf[j];
		buf[j] = buf[i - 1 - j];
		buf[i - 1 - j] = t;
		j++;
	}
	
	return buf;
}

void resize(HANDLE h, short x, short y)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(h, &csbi);
	SMALL_RECT r = {0};
	r.Bottom = y - 1;
	r.Right = x - 1;
	SetConsoleScreenBufferSize(h, (COORD) {MAX(x, csbi.srWindow.Right + 1), MAX(y, csbi.srWindow.Bottom + 1)});
	SetConsoleWindowInfo(h, TRUE, &r);
	SetConsoleScreenBufferSize(h, (COORD) {x, y});
}

DWORD th_update(void* p)
{
	static unsigned short seconds = 0;
	static unsigned short minutes = 0;
	static unsigned short hours = 0;
	static unsigned short days = 0;
	
	while(!end)
	{
		Sleep(1000);
		
		if(++seconds == 60)
		{
			seconds = 0;
			if(++minutes == 60)
			{
				minutes = 0;
				if(++hours == 24)
				{
					hours = 0;
					++days;
				}
			}
		}
		
		FillConsoleOutputCharacter(hout, ' ', 40*4, (COORD) {0, 3}, &u);
		printxy(1, 3, "%u grids generated", v);
		printxy(1, 4, "%u grids in memory", v - disk);
		printxy(1, 5, "%u grids written to disk", disk);
		printxy(1, 7, "%u days, %02u:%02u:%02u seconds elapsed", days, hours, minutes, seconds);
	}
	
	return 0;
}
