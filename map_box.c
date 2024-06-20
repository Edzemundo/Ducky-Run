//draw the map with boxes 


#include "address_map_nios2.h"
#include <stdlib.h>
#include <time.h>

void box(int, int, int, int, short); //x,y start and end, color


int main()
{
	
	//clear the screen
	box(0, 0, 319, 239, 0); //0, 319 and 0, 239 and black = 0

	while (1)
	{
           
		//X1, Y1, X2, Y2
			box(0, 10, 0 + 10, 10+ 10, 0xFF00);
			box(25, 20, 25 + 10, 20 + 10, 0xFA00);
			box(40, 40, 40 + 5, 40 + 5, 0x1CE0);
			box(100, 100, 100 + 50, 100 + 50, 0x001F);
			box(300, 10, 300 + 10, 10 + 10, 0xFF00);
			box(50, 50, 50 + 25, 50 + 25, 0xFA00);
			box(200, 200, 200 + 50, 200 + 15, 0x1CE0);
			box(300, 200, 320, 240, 0x001F);
			box(25, 200, 50, 240, 0xFF00);
			box(290, 100, 300, 110, 0xFA00);
			box(250, 10, 270, 50, 0x1CE0);
			box(220, 220, 225, 225, 0xFF00);
			box(100, 10, 125, 35, 0x001F);
			box(200, 50, 230, 100, 0xFA00);
			box(20, 150, 50, 190, 0x1CE0);
			box(80, 160, 120, 190, 0xFA00);
			box(170, 125, 215, 155, 0xFF00);			
	}

	return 0;
}

void box(int x1, int y1, int x2, int y2, short pixel_color){
	int pixel_ptr, row, col;

 

	for (row = y1; row <= y2; row++)
	{
		for (col = x1; col <= x2; col++)
		{
			pixel_ptr = FPGA_ONCHIP_BASE + (row << 10) + (col << 1);
			*(short*)(pixel_ptr) = pixel_color;
		}
	}
}


