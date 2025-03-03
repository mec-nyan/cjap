#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>


int wait_ms( unsigned ms ) {
	return usleep( ms * 1000 );
}

int _type( const char* str, unsigned ms ) {
	while ( *str ) {
		if ( fputc( *str, stdout ) == EOF ) {
			return EOF;
		}
		fflush( stdout );
		wait_ms( ms );
		++str;
	}
	return 0;
}

int type( const char* str ) {
	return _type( str, 24 );
}

int to_stdout( const char* str ) {
	while ( *str ) {
		if ( fputc( *str, stdout ) == EOF ) {
			return EOF;
		}
		str++;
	}
	return 0;
}

int to_stderr( const char* str ) {
	while ( *str ) {
		if ( fputc( *str, stderr ) == EOF ) {
			return EOF;
		};
		str++;
	}
	return 0;
}

struct termios setup( void ) {
	struct termios saved, cbreaky;
	tcgetattr( STDIN_FILENO, &saved );
	cbreaky          = saved;
	cbreaky.c_lflag &= ~( ECHO | ICANON );
	tcsetattr( STDIN_FILENO, TCSAFLUSH, &cbreaky );
	return saved;
}

int get_term_size( int* lines, int* cols ) {
	struct winsize ws;
	if ( ioctl( STDOUT_FILENO, TIOCGWINSZ, &ws ) != 0 ) {
		return -1;
	}
	*lines = ws.ws_row;
	*cols  = ws.ws_col;
	return 0;
}

void clean( struct termios* saved ) {
	tcsetattr( STDIN_FILENO, TCSAFLUSH, saved );
}
