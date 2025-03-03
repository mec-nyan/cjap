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
	colour_rgb orangy = { 242, 177, 121 };
	font_attrs fa     = { &orangy, -1, 0, false };
	send_code( stdout, &fa );

	type( "Are you ready for some kana fun? " );
	fgetc( stdin );

	restore_pos();
	clr_to_eos();

	colour_rgb bluey = { 0x79, 0xf2, 0xe8 };
	set_rgb_colour( &fa, &bluey );
	set_style( &fa, BOLD );
	set_style( &fa, REVERSE );
	send_code( stdout, &fa );

	type( "~ Goodbye! ~\n" );


	clean( &saved );
}

void print_info( void ) {
	font_attrs fa = {
		.rgb     = NULL,
		.palette = 5,
		.styles  = 0,
		.reset   = false,
	};
	send_code( stdout, &fa );

	fprintf( stdout, "learn-kana v0.0.1 🌸!\n" );

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
