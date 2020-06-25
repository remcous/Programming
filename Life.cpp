// Conway's Game of Life
// Life.cpp
// #1 Any live cell with less than 2 neighbours dies of underpopulation
// #2 Any live cell with exactly 2 or 3 neightbours lives on to next generation
// #3 Any live cell with more than 3 neighbours dies of overpopulation
// #4 Any dead cell with exactly 3 neighbours becomes a live cell, as by reproduction

#include <iostream>
#include <string>
#include <windows.h>
#include <stdlib.h>
using namespace std;

// Obtain handle to the console screen buffer
HANDLE HCONSOLE = GetStdHandle(STD_OUTPUT_HANDLE);

// Constants to define operating conditions
int NUM_CYCLES = 5000;
int PAUSE_TIME = 300;
char LIVE_CELL = '1';
char DEAD_CELL = ' ';

// Function Prototypes
void copy(string* input, string*output, int size);
void print(string grid[], int vert);
void gotoXY(int column, int row);

// **********************************************************************************
// *										MAIN									*
// **********************************************************************************

int main(){
	int vert, horz;	// store size of game board
	int count;		// used to evaluate rule conditions
	int x, y;		// x,y position of starting coordinate on console

	// Clear console
	system("cls");
	
	// Get coordinate of starting position
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(HCONSOLE, &info);
	x = info.dwCursorPosition.X;
	y = info.dwCursorPosition.Y;
	
	// Starting condition of game board: DEAD_CELL for dead, LIVE_CELL for living
	string grid[] = {		{"                  "},
							{"                  "},
							{"                  "},
							{"                  "},
							{"      1    1      "},
							{"    11 1111 11    "},
							{"      1    1      "},
							{"                  "},
							{"                  "},
							{"                  "},
							{"                  "}};

	// determine size of game board for calculations
	vert = sizeof(grid)/sizeof(grid[0]);
	horz = grid[0].length();
	string *grid_old;
	grid_old = new string[vert];

	// Print starting board
	copy(grid, grid_old, vert);
	print(grid, vert);
	Sleep(PAUSE_TIME);

	for(int k=0; k < NUM_CYCLES; k++){	// Run for designated number of cycles
		for(int j=0; j<vert; j++){		// Iterate through vertical
			for(int i=0; i<horz; i++){	// Iterate through horizontal
				// Reset count to zero
				count = 0;

				// Check neighbours if possible (check for edges)
				if(i-1 >= 0){	// not on West edge
					if(grid_old[j][i-1] == LIVE_CELL)	// check W
						count++;
					if(j-1 >= 0){	// not on South edge
						if(grid_old[j-1][i-1] == LIVE_CELL)	// Check SW
							count++;
					}
					if(j+1 < vert){	// not on North edge
						if(grid_old[j+1][i-1] == LIVE_CELL)	// Check NW
							count++;
					}
				}
				if(i+1 < horz){	// not on East edge
					if(grid_old[j][i+1] == LIVE_CELL)	// Check E
						count++;
					if(j-1 >= 0){	// not on South edge
						if(grid_old[j-1][i+1] == LIVE_CELL)	// Check SE
							count++;
					}
					if(j+1 < vert){	// not on North edge
						if(grid_old[j+1][i+1] == LIVE_CELL)	// Check NE
							count++;
					}
				}
				if(j-1 >= 0){	// not on South edge
					if(grid_old[j-1][i] == LIVE_CELL)	// Check S
						count++;
				}
				if(j+1 < vert){	// not on North edge
					if(grid_old[j+1][i] == LIVE_CELL)	// Check N
						count++;
				}

				if(grid_old[j][i] == LIVE_CELL)	// Current cell is live
				{
					// **********************************************************************************
					// #1 Any live cell with less than 2 neighbours dies of underpopulation
					// **********************************************************************************
					if(count < 2){
						grid[j][i] = DEAD_CELL;
					}
					
					// **********************************************************************************
					// #2 Any live cell with exactly 2 or 3 neightbours lives on to next generation
					// **********************************************************************************
					
					// Do nothing

					// **********************************************************************************
					// #3 Any live cell with more than 3 neighbours dies of overpopulation
					// **********************************************************************************

					if(count > 3){
						grid[j][i] = DEAD_CELL;
					}
				}
				else	// Current cell is dead
				{
					// **********************************************************************************
					// #4 Any dead cell with exactly 3 neighbours becomes a live cell, as by reproduction
					// **********************************************************************************

					if(count == 3){
						grid[j][i] = LIVE_CELL;
					}
				}
			}
		}

		print(grid,vert);			// Print updated grid over old grid
		copy(grid, grid_old, vert);	// update grid_old with data from this iteration
		Sleep(PAUSE_TIME);			// Pause to allow user to see changes
		gotoXY(x,y);				// Move back to initial position on console
	}

	// Free dynamically allocated storage
	delete[] grid_old;
	return 0;
}

// Method to copy one string array to another
void copy(string* input, string*output, int size){
	for(int i=0; i < size; i++){
		output[i] = input[i];
	}
}

// Print the contents of a string array separated by line breaks
void print(string str[], int vert){
	for(int i=0; i<vert; i++){
		std::cout << str[i] << endl;
	}
}

// Move the console pointer to a specified location
void gotoXY(int column, int row){
	// create a coordinate variable set to the specified parameter location
	COORD coord;
	coord.X = column;
	coord.Y = row;

	// Call SetConsoleCursorPosition
	if(!SetConsoleCursorPosition(HCONSOLE, coord)){
		// Error handling
		cerr << "Unable to move console cursor to specified position" << endl;
	}
}