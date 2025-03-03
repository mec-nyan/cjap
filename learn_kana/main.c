#include <iso646.h>
#include <stdio.h>
#include "curmanip.c"
#include "kana.c"
#include "style.c"

void print_info( void );


int main( void ) {
	/*printf("%s%s%s%s\n", hg_hi, hg_ra, hg_ga, hg_na);*/

	struct termios saved = setup();

	print_info();

	save_pos();

	type( "Are you ready for some kana fun? " );
	fgetc( stdin );

	restore_pos();
	clr_to_eos();

	type( "Goodbye!\n" );


	clean( &saved );
}

void print_info( void ) {
	font_attrs fa = { NULL, 0, 0 };
	set_style( &fa, DIM );
	send_code( stdout, &fa );

	fprintf( stdout, "learn-kana v0.0.1!\n" );

	const char* term = getenv( "TERM" );
	term != NULL ? fprintf( stdout, "Terminal: %s.\n", term ) : 0;

	int lines = 0, cols = 0;
	get_term_size( &lines, &cols );

	lines != 0 ? fprintf( stdout, "Dimensions: %d lines x %d columns.\n", lines, cols )
			   : fprintf( stderr, "Unknown dimensions.\n" );

	reset_attr( &fa );
	send_code( stdout, &fa );

	fflush( stdout );
}
