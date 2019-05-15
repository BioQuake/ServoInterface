#ifndef INPUT_H
#define INPUT_H

#define ARR_SIZE 3

#include <ncurses.h>

int cX, cY; 								//This controls the position of our cursor. Needed for Field Switching.
int selectedfield;							//This is the currently selected field.
int * inputfield[ARR_SIZE];						//Our multidimensional array. This will store the XY and VAL of our inputfields.

int drawfield(int x, int y, int size, int val, char *label);		//Function for drawing our fields.
void registerfield(int x, int y);					//Register fields here. This adds them to inputfield.
int setfieldcount(int c);						//Set the amount of fields we have here. This will allow us to allocate the memory.

#endif
