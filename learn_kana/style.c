#include <iso646.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	short r, g, b;
} colour_rgb;

typedef short pal_index;

typedef short style;

enum font_style {
	// TODO: not all ANSI escape sequences are supported by most terminal emulators.
	// Especially hidden, protected, blink, strikethrough, etc.
	// I'm only using the styles widely supported for now.
	NORMAL    = 0,
	BOLD      = 1,
	DIM       = 2,
	ITALIC    = 4,
	UNDERLINE = 8,
	REVERSE   = 16,
};

typedef struct {
	colour_rgb* rgb;
	pal_index   palette;
	style       styles;
	bool        reset;
} font_attrs;

void set_style( font_attrs* fa, enum font_style st ) {
	fa->styles |= st;
	fa->reset   = false;
}

void set_pal_index( font_attrs* fa, short index ) {
	fa->palette = index;
	fa->reset   = false;
}

void set_rgb_colour( font_attrs* fa, colour_rgb* rgb ) {
	fa->rgb   = rgb;
	fa->reset = false;
}

void reset_attr( font_attrs* fa ) {
	fa->rgb     = NULL;
	fa->palette = 0;
	fa->styles  = 0;
	fa->reset   = true;
}

void send_code( FILE* f, font_attrs* attrs ) {
	if ( attrs->reset ) {
		fprintf( f, "[0m" );
		return;
	}

	char code[ 100 ];
	for ( int i = 0; i < 100; ++i ) {
		code[ i ] = '\0';
	}

	int last = 0;

	// Styles are cummulative.
	int   on[ 8 ], idx = 0;
	short styles = attrs->styles;
	if ( ( styles & BOLD ) == BOLD ) {
		on[ idx ] = 1;
		++idx;
	}
	if ( ( styles & DIM ) == DIM ) {
		on[ idx ] = 2;
		++idx;
	}
	if ( ( styles & ITALIC ) == ITALIC ) {
		on[ idx ] = 3;
		++idx;
	}
	if ( ( styles & UNDERLINE ) == UNDERLINE ) {
		on[ idx ] = 4;
		++idx;
	}
	if ( ( styles & REVERSE ) == REVERSE ) {
		on[ idx ] = 7;
		++idx;
	}

	for ( int i = 0; i < idx; ++i ) {
		code[ last++ ] = '0' + on[ i ];
		if ( i < idx - 1 ) {
			code[ last++ ] = ';';
		}
	}

	if ( attrs->rgb ) {
		if ( last > 0 ) {
			code[ last ] = ';';
		}
		char ccode[ 20 ] = "38:2:";
		char rgb[ 5 ];
		sprintf( rgb, "%d:", attrs->rgb->r );
		strcat( ccode, rgb );
		sprintf( rgb, "%d:", attrs->rgb->g );
		strcat( ccode, rgb );
		sprintf( rgb, "%d", attrs->rgb->b );
		strcat( ccode, rgb );
		strcat( code, ccode );
	} else if ( attrs->palette > -1 and attrs->palette < 256 ) {
		if ( last > 0 ) {
			code[ last ] = ';';
		}
		char ccode[ 10 ];
		sprintf( ccode, "38:5:%d", attrs->palette );
		strcat( code, ccode );
	}


	fprintf( f, "[%sm", code );
	// Uncomment for debugging:
	// fprintf( f, "\n-- %s --\n", code );
}
