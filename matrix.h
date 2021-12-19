/**
 * MATRIX.H
 */

#ifndef __MATRIX_H__
#define __MATRIX_H__

#define ERROR_OUT_OF_MAT	0x0070F3A7
#define ERROR_SIZES_DONT_MATCH	0xD1FF512E

#include "debug.h"
#include "error.h"

typedef struct Mat Mat;

struct Mat {
	int rows;
	int cols;
	int *mat;
};

Mat *matcpy(Mat *, Mat *);
int num2x(Mat *, int);
int num2y(Mat *, int);
int xy2num(Mat *, int, int);
int getElem(Mat *, int, int);
int setElem(int, Mat *, int, int);
int isOutofMat(Mat *, int, int);

#endif /* __MATRIX_H__ */
