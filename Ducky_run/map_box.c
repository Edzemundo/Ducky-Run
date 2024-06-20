/*File used to create the map for the duck game.
For final project by Manree, Joe and Edmund
*/

//necessary libraries
#include "address_map_nios2.h"
#include <stdlib.h>
#include <time.h>

//function prototypes
void boxify(int, int, int, int, short); //x,y start and end, color
void VGA_text(int, int, char*);
int generate_random(int);
void mapify(void);


//This is an array of the location, colour and score value for each box in the game
//X1, Y1, X2, Y2, colour, score
int box[17][6] = {
{25, 20, 35, 30, 0xFA00, 20}
,{30, 40, 48, 60, 0x1CE0, 30}
,{100, 100, 150, 150, 0xFF00, 10}
,{300, 10, 310, 20, 0x001F, 50}
,{300, 10, 310, 20, 0xFF00, 10}
,{50, 50, 75, 75, 0xFA00, 20}
,{200, 200, 250, 215, 0x1CE0, 30}
,{300, 200, 320, 240, 0x001F, 50}
,{25, 200, 50, 240, 0xFF00, 10}
,{290, 100, 300, 110, 0xFA00,20}
,{250, 10, 270, 50, 0x1CE0, 30}
,{220, 220, 230, 230, 0xFF00, 10}
,{100, 10, 125, 35, 0x001F, 50}
,{200, 50, 230, 100, 0xFA00, 20}
,{20, 150, 50, 190, 0x1CE0, 30}
,{80, 160, 120, 190, 0xFA00, 20}
,{170, 125, 215, 155, 0xFF00, 10}
};


//function definition for creating each box at the specified location and color
void boxify(int x1, int y1, int x2, int y2, short pixel_color){
	int pixel_ptr, row, col;

	srand(time(NULL));	//random generator seed

	char ins[20] = "Get the boxes!    \0"; //instruction to show on screen

	VGA_text(35, 29, ins);
 
	for (row = y1; row <= y2; row++)	//for each row
	{
		for (col = x1; col <= x2; col++)	//for each column
		{
			pixel_ptr = FPGA_ONCHIP_BASE + (row << 10) + (col << 1);
			*(short*)(pixel_ptr) = pixel_color;
		}
	}
}


//function definition for creaing the boxes at the various locations
void mapify(void) {
	int i,j = 0;
	for (i = 0; i < 17; i++) {
		boxify(box[i][j], box[i][j + 1], box[i][j + 2], box[i][j + 3], box[i][j + 4]);
	}
}


//function definition to show text on the screen
void VGA_text(int x, int y, char* text_ptr) {
	int offset;
	volatile char* character_buffer = (char*)FPGA_CHAR_BASE;	// VGA character buffer

	/* assume that the text string fits on one line */
	offset = (y << 7) + x;
	while (*(text_ptr))
	{
		*(character_buffer + offset) = *(text_ptr);	// write to the character buffer
		++text_ptr;
		++offset;
	}
}


//function definition to generate a random number
int generate_random(int range) {
	int value;
	value = 1 + (int)rand % range;
	return(value);
}


