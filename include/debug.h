/**
 * DEBUG.H
 */

#ifndef __DEBUG_H__
#define __DEBUG_H__

#ifdef _DEBUG

#include <stdio.h>

#define disp_debug(...)	\
	do	\
	{	\
		fprintf(stdout, "%s	%d	%s	",	\
				__FILE__, __LINE__, __func__);	\
		fprintf(stdout, __VA_ARGS__);	\
		fprintf(stdout, "\n");	\
	} while(0)

#else

#define disp_debug(...)

#endif /* _DEBUG */

#endif /* __DEBUG_H__ */
