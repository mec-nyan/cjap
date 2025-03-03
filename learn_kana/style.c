#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	short r, g, b;
} colour_rgb;

typedef short pal_index;

typedef short style;

enum font_style {
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
} font_attrs;

void set_style( font_attrs* fa, enum font_style st ) {
	fa->styles |= st;
}

void set_pal_index( font_attrs* fa, short index ) {
	fa->palette = index;
}

void set_rgb_colour( font_attrs* fa, colour_rgb* rgb ) {
	fa->rgb = rgb;
}

void reset_attr( font_attrs* fa ) {
	fa->rgb     = NULL;
	fa->palette = 0;
	fa->styles  = 0;
}

void send_code( FILE* f, font_attrs* attrs ) {
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

	fprintf( f, "[%sm", code );
}
