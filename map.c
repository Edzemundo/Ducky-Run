//draw the map 

#include "address_map_nios2.h"
#include <stdlib.h>
#include <time.h>

void box(int, int, int, int, short); //x,y start and end, color
int generateRandom(void);

int main()
{
	
	srand(time(NULL));   //generate seed for random boxes
    int randValue = generateRandom(), randValue2 = randValue + 100;
	//clear the screen
	box(0, 0, 319, 239, 0); //0, 319 and 0, 239 and black = 0

	while (1)
	{
           
		//X1, Y1, X2, Y2
			box(randValue, randValue, randValue + 50, randValue + 50, 0xFF00);
		
            box(randValue2, randValue2, randValue2 + 50, randValue2 + 50, 0xFA00);

		 
			
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

// function definition generate random integer
int generateRandom(void) {
    int value;
    //rand produces a random value that can be large we want to scale
    value = 1 + (int) rand() % 10; // between 1 and 10
    return(value);
}
