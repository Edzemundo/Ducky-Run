#include "address_map_nios2.h"

void VGA_text(int, int, char*);


int main(void)
{
	/* create a message to be displayed on the VGA and LCD displays */
	char text_top_row[40] = "Score: \0";

	VGA_text(300, 220, text_top_row);
}

/*******************************************************************************
 * Subroutine to send a string of text to the VGA monitor
 ******************************************************************************/
void VGA_text(int x, int y, char* text_ptr)
{
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
