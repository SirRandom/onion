#ifndef ___ONION___
#include <windows.h>
#include <string.h>
#include <stdio.h>

#define WIN_X 50
#define WIN_Y 12

#define RC_MAX (1024*8)
#define QUEUE_INITSZ 32

#define malloc(b)					HeapAlloc(heap, 0, (b))
#define mallocz(b)				HeapAlloc(heap, HEAP_ZERO_MEMORY, (b))
#define realloc(p, b)			HeapReAlloc(heap, 0, (p), (b))
#define reallocz(p, b)			HeapReAlloc(heap, HEAP_ZERO_MEMORY, (p), (b))
#define memcpy(d, s, b)			CopyMemory((d), (s), (b))
#define free(p)					HeapFree(heap, 0, (p))

#define thread(f, p)				CreateThread(NULL, 0, (f), (p), 0, NULL)

#define printxy(x, y, fmt, ...)	sprintf(buf, (fmt), __VA_ARGS__); OutputXY((x), (y), buf)
#define OutputXY(x, y, str)		WriteConsoleOutputCharacterA(hout, (str), strlen(str), (COORD) {(x), (y)}, &u)

#define MAX(a, b) (((a) < (b))? (b) : (a))

#define is_1(g, x, y)		((g) -> grid[(x)][(y)])
#define is_0(g, x, y)		(!((g) -> grid[(x)][(y)]))

#define NORTH				0
#define NORTHEAST			1
#define EAST				2
#define SOUTHEAST			3
#define SOUTH				4
#define SOUTHWEST			5
#define WEST				6
#define NORTHWEST			7

typedef unsigned long long ull;
typedef unsigned char byte;
typedef unsigned int uint;

typedef struct Grid
{
	char*		cycstr;
	uint		cycstrlen;
	byte**	grid;
	uint		peri;
	uint		surfarea;
	struct
	{
		uint n;
		uint s;
		uint e;
		uint w;
	} bounds;
	uint area;
	uint sz;
} Grid;

typedef struct Queue
{
	Grid** backing;
	uint head;
	uint tail;
	uint cap;
	uint len;
} Queue;

extern char buf[WIN_X + 1];
extern char* cs3333;
extern HANDLE heap, hconout, hconin, hout;
extern ull ctrfreq;
extern Queue* queues[5];
extern int running, end;
extern uint active_queue, v, disk;
extern DWORD u;

Grid* add(Grid*, int, int, int*);
Grid* cpgrid(Grid*);
char* cycstr(Grid*);
int   eqgrid(Grid*, Grid*);
void  print(Grid*);
void  rmgrid(Grid*);
void  qAdd(Queue*, Grid*);
Grid* qGet(Queue*);

DWORD th_update(void*);

void resize(HANDLE, short, short);
char* digits(unsigned);

/* DEBUG FUNCTIONS */
void pg(Grid*);
void pq(Queue*);
void paq(void);

#define ___ONION___
#endif
