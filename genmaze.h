/**
 * GENMAZE.H
 */

#ifndef __GENMAZE_H__
#define __GENMAZE_H__

#include "debug.h"
#include "matrix.h"

typedef struct Road Road;

struct Road
{
	int x;
	int y;
	Road *back;
};

Mat *genMaze(int, int);
Mat *initMaze(Mat *);
Mat *updateMaze(Mat *);
Mat *digMaze(Mat *, int, int);
Road *newRoad(int, int, Road *);
Road *getRondomRoad(Road *);

#endif /* __GENMAZE_H__ */
