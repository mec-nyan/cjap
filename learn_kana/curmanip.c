#include "term.c"

void save_pos( void ) {
	to_stdout( "7" );
}

void restore_pos( void ) {
	to_stdout( "8" );
}

void home( void ) {
	to_stdout( "[H" );
}

void clr_to_eol( void ) {
	to_stdout( "[K" );
}

void clr_to_bol( void ) {
	to_stdout( "[1K" );
}

void clr_to_eos( void ) {
	to_stdout( "[J" );
}

void clear_screen( void ) {
	home();
	clr_to_eos();
}

void enter_alt_buf( void ) {
	to_stdout( "[?1049h" );
}

void exit_alt_buf( void ) {
	to_stdout( "[?1049l" );
}

// Should we use "printf" everywhere?
void move( int x, int y ) {
	printf( "[%d;%dH", y, x );
}
