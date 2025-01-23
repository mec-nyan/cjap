#include "term.c"

void save_pos() {
	to_stdout("7");
}

void restore_pos() {
	to_stdout("8");
}

void home() {
	to_stdout("[H");
}

void clr_to_eol() {
	to_stdout("[K");
}

void clr_to_bol() {
	to_stdout("[1K");
}

void clr_to_eos() {
	to_stdout("[J");
}

void clear_screen() {
	home();
	clr_to_eos();
}

void enter_alt_buf() {
	to_stdout("[?1049h");
}

void exit_alt_buf() {
	to_stdout("[?1049l");
}

// Should we use "printf" everywhere?
void move(int x, int y) {
	printf("[%d;%dH", y, x);
}
