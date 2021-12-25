/**
 * ERROR.C
 */

#include "error.h"
#include <stdarg.h>	// for va_args
#include <stdlib.h>	// for exit()
#include <stdio.h>	// for fprintf()

int error(int errcode, char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	fprintf(stderr, "ERROR %x8 : ", errcode);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	va_end(ap);
	exit(1);
}
