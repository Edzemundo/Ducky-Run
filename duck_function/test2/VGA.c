#include "address_map_nios2.h"

/* function prototypes */
void VGA_text (int, int, char *);
void VGA_box (int, int, int, int, short);

/*******************************************************************************
 * This program demonstrates use of the media ports in the DE1-SoC Computer
 * Draws a blue box on the VGA display, and places a text string inside the box
 ******************************************************************************/
int main(void)
{
	/* Declare volatile pointers to I/O registers (volatile means that IO load
	 * and store instructions will be used to access these pointer locations, 
	 * instead of regular memory loads and stores) 
	 */
  	volatile int * red_LED_ptr = (int *) LEDR_BASE;

	/* create a message to be displayed on the VGA and LCD displays */
	char text_top_row[40] = "Intel FPGA\0";
	char text_bottom_row[40] = "Computer Systems\0";

	VGA_text (35, 29, text_top_row);
	VGA_text (32, 30, text_bottom_row);
	VGA_box (0, 0, 319, 239, 0);							// clear the screen
	VGA_box (31*4, 28*4, 49*4 - 1, 32*4 - 1, 0x187F);
}

/*******************************************************************************
 * Subroutine to send a string of text to the VGA monitor 
 ******************************************************************************/
void VGA_text(int x, int y, char * text_ptr)
{
	int offset;
  	volatile char * character_buffer = (char *) FPGA_CHAR_BASE;	// VGA character buffer

	/* assume that the text string fits on one line */
	offset = (y << 7) + x;
	while ( *(text_ptr) )
	{
		*(character_buffer + offset) = *(text_ptr);	// write to the character buffer
		++text_ptr;
		++offset;
	}
}

/*******************************************************************************
 * Draw a filled rectangle on the VGA monitor 
 ******************************************************************************/
void VGA_box(int x1, int y1, int x2, int y2, short pixel_color)
{
	int pixel_ptr, row, col;

	/* assume that the box coordinates are valid */
	for (row = y1; row <= y2; row++)
		for (col = x1; col <= x2; ++col)
		{
			pixel_ptr = FPGA_ONCHIP_BASE + (row << 10) + (col << 1);
			*(short *)pixel_ptr = pixel_color;		// set pixel color
		}
}

