#include "display.h"

class Character {
  public:
//    Character();
    int* linesPROGMEM = NULL; // use to store the beginning pointer to the first point
    int sizeOfLines;
    char symbol;
    Display* display;
    int width;
    draw(int x, int y, int color);
    char linesInserted = 0;
};

Character::draw(int x, int y, int color) {
  int dots = sizeOfLines * 4;
  for (int i = 0; i < dots; i += 4) {
    int* p = linesPROGMEM + i;
    display->drawLine(pgm_read_word(&p[0]) + x, pgm_read_word(&p[1]) + y, pgm_read_word(&p[2]) + x, pgm_read_word(&p[3]) + y, color);
  }
};
