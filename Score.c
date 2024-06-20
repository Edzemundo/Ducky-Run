#include "address_map_nios2.h"
#include "nios2_ctrl_reg_macros.h"

//Move text "Altera" across the screen (left/right)
//Move a line up the screen

volatile int timeout;	//global timeout varibale for synchronization

//int y_dir;	//set it to 1 to move the line up one pixel at a time

volatile int pixel_buffer_start = FPGA_ONCHIP_BASE;

int resolution_x = 320;		//max x
int resolution_y = 240;		//max y

void clearScreen();
void VGA_text(int, int, char *);
//void drawLine(int, int, short);

int main()
{
	//volatile int * interval_timer_ptr = (int *) TIMER_BASE;
	
	timeout = 0;
	
	int ALT_x1, ALT_x2, ALT_y;
	int ALT_inc_x;
	int char_buffer_x;
	
	int y_position = 230;	//start at 230
	y_dir = 1;			//increment by 1
	
	int counter = 0x960000;		//approx 200ms
	*(interval_timer_ptr + 2) = (counter & 0xFFFF);
	*(interval_timer_ptr + 3) = (counter >> 16) & 0xFFFF;
	*(interval_timer_ptr + 1) = 0x7;
	
	NIOS2_WRITE_IENABLE(0x1);
	NIOS2_WRITE_STATUS(1);
	
	char text_ALTERA[10] = "Score: \0";
	char text_erase[10] = "      \0";
	
	clearScreen();
	
	char_buffer_x = 79;
	ALT_x1 = 0;		//text start screen
	ALT_x2 = 5;		//text end on screen
	ALT_y = 0;
	ALT_inc_x = 1;	//move accross one at a time
	
	VGA_text(ALT_x1, ALT_y, text_Score);
	
	//drawLine(0, y_position, 0x187F);
	
	while(1)
	{
		while(!timeout);	//barrier, while timeout == 0, do nothing
		
		//eventaully, timer gets to 0, send out interrupt
		//calls ISR which sets timeout = 1 so you can move past the barrier
		
		VGA_text(ALT_x1, ALT_y, text_erase);	//erase text
		ALT_x1 += ALT_inc_x;
		ALT_x2 += ALT_inc_x;
		
		if((ALT_x2 == char_buffer_x) || (ALT_x1 == 0)) //if you get to a boundary
		{
			ALT_inc_x = -(ALT_inc_x);		//change direction
		}
		
		VGA_text(ALT_x1, ALT_y, text_ALTERA);	//write in new position
		
		
		clearScreen();
		y_position -= y_dir;
		if(y_position == 0)		//top of the screen
		{
			y_position = 230;
		}
		drawLine(0, y_position, 0x187F);
		
		timeout = 0;		//DO NOT FORGET TO RESET THIS
	}
	
	return 0;
}

void clearScreen()
{
	int clearColor = 0;
	
	int pixel_ptr, row, col;
	
	for(row = 0; row < resolution_y; row++)
	{
		for(col = 0; col < resolution_x; col++)
		{
			pixel_ptr = pixel_buffer_start + (row << 10) + (col << 1);
			*(short *)pixel_ptr = clearColor;
		}
	}
}

void VGA_text(int x, int y, char * text_ptr)
{
	int offset;
	volatile char * character_buffer = (char *) FPGA_CHAR_BASE;
	
	offset = (y << 7) + x;
	
	while(*(text_ptr))
	{
		*(character_buffer + offset) = *(text_ptr);
		++text_ptr;
		++offset;
	}
}

//void drawLine(int Line_x, int Line_y, short Line_color)
//{
	//int col, pixel_ptr;
	//for(col = 0; col < resolution_x; col++)
	//{
		//pixel_ptr = pixel_buffer_start + (Line_y << 10) + (col << 1);
		//*(short *)pixel_ptr = Line_color;
	//}
//}


//offset when drawing figures
//(row << 10) + (col << 1)
//(row << 9) + col;







