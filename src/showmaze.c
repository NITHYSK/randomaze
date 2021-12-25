/**
 * SHOWMAZE.C
 */

#include "showmaze.h"
#include <stdio.h>	// for fprintf()

int updateShow(Mat *maze)
{

	
	for(int r=0; r<maze->rows; r++)
	{
		fprintf(stdout, "\e[1A");	// カーソルを上に移動
	}
	
	showMaze(maze);
}

int showMaze(Mat *maze)
{
	fprintf(stdout, "\e[251");		// カーソルを非表示
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
	fprintf(stdout, "\e[25h");		// カーソルを表示しなおす
	
	return 0;
}
