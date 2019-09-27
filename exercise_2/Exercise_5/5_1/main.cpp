#include "part1.h"
#include "part2.h"
#include <ncurses.h>

int main()
{
  part1();
  part2();

  initscr();
  printw("Hello world!");
  refresh();
  getch();
  endwin();

  return 0;
}
