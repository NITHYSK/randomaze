/**
 * MATRIX.C
 */

#include "matrix.h"

Mat *matcpy(Mat *src, Mat *dst)
{
	if(
			src->rows != dst->rows ||
			src->cols != dst->cols
	  )
	{
		error(ERROR_SIZES_DONT_MATCH, "The sizes don't match.");
	}
	for(int r=0; r<src->rows; r++)
	{
		for(int c=0; c<src->cols; c++)
		{
			setElem(	getElem(src, c, r),
					dst, c, r
			       );
		}
	}
	return dst;
}

int getElem(Mat *src, int x, int y)
{
	if(isOutofMat(src, x, y))
	{
		error(ERROR_OUT_OF_MAT, "Elem is Out of Mat !");
	}

	return src->mat[xy2num(src,x,y)];
}

int setElem(int src, Mat *dst, int x, int y)
{
	if(isOutofMat(dst, x, y))
	{
		error(ERROR_OUT_OF_MAT, "Elem is Out of Mat !");
	}

	dst->mat[xy2num(dst,x,y)] = src;
	
	return 0;
}

int isOutofMat(Mat *mat, int x, int y)
{
	return	x < 0 || mat->cols <= x ||
		y < 0 || mat->rows <= y;
}

int num2x(Mat *mat, int num)
{
	return num % mat->cols;
}

int num2y(Mat *mat, int num)
{
	return num / mat->cols;
}

int xy2num(Mat *mat, int x, int y)
{
	return y * mat->cols + x;
}
