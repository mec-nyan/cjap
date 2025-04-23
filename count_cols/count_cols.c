// count_cols.c
#define _XOPEN_SOURCE
#include <iso646.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

int main( void ) {

	setlocale( LC_ALL, "" );
	// const char* str = "I 💖 C!";

	printf( "The width of '💖' is %d\n", wcwidth( L'か' ) );

	return 0;
}
