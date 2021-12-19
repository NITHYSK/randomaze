/**
 * GENMAZE.C
 */

#define dir_right	0
#define dir_left	1
#define dir_down	2
#define dir_up		3
#define init_x	1
#define init_y	1

#include "genmaze.h"
#include "showmaze.h"
#include <stdlib.h>	// for srand()
#include <time.h>	// for seed

int fill(int, Mat *);
int _4dise();
int ndise(int);
int randig(Mat *, int, int);
Road *dig2(Mat *, int, int, int);
int lookElem(Mat *, int, int);
int ahead(Mat *, int, int, int);
int isDeadEnd(Mat *, int, int);
int isGenComp(Mat *);
Road *getRandRoad(Road *);

Road *headroad;
Road *oddpos;

Mat *genMaze(int rows, int cols)
{
	Mat *maze = (Mat *)malloc(sizeof(Mat));
	maze->rows	= rows;
	maze->cols	= cols;
	maze->mat	= (int *)calloc(rows*cols, sizeof(int));
	fill(1, maze);
	return maze;
}

Mat *initMaze(Mat *maze)
{
	headroad = newRoad(init_x, init_y, (Road *)NULL);
	setElem(0, maze, init_x, init_y);
	//digMaze(maze, x, y);
	return maze;
}

Mat *updateMaze(Mat *maze)
{
	int x=1;
	int y=1;

	headroad = newRoad(x, y, (Road *)NULL);

	setElem(0, maze, x, y);

	digMaze(maze, x,y);

	return maze;
}

Mat *digMaze(Mat *maze, int x, int y)
{
	disp_debug("start");

	if(isGenComp(maze))
	{
		return maze;
	}

	while(!isDeadEnd(maze, x, y))
	{
		int digdir;
		do
		{
			digdir = _4dise();
		} while(!ahead(maze, x, y, digdir)); // 2つ先が0,つまり通路である限りダイスを振り直す
		disp_debug("x	= %d", x);
		disp_debug("y	= %d", y);
		disp_debug("digdir	= %d", digdir);
		//updateShow(maze);
		
		headroad = dig2(maze, x, y, digdir);
		x = headroad->x;
		y = headroad->y;
		updateShow(maze);
		
		//if(getchar() == 'q') exit(0);
	}

	do
	{
		int randpos = ndise(maze->rows * maze->cols);
		x = ndise(maze->cols/2) * 2 + 1;
		y = ndise(maze->rows/2) * 2 + 1;
	} while(getElem(maze, x, y) != 0);

	headroad = newRoad(x, y, headroad);
	//headroad = getRandRoad(headroad);
	//updateShow(maze);

	disp_debug("end");
	return digMaze(maze, headroad->x, headroad->y);
}

Road *dig2(Mat *maze, int x, int y, int dir)
{
	Road *newroad = newRoad(x, y, headroad);
	for(int i=0; i<2; i++)
	{
		switch(dir)
		{
			case dir_right:
				setElem(0, maze, ++x, y);
				newroad->x++;
				break;
			case dir_down:
				setElem(0, maze, x, ++y);
				newroad->y++;
				break;
			case dir_left:
				setElem(0, maze, --x, y);
				newroad->x--;
				break;
			case dir_up:
				setElem(0, maze, x, --y);
				newroad->y--;
				break;
			default:
				break;
		}
	}

	return newroad;
}

int isGenComp(Mat *maze)
{
	for(int r=0; r<maze->rows; r++)
	{
		for(int c=0; c<maze->cols; c++)
		{
			if(r%2 && c%2) // r, cともに奇数ならば
			{
				if(getElem(maze, c ,r) != 0)
				{
					return 0;
				}
			}
		}
	}
	return 1;
}

int isDeadEnd(Mat *maze, int x, int y)
{
	disp_debug("start");
	int count = ahead(maze, x, y, dir_right)	+
		    ahead(maze, x, y, dir_down)		+
		    ahead(maze, x, y, dir_left)		+
		    ahead(maze, x, y, dir_up);
	disp_debug("end count = %d", count);
	if(count == 0)
	{
		return 1;
	} else {
		return 0;
	}
}

/* 2 squares ahead */
int ahead(Mat *maze, int x, int y, int digdir)
{
	switch(digdir)
	{
		case dir_right:
			return lookElem(maze, x+2, y);
			break;
		case dir_left:
			return lookElem(maze, x-2, y);
			break;
		case dir_up:
			return lookElem(maze, x, y-2);
			break;
		case dir_down:
			return lookElem(maze, x, y+2);
			break;
		default:
			break;
	}
}

int lookElem(Mat *mat, int x, int y)
{
	if(isOutofMat(mat, x, y))
	{
		return 0; // 外周は通路とする
	} else {
		return getElem(mat, x, y);
	}
}

int fill(int state, Mat *mat)
{
	for(int r=0; r<mat->rows; r++)
	{
		for(int c=0; c<mat->cols; c++)
		{
			setElem(state, mat, c, r);
		}
	}
	return 0;
}

int countRoad(Road *rp)
{
	if(rp->back == (Road *)NULL)
	{
		return 0;
	} else {
		return 1 + countRoad(rp);
	}
}

Road *getRandRoad(Road *road)
{
	int nr = countRoad(headroad);
	int num = ndise(nr);
	
	Road *rp = headroad;
	for(int i=0; i<num; i++)
	{
		rp = rp->back;
	}
	return rp;
}

Road *newRoad(int x, int y, Road *road)
{
	Road *newroad = (Road *)malloc(sizeof(Road));
	newroad->x = x;
	newroad->y = y;
	newroad->back = road;
	return newroad;
}

int ndise(int n)
{
	srand((unsigned int) clock());
	return rand()%n;
}

int _4dise()
{
	srand((unsigned int) clock());
	return rand()%4;
}

