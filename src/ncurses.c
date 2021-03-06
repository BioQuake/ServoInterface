// Program and adapter written by Kevin Huisman (Quake)

/* INPUT SHEET
	UP-DN	= SWITCH TABS
	TAB	= SWITCH SELECTION
	ENTER	= EDIT FIELD VALUE
	F1	= EXIT
*/

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <form.h>
#include "input.h"

//Input keys.
#define Key_Up	 		KEY_UP
#define Key_F1 			KEY_F(1)
#define Key_F2			KEY_F(2)
#define Key_F3			KEY_F(3)
#define Key_Return		KEY_ENTER

//These are our UTF-8 codes for the Character blocks. Used for drawing Screen Elements.
#define Solid_Block 		(char)		0x2588
#define Top_Right 		(char)		0x256E
#define Top_Left 		(char)		0x256D
#define Bottom_Left		(char)		0x2570
#define Bottom_Right		(char)		0x256F
#define Joint_Left 		(char)		0x2524
#define Joint_Right		(char)		0x251C
#define Vertical_Border		(char)		0x2502
#define Horizontal_Border 	(char)		0x2500

//Coloursets. Defined here for ease of implementation.
#define Foreground		1
#define Status_Bar		2
#define Value_Field		3
#define Background		4
#define Border			5
#define Error			6

//Panel Data.
#define Main_Margin_U		2
#define Main_Margin_D		3
#define Main_Margin_L		5
#define Main_Margin_R		5
#define Shadow_Offset		1

//Our terminal MUST be 159x36!!!!
#define Term_Height		36
#define Term_Width		159

int main()
{
	
	//Variable Declarations.
	int ch;						//Char int (Used for handling input).

	//Initialise the stuff we need to draw our window, our form, and our input fields.
	initscr();					//Initialize ncurses.
	raw();						//Raw Input (No Escape Characters).
	keypad(stdscr,TRUE);				//Allow the capture of F1-F12. All input gets passed to prog.
	noecho();					//Disable Echo.
	cbreak();					//cbreak mode.
	curs_set(0);					//Hide the cursor.	
	setfieldcount(3);
	
	//Check if our terminal supports colours. If not, shut down.
	if (has_colors() == FALSE)
	{	
		attron(A_BLINK | A_BOLD);
		printw("Your Terminal does not support colours. ServInterface only works on terminals with colour support.");
		getch();
		endwin();
		exit(1);	
	}
	
	//If we got to this point, our terminal should support colours. Lets define our coloursets.
	start_color();					//Start handling the colours.
	init_pair(Foreground, COLOR_BLACK, COLOR_WHITE);
	init_pair(Background, COLOR_BLUE, COLOR_BLUE);
	init_pair(Status_Bar, COLOR_BLACK, COLOR_WHITE);
	init_pair(Error, COLOR_WHITE, COLOR_RED);
	
	//Warn user to set their terminal mode correctly.
	if(COLS != Term_Width || LINES != Term_Height)
	{
		attron(COLOR_PAIR(Error) | A_BLINK | A_BOLD);
		printw("Your Terminal Mode is not set to %ix%i. Please make sure your Terminal Mode is set correctly.", Term_Width, Term_Height);
		getch();
		endwin();
		exit(1);
	}
	
	//Program loop
	do
	{
		//Set our cursor to 0,0, so we don't mess up the window drawing, and can get our cursor drawn correctly.
		move(0,0);
		//Draw our screen.
		//Iterating through the horizontal axis. The size of this is Term_Width.
		for (int hIter = 0; hIter < Term_Height; hIter++)
			{
				//Iterating through the vertical axis. The size of this is Term_Height
				for (int wIter = 0; wIter < Term_Width; wIter++)
				{
					//If the current block is INSIDE the window we're going to draw.
					if(hIter >  Main_Margin_U 
					&& hIter < Term_Height - Main_Margin_D 
					&& wIter > Main_Margin_L 
					&& wIter < Term_Width - Main_Margin_R)
					{
						attron(COLOR_PAIR(Foreground));		//Set our colourpair to that of the Foreground.
						addch(' ');
						attroff(COLOR_PAIR(Foreground));

					}
					//If not, it's outside and slightly below and to the right, thus we should draw the drop shadow.
					else if (hIter == Term_Height - Main_Margin_D  
					&& wIter-Shadow_Offset < Term_Width - Main_Margin_R 
					&& wIter > Main_Margin_L+Shadow_Offset
					|| wIter == Term_Width - Main_Margin_R 
					&& hIter-Shadow_Offset > Main_Margin_U 
					&& hIter < Term_Height-Main_Margin_D+Shadow_Offset)
					{
						attron(COLOR_PAIR(Foreground));		//Set our colourpair to that of the Foreground.
						addch(Solid_Block);
						attroff(COLOR_PAIR(Foreground));	
					}
					//Draw our border at the lowest position.
					else if (hIter == Term_Height-1)
					{
						attron(COLOR_PAIR(Status_Bar));		//Set our colourpair to that of the Border.
						addch(' ');
						attroff(COLOR_PAIR(Status_Bar));
					}
					//And if the character is outside of the main window, draw our background.
					else
					{
						attron(COLOR_PAIR(Background)); 	//Set our colourpair to that of the Background.
						addch(' ');
						attroff(COLOR_PAIR(Background));
					}
				}
			}
		//Draw our controls on the lower border.
		attron(COLOR_PAIR(Status_Bar));
		mvaddstr(Term_Height-1, Main_Margin_L,"	  ServInterface.									EXIT = F1   CYCLE FIELDS = UP/DN    EDIT VALUE = RETURN	   kq		");
		attroff(COLOR_PAIR(Status_Bar));
		drawfield(5,10,5,102,"Servo 1: ");
		drawfield(7,10,5,253,"Servo 2: ");
		drawfield(9,10,5,23,"Servo 3: ");
	
	//Now that our fields are drawn, we'll handle the input and fields.
	
	//If enter is pressed 
	if ((ch = getch()) == Key_Return)
	{
		while((ch = getch)) != Key_Return)	//While enter is not pressed
			//inputfield[][] is value.
	}
							
	}while((ch = getch()) != Key_F1);//Wait for user input before either refreshing, or shutting down.
	
	releasefields();		//Release the memory our fields use.
	endwin();			//Close our window.
	return 0;
}
