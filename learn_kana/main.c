#include "kana.c"
#include "curmanip.c"

int main() {
  /*printf("%s%s%s%s\n", hg_hi, hg_ra, hg_ga, hg_na);*/

  struct termios saved = setup();

  save_pos();

  to_stdout("Welcome!\n\n\tWanna learn some hiragana? ");

  fgetc(stdin);
  restore_pos();
  clr_to_eos();

  to_stdout("Welcome!\n\n\tIt'll be fun! ");

  fgetc(stdin);
  restore_pos();
  clr_to_eos();

  to_stdout("Welcome!\n\n\tAnd then you'll be able to read Manga... ");

  fgetc(stdin);
  restore_pos();
  clr_to_eos();

  to_stdout("Welcome!\n\n\tOk, maybe not. ");

  fgetc(stdin);
  restore_pos();
  clr_to_eos();

  to_stdout("Welcome!\n\n\tMaybe some! ");

  fgetc(stdin);
  restore_pos();
  clr_to_eos();

  enter_alt_buf();
  move(8, 6);
  to_stdout("We've entered another dimension!");

  fgetc(stdin);
  exit_alt_buf();

  to_stdout("Goodbye!\n");


  clean(&saved);
}
