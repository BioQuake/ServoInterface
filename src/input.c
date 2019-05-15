#include <stdlib.h>
#include <string.h>
#include "input.h"

//Input function file.
int drawfield(int x, int y, int size, int val, char *label)
{
    mvaddstr(x,y,label);				//Move our cursor to X, Y and Display our Label
    for(int iter = 0; iter < size; iter++)		//Write our Value/Whitespace
    {
        addch(' ');					//Draw the whitespace
    }
    move(x,strlen(label)+y);				//Move to the value field.
    printw("%i",val);
    move(0,0); 
    return 0;
}

//Register our fields. This will allow us to switch our cursor to get the input working.
void registerfield(int x, int y)
{
    //We're going to be doing some manual memory management here, so we need to be VERY careful to not mess up.
        
}

//Set the count of our fields; used to switch between them.
int setfieldcount(int c)
{
    //Memalloc stuff here. Be very careful with this.
    //Since we're goint to be allocating a multi-dimensional array, we're going to have to
    //Use a loop to get to every element.

    for (int i=0; i<ARR_SIZE; i++) 
         inputfield[i] = (int *)malloc(c * sizeof(int));     
}

//This is for deallocating the memory we have allocated for the twodimensional array.
int releasefields()
{
    for (int i=0; i<ARR_SIZE; i++)
    {
        free(inputfield[i]);
    }
    free(inputfield);
}
