#include "o.h"

#include "placei.i"
#include "placel.i"
#include "placet.i"

#define nae(y)				((y) == 1)
#define sae(g, y)			((y) == (g) -> sz - 2)
#define eae(g, x)			((x) == (g) -> sz - 2)
#define wae(x)				((x) == 1)

#define placeNorthernT(g, x, y)		placet((g), NORTH, (x), (y))
#define placeSouthernT(g, x, y)		placet((g), SOUTH, (x), (y))
#define placeEasternT(g, x, y)		placet((g), EAST, (x), (y))
#define placeWesternT(g, x, y)		placet((g), WEST, (x), (y))

#define placeNorthernI(g, x, y)		placei((g), NORTH, (x), (y))
#define placeSouthernI(g, x, y)		placei((g), SOUTH, (x), (y))
#define placeEasternI(g, x, y)		placei((g), EAST, (x), (y))
#define placeWesternI(g, x, y)		placei((g), WEST, (x), (y))

#define placeNortheasternL(g, x, y)	placel((g), NORTHEAST, (x), (y))
#define placeSoutheasternL(g, x, y)	placel((g), SOUTHEAST, (x), (y))
#define placeSouthwesternL(g, x, y)	placel((g), SOUTHWEST, (x), (y))
#define placeNorthwesternL(g, x, y)	placel((g), NORTHWEST, (x), (y))

Grid* add(Grid* g, int x, int y, int* p)
{
	// n | s | e | w
	
	if(x < 0 || y < 0)
	{
		printf("!!! TRIED TO ADD PAST BOUNDARIES !!!\n");
		printf("Grid %s: %d %d\n", cycstr(g), x, y);
	}
	
	switch(g -> grid[x][y - 1] << 3 | g -> grid[x][y + 1] << 2 | g -> grid[x + 1][y] << 1 | g -> grid[x - 1][y])
	{
		case 1: // 0001: Attempt to place a T facing east-ward
			*p = 4;
			switch(nae(y) << 2 | sae(g, y) << 1 | eae(g, x))
			{
				case 0:
					if(is_0(g, x - 1, y - 2) && is_0(g, x - 1, y + 2) && is_0(g, x + 2, y - 1) && is_0(g, x + 2, y + 1) && is_0(g, x + 1, y - 2) && is_0(g, x + 1, y + 2) && is_0(g, x, y - 2) && is_0(g, x, y + 2) && is_0(g, x + 2, y))
						return placeEasternT(g, x, y);
					return NULL;
				
				case 1:
					if(is_0(g, x - 1, y - 2) && is_0(g, x - 1, y + 2) && is_0(g, x, y - 2) && is_0(g, x, y + 2))
						return placeEasternT(g, x, y);
					return NULL;
				
				case 2:
					if(is_0(g, x - 1, y - 2) && is_0(g, x + 2, y - 1) && is_0(g, x + 1, y - 2) && is_0(g, x, y - 2) && is_0(g, x + 2, y))
						return placeEasternT(g, x, y);
					return NULL;
				
				case 3:
					if(is_0(g, x - 1, y - 2) && is_0(g, x, y - 2))
						return placeEasternT(g, x, y);
					return NULL;
				
				case 4:
					if(is_0(g, x - 1, y + 2) && is_0(g, x + 2, y + 1) && is_0(g, x + 1, y + 2) && is_0(g, x, y + 2) && is_0(g, x + 2, y))
						return placeEasternT(g, x, y);
					return NULL;
				
				case 5:
					if(is_0(g, x - 1, y + 2) && is_0(g, x, y + 2))
						return placeEasternT(g, x, y);
					return NULL;
				
				case 6:
					if(is_0(g, x + 2, y))
						return placeEasternT(g, x, y);
					return NULL;
				
				case 7:	return placeEasternT(g, x, y);
				default:	return NULL;
			}
		
		case 2: // 0010: Attempt to place a T piece facing west-ward
			*p = 4;
			switch(nae(y) << 2 | sae(g, y) << 1 | wae(x))
			{
				case 0:
					if(is_0(g, x + 1, y - 2) && is_0(g, x + 1, y + 2) && is_0(g, x - 2, y - 1) && is_0(g, x - 2, y + 1) && is_0(g, x - 1, y - 2) && is_0(g, x - 1, y + 2) && is_0(g, x, y - 2) && is_0(g, x, y + 2) && is_0(g, x - 2, y))
						return placeWesternT(g, x, y);
					return NULL;
				
				case 1:
					if(is_0(g, x + 1, y - 2) && is_0(g, x + 1, y + 2) && is_0(g, x, y - 2) && is_0(g, x, y + 2))
						return placeWesternT(g, x, y);
					return NULL;
				
				case 2:
					if(is_0(g, x + 1, y - 2) && is_0(g, x - 2, y - 1) && is_0(g, x - 1, y - 2) && is_0(g, x, y - 2) && is_0(g, x - 2, y))
						return placeWesternT(g, x, y);
					return NULL;
				
				case 3:
					if(is_0(g, x + 1, y - 2) && is_0(g, x, y - 2))
						return placeWesternT(g, x, y);
					return NULL;
				
				case 4:
					if(is_0(g, x + 1, y + 2) && is_0(g, x - 2, y + 1) && is_0(g, x - 1, y + 2) && is_0(g, x, y + 2) && is_0(g, x - 2, y))
						return placeWesternT(g, x, y);
					return NULL;
				
				case 5:
					if(is_0(g, x + 1, y + 2) && is_0(g, x, y + 2))
						return placeWesternT(g, x, y);
					return NULL;
				
				case 6:
					if(is_0(g, x - 2, y))
						return placeWesternT(g, x, y);
					return NULL;
				
				case 7:	return placeWesternT(g, x, y);
				default:	return NULL;
			}
		
		case 4: // 0100: Attempt to place a T piece facing north-ward
			*p = 4;
			switch(nae(y) << 2 | eae(g, x) << 1 | wae(x))
			{
				case 0:
					if(is_0(g, x + 2, y + 1) && is_0(g, x - 2, y + 1) && is_0(g, x + 1, y - 2) && is_0(g, x - 1, y - 2) && is_0(g, x + 2, y - 1) && is_0(g, x - 2, y - 1) && is_0(g, x + 2, y) && is_0(g, x - 2, y) && is_0(g, x, y - 2))
						return placeNorthernT(g, x, y);
					return NULL;
				
				case 1:
					if(is_0(g, x + 2, y + 1) && is_0(g, x + 1, y - 2) && is_0(g, x + 2, y - 1) && is_0(g, x + 2, y) && is_0(g, x, y - 2))
						return placeNorthernT(g, x, y);
					return NULL;
				
				case 2:
					if(is_0(g, x - 2, y + 1) && is_0(g, x - 1, y - 2) && is_0(g, x - 2, y - 1) && is_0(g, x - 2, y) && is_0(g, x, y - 2))
						return placeNorthernT(g, x, y);
					return NULL;
				
				case 3:
					if(is_0(g, x, y - 2)) return placeNorthernT(g, x, y);
					return NULL;
				
				case 4:
					if(is_0(g, x + 2, y + 1) && is_0(g, x - 2, y + 1) && is_0(g, x + 2, y) && is_0(g, x - 2, y))
						return placeNorthernT(g, x, y);
					return NULL;
				
				case 5:
					if(is_0(g, x + 2, y + 1) && is_0(g, x + 2, y))
						return placeNorthernT(g, x, y);
					return NULL;
				
				case 6:
					if(is_0(g, x - 2, y + 1) && is_0(g, x - 2, y))
						return placeNorthernT(g, x, y);
					return NULL;
				
				case 7:	return placeNorthernT(g, x, y);
				default:	return NULL;
			}
		
		case 8: // 1000: Attempt to place a T facing south-ward
			*p = 4;
			switch(sae(g, y) << 2 | eae(g, x) << 1 | wae(x))
			{
				case 0:
					if(is_0(g, x + 2, y - 1) && is_0(g, x - 2, y - 1) && is_0(g, x + 1, y + 2) && is_0(g, x - 1, y + 2) && is_0(g, x + 2, y + 1) && is_0(g, x - 2, y + 1) && is_0(g, x + 2, y) && is_0(g, x - 2, y) && is_0(g, x, y + 2))
						return placeSouthernT(g, x, y);
					return NULL;
				
				case 1:
					if(is_0(g, x + 2, y - 1) && is_0(g, x + 1, y + 2) && is_0(g, x + 2, y + 1) && is_0(g, x + 2, y) && is_0(g, x, y + 2))
						return placeSouthernT(g, x, y);
					return NULL;
				
				case 2:
					if(is_0(g, x - 2, y - 1) && is_0(g, x - 1, y + 2) && is_0(g, x - 2, y + 1) && is_0(g, x - 2, y) && is_0(g, x, y + 2))
						return placeSouthernT(g, x, y);
					return NULL;
				
				case 3:
					if(is_0(g, x, y + 2)) return placeSouthernT(g, x, y);
					return NULL;
				
				case 4:
					if(is_0(g, x + 2, y - 1) && is_0(g, x - 2, y - 1) && is_0(g, x + 2, y) && is_0(g, x - 2, y))
						return placeSouthernT(g, x, y);
					return NULL;
				
				case 5:
					if(is_0(g, x + 2, y - 1) && is_0(g, x + 2, y))
						return placeSouthernT(g, x, y);
					return NULL;
				
				case 6:
					if(is_0(g, x - 2, y - 1) && is_0(g, x - 2, y))
						return placeSouthernT(g, x, y);
					return NULL;
				
				case 7:	return placeSouthernT(g, x, y);
				default:	return NULL;
			}
		
		case 5: // 0101: Attempt to place an L facing north-east-ward
			*p = 3;
			switch(nae(y) << 1 | eae(g, x))
			{
				case 0:
					if(is_0(g, x - 1, y - 2) && is_0(g, x + 2, y + 1) && is_0(g, x + 1, y - 2) && is_0(g, x + 2, y - 1) && is_0(g, x, y - 2) && is_0(g, x + 2, y))
						return placeNortheasternL(g, x, y);
					return NULL;
				
				case 1:
					if(is_0(g, x - 1, y - 2) && is_0(g, x, y - 2))
						return placeNortheasternL(g, x, y);
					return NULL;
				
				case 2:
					if(is_0(g, x + 2, y + 1) && is_0(g, x + 2, y))
						return placeNortheasternL(g, x, y);
					return NULL;
				
				case 3: return placeNortheasternL(g, x, y);
				default: return NULL;
			}
		
		case 6: // 0110: Attempt to place an L facing north-west-ward
			*p = 3;
			switch(nae(y) << 1 | wae(x))
			{
				case 0:
					if(is_0(g, x + 1, y - 2) && is_0(g, x - 2, y + 1) && is_0(g, x - 1, y - 2) && is_0(g, x - 2, y - 1) && is_0(g, x, y - 2) && is_0(g, x - 2, y))
						return placeNorthwesternL(g, x, y);
					return NULL;
				
				case 1:
					if(is_0(g, x + 1, y - 2) && is_0(g, x, y - 2))
						return placeNorthwesternL(g, x, y);
					return NULL;
				
				case 2:
					if(is_0(g, x - 2, y + 1) && is_0(g, x - 2, y))
						return placeNorthwesternL(g, x, y);
					return NULL;
				
				case 3: return placeNorthwesternL(g, x, y);
				default:	return NULL;
			}
		
		case 9: // 1001: Attempt to place an L facing south-east-ward
			*p = 3;
			switch(sae(g, y) << 1 | eae(g, x))
			{
				case 0:
					if(is_0(g, x + 2, y - 1) && is_0(g, x - 1, y + 2) && is_0(g, x + 2, y + 1) && is_0(g, x + 1, y + 2) && is_0(g, x + 2, y) && is_0(g, x, y + 2))
						return placeSoutheasternL(g, x, y);
					return NULL;
				
				case 1:
					if(is_0(g, x - 1, y + 2) && is_0(g, x, y + 2))
						return placeSoutheasternL(g, x, y);
					return NULL;
				
				case 2:
					if(is_0(g, x + 2, y - 1) && is_0(g, x + 2, y))
						return placeSoutheasternL(g, x, y);
					return NULL;
				
				case 3:	return placeSoutheasternL(g, x, y);
				default:	return NULL;
			}
		
		case 10: // 1010: Attempt to place an L facing south-west-ward
			*p = 3;
			switch(sae(g, y) << 1 | wae(x))
			{
				case 0:
					if(is_0(g, x - 2, y - 1) && is_0(g, x + 1, y + 2) && is_0(g, x - 2, y + 1) && is_0(g, x - 1, y + 2) && is_0(g, x - 2, y) && is_0(g, x, y + 2))
						return placeSouthwesternL(g, x, y);
					return NULL;
				
				case 1:
					if(is_0(g, x + 1, y + 2) && is_0(g, x, y + 2))
						return placeSouthwesternL(g, x, y);
					return NULL;
				
				case 2:
					if(is_0(g, x - 2, y - 1) && is_0(g, x - 2, y))
						return placeSouthwesternL(g, x, y);
					return NULL;
				
				case 3:	return placeSouthwesternL(g, x, y);
				default:	return NULL;
			}
		
		case 7: // 0111: Attempt to place an I facing north-ward
			*p = 2;
			if(nae(y) || (is_0(g, x - 1, y - 2) && is_0(g, x + 1, y - 2) && is_0(g, x, y - 2)))
				return placeNorthernI(g, x, y);
			return NULL;
		
		case 11: // 1011: Attempt to place an I facing south-ward
			*p = 2;
			if(sae(g, y) || (is_0(g, x - 1, y + 2) && is_0(g, x + 1, y + 2) && is_0(g, x, y + 2)))
				return placeSouthernI(g, x, y);
			return NULL;
		
		case 13: // 1101: Attempt to place an I facing east-ward
			*p = 2;
			if(eae(g, x) || (is_0(g, x + 2, y - 1) && is_0(g, x + 2, y + 1) && is_0(g, x + 2, y)))
				return placeEasternI(g, x, y);
			return NULL;
		
		case 14: // 1110: Attempt to place an I facing west-ward
			*p = 2;
			if(wae(x) || (is_0(g, x - 2, y - 1) && is_0(g, x - 2, y + 1) && is_0(g, x - 2, y)))
				return placeWesternI(g, x, y);
			// return NULL; intentionally fall through
		
		case 0:
		case 3:
		case 12:
		case 15:
		default: return NULL;
	}
}
