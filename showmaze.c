/**
 * SHOWMAZE.C
 */

#include "showmaze.h"
#include <stdio.h>	// for fprintf()

int updateShow(Mat *maze)
{

	
	for(int r=0; r<maze->rows; r++)
	{
		fprintf(stdout, "\e[1A");
	}
	
	showMaze(maze);
}

int showMaze(Mat *maze)
{
	for(int r=0; r<maze->rows; r++)
	{
		for(int c=0; c<maze->cols; c++)
		{
			if(getElem(maze, c, r))
			{
				fprintf(stdout, "\x1b[7m \x1b[0m");
			} else {
				fprintf(stdout, " ");
			}
		}
		fprintf(stdout, "\n");
	}
	
	return 0;
}
