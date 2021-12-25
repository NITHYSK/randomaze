/**
 * SHOWMAZE.H
 */

#ifndef __SHOWMAZE_H__
#define __SHOWMAZE_H__

#define ESC	0x1B		//エスケープシーケンス用

#include "debug.h"
#include "matrix.h"

int showMaze(Mat *);
int updateShow(Mat *);

#endif /* __SHOWMAZE_H__ */
