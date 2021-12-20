/**
 * MAIN.C
 */

//#define _DEBUG
#define _NODEBUG

#define ERROR_ARGC	0xAC15D1FF
#define ERROR_BADSIZE	0xBAD512E
#define ERROR_NOTODD	0x2070DD

#define default_width	17
#define default_height	17

#include "stdafx.h"

int main(int argc, char **argv)
{
	if(argc != 3 && argc != 1)
	{
		error(ERROR_ARGC, "Number of argments is different .");
	}
	if(!argv[1]%2 || !argv[2]%2)
	{
		error(ERROR_NOTODD, "コマンドライン引数には奇数を入力してください");
	}

	Mat *maze;
	if(argc == 3)
	{
		maze = genMaze(atoi(argv[1]), atoi(argv[2]));
	} else {
		maze = genMaze(default_width, default_height);
	}
	//printf("maze generated. \n");
	showMaze(maze);

	//getchar();
	initMaze(maze);
	//printf("maze initiated. \n");
	//updateShow(maze);

	digMaze(maze, 1, 1);

	printf("maze generated. \n");

	struct winsize ws;

		
	for(;;)
	{
		if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
		{
			error(ERROR_BADSIZE, "WINDOWSIZE IS BAD");
			exit(1);
		}

		switch(isInterrupt())
		{
			case 'q':
				exit(0);

			case (char)0x0A: // ENTER
				break;

			default:
				break;
		}
	}

	return 0;
}

