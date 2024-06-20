#include "address_map_nios2.h"
#include "nios2_ctrl_reg_macros.h"
#include <stdio.h>
#include "JTAG_UART.h"  //must add this

//other code

volatile int timeout;	//global timeout varibale for synchronization

int y_dir;	//set it to 1 to move the line up one pixel at a time

volatile int pixel_buffer_start = FPGA_ONCHIP_BASE;

int resolution_x = 320;		//max x
int resolution_y = 240;		//max y

void clearScreen();
void VGA_text(int, int, char*);
void drawLine(int, int, short);
void VGA_box(int, int, int, int, short);

int main() {


    volatile int* JTAG_UART_ptr = (int*)JTAG_UART_BASE; //must add this

	volatile int* interval_timer_ptr = (int*)TIMER_BASE;

	timeout = 0;

	int ALT_y1, ALT_y2, ALT_x, ALT_yy1, ALT_yy2;
	int ALT_inc_x;
	int char_buffer_x1, char_buffer_x2;

	int y_position = 230;	//start at 230
	y_dir = 1;			//increment by 1

	int counter = 0x9600;		//approx 200ms
	*(interval_timer_ptr + 2) = (counter & 0xFFFF);
	*(interval_timer_ptr + 3) = (counter >> 16) & 0xFFFF;
	*(interval_timer_ptr + 1) = 0x7;

	NIOS2_WRITE_IENABLE(0x1);
	NIOS2_WRITE_STATUS(1);

	char text_ALTERA[10] = "ALTERA\0";
	char text_erase[10] = "      \0";

	clearScreen();

	char_buffer_x1 = 240;
	char_buffer_x2 = 226;

	ALT_y1 = 0;		//text start screen
	ALT_y2 = ALT_y1 + 40;	//text end on screen
	ALT_yy1 = 13;
	ALT_yy2 = 27;



	ALT_x = 0;
	ALT_inc_x = 1;	//move accross one at a time

			VGA_box(110, ALT_y1, 150, ALT_y2, 0x001F);	//write in new position
		    VGA_box(123, ALT_yy1, 137, ALT_yy2, 0x1CE0);
			VGA_box(150, ALT_y1, 210, ALT_y2, 0xFF00);


    while (1) 
    {
        while (!timeout) 
        {

            //other code
		VGA_box(160, ALT_y1, 200, ALT_y2, 0x001F);
		VGA_box(40, 40, 80, 80, 0x001F);
		VGA_box(173, ALT_yy1, 187, ALT_yy2, 0x1CE0);
		VGA_box(200, ALT_y1, 260, ALT_y2, 0xFF00);
	
            char c = get_jtag(JTAG_UART_ptr);   //reading the input from the keyboard

			
            
            switch (c)
            {
                case 'w':
				ALT_y1 -= ALT_inc_x;
				ALT_y2 -= ALT_inc_x;
				ALT_yy1 -= ALT_inc_x;
				ALT_yy2 -= ALT_inc_x;

				if ((ALT_y2 == char_buffer_x1) || (ALT_y1 == 0)) //if you get to a boundary
				{
					ALT_inc_x = -(ALT_inc_x);		//change direction
				}
				else if ((ALT_yy2 == char_buffer_x2) || (ALT_yy1 == 12)) //if you get to a boundary
				{
					ALT_inc_x = -(ALT_inc_x);		//change direction
				}
				VGA_box(110, ALT_y1, 150, ALT_y2, 0x001F);	//write in new position
		  	    VGA_box(123, ALT_yy1, 137, ALT_yy2, 0x1CE0);
				VGA_box(150, ALT_y1, 210, ALT_y2, 0xFF00);
	
				clearScreen(); 

				timeout = 0; 
	
                    break;
                case 's':
                    //do something
                    break;
                case 'i':
                    //do something                 
                    break;
                case 'k':
                    //do something                 
                    break;
            }
		    
            
        }
    }
}

//function definitions

void clearScreen()
{
	int clearColor = 0;

	int pixel_ptr, row, col;

	for (row = 0; row < resolution_y; row++)
	{
		for (col = 0; col < resolution_x; col++)
		{
			pixel_ptr = pixel_buffer_start + (row << 10) + (col << 1);
			*(short*)pixel_ptr = clearColor;
		}
	}
}

void VGA_text(int x, int y, char* text_ptr)
{
	int offset;
	volatile char* character_buffer = (char*)FPGA_CHAR_BASE;

	offset = (y << 7) + x;

	while (*(text_ptr))
	{
		*(character_buffer + offset) = *(text_ptr);
		++text_ptr;
		++offset;
	}
}

void drawLine(int Line_x, int Line_y, short Line_color)
{
	int col, pixel_ptr;
	for (col = 0; col < resolution_x; col++)
	{
		pixel_ptr = pixel_buffer_start + (Line_y << 10) + (col << 1);
		*(short*)pixel_ptr = Line_color;
	}
}

void VGA_box(int x1, int y1, int x2, int y2, short pixel_color)
{
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
