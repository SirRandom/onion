#include <windows.h>

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

int main(int argc, char** argv)
{
	
	
	
	return 0;
}
