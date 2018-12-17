#include "o.h"

#define gettime(name)		ull name; QueryPerformanceCounter((LARGE_INTEGER*) &name)
#define seconds(ta, tb)		((double) ((tb) - (ta)) / ctrfreq)
#define output_and_kill(x)	(print(x), rmgrid(x))

char* cs3333 = "3333";
HANDLE heap, hconin, hconout, hout;
ull ctrfreq;
Queue* queues[5];
int running = 1, end = 0;
int queue = 2;
uint active_queue = 0, v = 0, disk = 0;

BOOL CtrlHandler(DWORD ctrl)
{
	switch(ctrl)
	{
		case CTRL_C_EVENT:
		case CTRL_BREAK_EVENT:
		case CTRL_CLOSE_EVENT:
		case CTRL_LOGOFF_EVENT:
		default:
			FillConsoleOutputAttribute(hout, 0x0C, WIN_X * 2, (COORD) {0, 9}, &u);
			OutputXY(1, 9, "Received kill signal   ");
			OutputXY(1, 10, "Finalizing and dumping grids...");
			running = 0;
			return TRUE;
	}
}

static Grid* init(uint sz)
{
	heap = GetProcessHeap();
	QueryPerformanceFrequency((LARGE_INTEGER*) &ctrfreq);
	SetConsoleCtrlHandler(CtrlHandler, TRUE);
	hconout = GetStdHandle(STD_OUTPUT_HANDLE);
	hconin = GetStdHandle(STD_INPUT_HANDLE);
	hout = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, 0, CONSOLE_TEXTMODE_BUFFER, 0);
	SetConsoleActiveScreenBuffer(hout);
	resize(hout, WIN_X, WIN_Y);
	SetConsoleTitleA("Onion");
	
	FillConsoleOutputAttribute(hout, 0x08, WIN_X * 2, (COORD) {0, 9}, &u);
	OutputXY(1, 1, "Currently working on queue of area");
	OutputXY(1, 9, "Use CTRL+C to terminate");
	
	thread(th_update, 0);
	
	for(uint i = 0; i < 5; i++)
	{
		queues[i] = mallocz(sizeof(Queue));
		queues[i] -> backing = mallocz(sizeof(Grid*) * QUEUE_INITSZ);
		queues[i] -> cap = QUEUE_INITSZ;
	}
	
	Grid* g = malloc(sizeof(Grid));
	uint i;
	
	g -> cycstr = cs3333;
	g -> cycstrlen = 4;
	
	g -> grid = malloc(sizeof(byte*) * sz);
	for(i = 0; i < sz; g -> grid[i++] = mallocz(sizeof(byte) * sz));
	
	g -> peri = 12;
	g -> surfarea = 4;
	
	i = sz / 2;
	
	g -> bounds.n =
	g -> bounds.w = i - 1;
	g -> bounds.s =
	g -> bounds.e = i + 1;
	g -> area = 5;
	g -> sz = sz;
	
	g -> grid[i][i] =
	g -> grid[i + 1][i] =
	g -> grid[i - 1][i] =
	g -> grid[i][i + 1] =
	g -> grid[i][i - 1] = 1;
	
	return g;
}

static void bf(Grid* g)
{
	uint p;
	Grid *gg, *ggg;
	
	qAdd(queues[active_queue], g);
	while(running)
	{
		OutputXY(36, 1, digits(++queue));
		
		while(queues[active_queue] -> len)
		{
			if(!(gg = qGet(queues[active_queue])))
				continue;
			
			for(uint scan_y = 1; scan_y < gg -> sz - 1; scan_y++)
				for(uint scan_x = 1; scan_x < gg -> sz - 1; scan_x++)
					if(is_0(gg, scan_x, scan_y) && (ggg = add(gg, scan_x, scan_y, &p)))
						qAdd(queues[(active_queue + p) % 5], ggg);
			
			output_and_kill(gg);
		}
		
		active_queue = (active_queue + 1) % 5;
	}
	
	for(uint i = 0; i < 5; i++)
	{
		if(queues[i] -> len)
			while(queues[i] -> len)
				output_and_kill(qGet(queues[i]));
		
		free(queues[i] -> backing);
		free(queues[i]);
	}
}

int main(int argc, char** argv)
{
	bf(init(argc > 1 ? atoi(argv[1]) : 13u));
	
	end = 1;
	FillConsoleOutputAttribute(hout, 0x0A, WIN_X * 2, (COORD) {0, 9}, &u);
	OutputXY(1, 9, "Grids successfully dumped to disk");
	OutputXY(1, 10, "Sleeping for ten seconds...    ");
	
	Sleep(10000);
	SetConsoleActiveScreenBuffer(hconout);
	return 0;
}
