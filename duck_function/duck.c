//yellow 0xFF00, red 0xFA00, Green 0x1CE0, Blue 0x001F, black 0x0

//draw a project figure  

#include "address_map_nios2.h"
#include "nios2_ctrl_reg_macros.h"
#include <stdio.h>
#include "JTAG_UART.c" //must add this

void clear(void);
void ducky(int, int, int, int, short); //x,y start and end, color
void moveDucky(void);

int duckyLocation1[4] = {56, 53, 60, 58};
int duckyLocation2[4] = {50, 50, 55, 55};
int duckyLocation3[4] = {50, 56, 55, 61};

int main()
{
	clear();

	//X1, Y1, X2, Y2
	ducky(duckyLocation1[0], duckyLocation1[1], duckyLocation1[2], duckyLocation1[3], 0xFA00);
	ducky(duckyLocation2[0], duckyLocation2[1], duckyLocation2[2], duckyLocation2[3], 0xFF00); //first 
	ducky(duckyLocation3[0], duckyLocation3[1], duckyLocation3[2], duckyLocation3[3], 0xFF00);  //second 
    
    while (1) {

		moveDucky();
    }

	return 0;
}

void clear() {
	//clear the screen
	ducky(0, 0, 319, 239, 0); //0, 319 and 0, 239 and black = 0
}

void ducky(int x1, int y1, int x2, int y2, short pixel_color)
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

void moveDucky() {
	
	volatile int* JTAG_UART_ptr = (int*)JTAG_UART_BASE; //must add this

	while (1) {

		char c = get_jtag(JTAG_UART_ptr);   //reading the input from the keyboard

		switch (c) {
		case 'w':
			clear();
			ducky(duckyLocation1[0], duckyLocation1[1] - 10, duckyLocation1[2], duckyLocation1[3] - 10, 0xFA00);
			duckyLocation1[1] -= 10;
			duckyLocation1[3] -= 10;
			ducky(duckyLocation2[0], duckyLocation2[1] - 10, duckyLocation2[2], duckyLocation2[3] - 10, 0xFF00); //first 
			duckyLocation2[1] -= 10;
			duckyLocation2[3] -= 10;
			ducky(duckyLocation3[0], duckyLocation3[1] - 10, duckyLocation3[2], duckyLocation3[3] - 10, 0xFF00);  //second
			duckyLocation3[1] -= 10;
			duckyLocation3[3] -= 10;
			break;

		case 'a':
			clear();
			ducky(duckyLocation1[0] - 10, duckyLocation1[1], duckyLocation1[2] - 10, duckyLocation1[3], 0xFA00);
			duckyLocation1[0] -= 10;
			duckyLocation1[2] -= 10;
			ducky(duckyLocation2[0] - 10, duckyLocation2[1], duckyLocation2[2] - 10, duckyLocation2[3], 0xFF00); //first 
			duckyLocation2[0] -= 10;
			duckyLocation2[2] -= 10;
			ducky(duckyLocation3[0] - 10, duckyLocation3[1], duckyLocation3[2] - 10, duckyLocation3[3], 0xFF00);  //second
			duckyLocation3[0] -= 10;
			duckyLocation3[2] -= 10;
			break;
		
		case 's':
			clear();
			ducky(duckyLocation1[0], duckyLocation1[1] + 10, duckyLocation1[2], duckyLocation1[3] + 10, 0xFA00);
			duckyLocation1[1] += 10;
			duckyLocation1[3] += 10;
			ducky(duckyLocation2[0], duckyLocation2[1] + 10, duckyLocation2[2], duckyLocation2[3] + 10, 0xFF00); //first 
			duckyLocation2[1] += 10;
			duckyLocation2[3] += 10;
			ducky(duckyLocation3[0], duckyLocation3[1] + 10, duckyLocation3[2], duckyLocation3[3] + 10, 0xFF00);  //second
			duckyLocation3[1] += 10;
			duckyLocation3[3] += 10;
			break;

		case 'd':
			clear();
			ducky(duckyLocation1[0] + 10, duckyLocation1[1], duckyLocation1[2] + 10, duckyLocation1[3], 0xFA00);
			duckyLocation1[0] += 10;
			duckyLocation1[2] += 10;
			ducky(duckyLocation2[0] + 10, duckyLocation2[1], duckyLocation2[2] + 10, duckyLocation2[3], 0xFF00); //first 
			duckyLocation2[0] += 10;
			duckyLocation2[2] += 10;
			ducky(duckyLocation3[0] + 10, duckyLocation3[1], duckyLocation3[2] + 10, duckyLocation3[3], 0xFF00);  //second
			duckyLocation3[0] += 10;
			duckyLocation3[2] += 10;
			break;
		}
		
	}
}