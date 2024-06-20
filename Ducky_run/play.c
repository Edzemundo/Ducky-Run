/* Duck game final project by Manreet, Joe and Edmund
this is the main function used to run the game. It requires all
the library files listed below including the custom "map_box.c" file.
*/

//yellow 0xFF00, red 0xFA00, Green 0x1CE0, Blue 0x001F, black 0x0

 
//included libraries and files
#include "address_map_nios2.h"
#include "nios2_ctrl_reg_macros.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "JTAG_UART.c" //must add this
#include "map_box.c"

//Function prototypes
void clear(void);
void ducky(int, int, int, int, short); //x,y start and end, color
void moveDucky(void);
void eatBox(void);
void VGA_text_display(int, int, char*);
void game_over(void);
void you_win(void);

//initial location of the main character(duck)
int duckyLocation1[4] = {56 + 30, 53, 60 + 30, 58};
int duckyLocation2[4] = {50 + 30, 56, 55 + 30, 61};
int duckyLocation3[4] = {50 + 30, 56, 55 + 30, 61};

//"score:..." shown at the bottom right of screen
char text[20] = "Score: \0";

//variables used in multiple functions
extern int box[17][6];	//array that includes details on the boxes for the map
int sumScore = 0;	//total score variable
int ones, tens, hundreds;	//varaibles for splitting up the score for displaying it on the screen as text


int main()
{
	//clear the screen
	clear();
	
	//X1, Y1, X2, Y2
	//create the duck at its initial location
	ducky(duckyLocation1[0], duckyLocation1[1], duckyLocation1[2], duckyLocation1[3], 0xFA00);
	ducky(duckyLocation2[0], duckyLocation2[1], duckyLocation2[2], duckyLocation2[3], 0xFF00); //first 
	ducky(duckyLocation3[0], duckyLocation3[1], duckyLocation3[2], duckyLocation3[3], 0xFF00);  //second 
    
	//while loop for running continuously
    while (1) {

		//separate the score into the ones, tens and hundreds
		ones = sumScore % 10;
		tens = (sumScore / 10) % 10;
		hundreds = (sumScore / 100) % 10;

		//Place the score values into the "text" character array to be shown on the screen
		text[9] = ones + '0';
		text[8] = tens + '0';
		text[7] = hundreds + '0';


		//if all the boxes not yet been grabbed
		if (sumScore < 420) {
			moveDucky();	//ability to move the duck
			mapify();	//create the updated map
			eatBox();	//edit any boxed that have been grabbed
			VGA_text_display(50, 50, text);	//show the updated text on the screen
		}

		//else if all the boxes have been grabbed, show the winning screen
		else if (sumScore >= 420) {
			text[8] = '2';
			VGA_text_display(50, 50, text);
			you_win();
			exit(0);
		}
    }

	return 0;
}


//function definition to clear the screen
void clear() {
	//clear the screen
	ducky(0, 0, 319, 239, 0); //0, 319 and 0, 239 and black = 0
}


//function definition to create the duck at a specified location
void ducky(int x1, int y1, int x2, int y2, short pixel_color)
{
	int pixel_ptr, row, col;

	for (row = y1; row <= y2; row++)	//for each row
	{
		for (col = x1; col <= x2; col++)	//for each column
		{
			pixel_ptr = FPGA_ONCHIP_BASE + (row << 10) + (col << 1);
			*(short*)(pixel_ptr) = pixel_color;
		}
	}
}


//function definition to grab the keyboard input and move the ducks position based on key input
void moveDucky() {
	
	volatile int* JTAG_UART_ptr = (int*)JTAG_UART_BASE; //must add this
	char c = get_jtag(JTAG_UART_ptr);   //reading the input from the keyboard

	//case statement for various inputs
	switch (c) {
	case 'w':
		clear();
		ducky(duckyLocation1[0], duckyLocation1[1] - 5, duckyLocation1[2], duckyLocation1[3] - 5, 0xFA00);
		duckyLocation1[1] -= 5;
		duckyLocation1[3] -= 5;
		ducky(duckyLocation2[0], duckyLocation2[1] - 5, duckyLocation2[2], duckyLocation2[3] - 5, 0xFF00); //first 
		duckyLocation2[1] -= 5;
		duckyLocation2[3] -= 5;
		ducky(duckyLocation3[0], duckyLocation3[1] - 5, duckyLocation3[2], duckyLocation3[3] - 5, 0xFF00);  //second
		duckyLocation3[1] -= 5;
		duckyLocation3[3] -= 5;
		break;

	case 'a':
		clear();
		ducky(duckyLocation1[0] - 5, duckyLocation1[1], duckyLocation1[2] - 5, duckyLocation1[3], 0xFA00);
		duckyLocation1[0] -= 5;
		duckyLocation1[2] -= 5;
		ducky(duckyLocation2[0] - 5, duckyLocation2[1], duckyLocation2[2] - 5, duckyLocation2[3], 0xFF00); //first 
		duckyLocation2[0] -= 5;
		duckyLocation2[2] -= 5;
		ducky(duckyLocation3[0] - 5, duckyLocation3[1], duckyLocation3[2] - 5, duckyLocation3[3], 0xFF00);  //second
		duckyLocation3[0] -= 5;
		duckyLocation3[2] -= 5;
		break;
	
	case 's':
		clear();
		ducky(duckyLocation1[0], duckyLocation1[1] + 5, duckyLocation1[2], duckyLocation1[3] + 5, 0xFA00);
		duckyLocation1[1] += 5;
		duckyLocation1[3] += 5;
		ducky(duckyLocation2[0], duckyLocation2[1] + 5, duckyLocation2[2], duckyLocation2[3] + 5, 0xFF00); //first 
		duckyLocation2[1] += 5;
		duckyLocation2[3] += 5;
		ducky(duckyLocation3[0], duckyLocation3[1] + 5, duckyLocation3[2], duckyLocation3[3] + 5, 0xFF00);  //second
		duckyLocation3[1] += 5;
		duckyLocation3[3] += 5;
		break;

	case 'd':
		clear();
		ducky(duckyLocation1[0] + 5, duckyLocation1[1], duckyLocation1[2] + 5, duckyLocation1[3], 0xFA00);
		duckyLocation1[0] += 5;
		duckyLocation1[2] += 5;
		ducky(duckyLocation2[0] + 5, duckyLocation2[1], duckyLocation2[2] + 5, duckyLocation2[3], 0xFF00); //first 
		duckyLocation2[0] += 5;
		duckyLocation2[2] += 5;
		ducky(duckyLocation3[0] + 5, duckyLocation3[1], duckyLocation3[2] + 5, duckyLocation3[3], 0xFF00);  //second
		duckyLocation3[0] += 5;
		duckyLocation3[2] += 5;
		break;
	}

	//if the duck goes beyond the bounds of the screen, activate the game over screen
	if (duckyLocation1[0] < 0 || duckyLocation1[0] > 319 || duckyLocation1[1] < 0 || duckyLocation1[1] > 239) {
		game_over();
		exit(0);
	}

	// printf("%d\n", duckyLocation1[0]);
	// printf("%d\n", duckyLocation1[1]);
}


//function definition for grabbing the boxes
void eatBox(void) {
	int i, j;
	
	//checks if the duck's beak is within the bounds of any box
	for (i = 0; i < 17; i++){
		if((duckyLocation1[0] >= box[i][0] && duckyLocation1[2] <= box[i][2]) && (duckyLocation1[1] >= box[i][1] && duckyLocation1[3] <= box[i][3])) {
			for (j=0; j<5; j++){
				box[i][j] = 0;
			}
			sumScore += box[i][5];
			
			printf("eaten\n");
			printf("%d", sumScore);
		}
	}
	
}


//function definition for displaying text on the screen
void VGA_text_display(int x, int y, char* text_ptr) {
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


//function definition for showing the game over screen
void game_over(void) {
	clear();
	char message[30] = "GAME OVER!        \0";
	VGA_text_display(35, 29, message);
}


//function definition for showing the 'you win' screen
void you_win(void) {
	clear();
	char message[30] = "GOOD JOB! YOU WIN!\0";
	VGA_text_display(35, 29, message);
}