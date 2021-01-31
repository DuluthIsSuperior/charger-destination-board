#include "display.h"

const int *const lineData[] PROGMEM = {  // character (number of points + starting offset)
  1, 0, 2, 0, 0, 1, 0, 6, 3, 1, 3, 6, 1, 4, 2, 4, // A (16 + 0)
  0, 0, 0, 6, 1, 0, 2, 0, 1, 3, 2, 3, 1, 6, 2, 6, 3, 1, 3, 2, 3, 4, 3, 5, // B (24 + 16)
  0, 1, 0, 5, 1, 0, 2, 0, 3, 1, 3, 1, 1, 6, 2, 6, 3, 5, 3, 5, // C (20 + 40)
  0, 0, 0, 6, 1, 0, 2, 0, 1, 6, 2, 6, 3, 1, 3, 5, // D (16 + 60)
  0, 0, 0, 6, 1, 0, 3, 0, 1, 3, 2, 3, 1, 6, 3, 6,  // E (16 + 76)
  0, 0, 0, 6, 1, 0, 3, 0, 1, 3, 2, 3,  // F (12 + 92)
  0, 1, 0, 5, 1, 0, 2, 0, 3, 1, 3, 1, 1, 6, 2, 6, 3, 3, 3, 5, 2, 3, 2, 3, // G (24 + 104)
  0, 0, 0, 6, 1, 3, 2, 3, 3, 0, 3, 6,  // H (12 + 128)
  0, 0, 0, 6, // I (4 + 140)
  3, 0, 3, 5, 2, 6, 1, 6, 0, 5, 0, 5,  // J (12 + 144)
  0, 0, 0, 6, 1, 2, 3, 0, 1, 4, 3, 6,  // K (12 + 156)
  0, 0, 0, 6, 1, 6, 3, 6, // L (8 + 168)
  0, 0, 0, 6, 1, 1, 2, 2, 3, 1, 3, 1, 4, 0, 4, 6, // M (16 + 176)
  0, 0, 0, 6, 0, 0, 4, 6, 4, 0, 4, 6, // N (12 + 192)
  0, 1, 0, 5, 1, 0, 2, 0, 3, 1, 3, 5, 1, 6, 2, 6, // O (16 + 204)
  0, 0, 0, 6, 1, 0, 2, 0, 1, 3, 2, 3, 3, 1, 3, 2, // P (16 + 220)
  0, 1, 0, 5, 1, 0, 2, 0, 3, 1, 3, 4, 1, 6, 1, 6, 2, 5, 3, 6, // Q (20 + 236)
  0, 0, 0, 6, 1, 0, 2, 0, 1, 3, 2, 3, 3, 1, 3, 2, 1, 4, 3, 6, // R (20 + 256)
  3, 1, 3, 1, 2, 0, 1, 0, 0, 1, 0, 2, 1, 3, 2, 3, 3, 4, 3, 5, 2, 6, 1, 6, 0, 5, 0, 5, // S (28 + 276)
  0, 0, 4, 0, 2, 1, 2, 6, // T (8 + 304)
  0, 0, 0, 5, 1, 6, 2, 6, 3, 0, 3, 5, // U (12 + 312)
  2, 6, 2, 4, 2, 4, 0, 0, 2, 4, 4, 0, // V (12 + 324)
  0, 0, 0, 6, 1, 5, 2, 4, 3, 5, 4, 6, 4, 5, 4, 0, // W (16 + 336)
  1, 2, 3, 4, 1, 4, 4, 1, 0, 0, 0, 1, 4, 0, 4, 1, 0, 5, 0, 6, 4, 5, 4, 6,  // X (24 + 352)
  2, 6, 2, 3, 1, 3, 1, 2, 0, 1, 0, 0, 3, 3, 3, 2, 4, 1, 4, 0, // Y (20 + 376)
  0, 0, 3, 0, 3, 1, 0, 4, 0, 5, 0, 5, 0, 6, 3, 6, // Z (16 + 396)
  0, 1, 0, 5, 1, 0, 2, 0, 3, 1, 3, 5, 1, 6, 2, 6, // 0 (16 + 412)
  0, 1, 0, 1, 1, 0, 1, 5, 0, 6, 2, 6, // 1 (12 + 428)
  0, 1, 0, 1, 1, 0, 2, 0, 3, 1, 3, 2, 2, 3, 0, 5, 0, 6, 0, 6, 1, 6, 3, 6, // 2 (24 + 440)
  0, 1, 0, 1, 1, 0, 2, 0, 3, 1, 3, 2, 1, 3, 2, 3, 3, 4, 3, 5, 1, 6, 2, 6, 0, 5, 0, 5, // 3 (28 + 464)
  4, 4, 4, 4, 3, 6, 3, 0, 2, 4, 0, 4, 0, 3, 3, 0, // 4 (16 + 492)
  3, 0, 0, 0, 0, 1, 0, 2, 1, 2, 2, 2, 3, 3, 3, 5, 2, 6, 1, 6, 0, 5, 0, 5, // 5 (24 + 508)
  3, 1, 3, 1, 2, 0, 1, 0, 0, 1, 0, 5, 1, 6, 2, 6, 3, 5, 3, 4, 2, 3, 1, 3, // 6 (24 + 532)
  0, 0, 3, 0, 3, 1, 1, 6, 0, 0, 0, 0, // 7 (12 + 556)
  1, 0, 2, 0, 0, 1, 0, 2, 3, 1, 3, 2, 1, 3, 2, 3, 0, 4, 0, 5, 3, 4, 3, 5, 1, 6, 2, 6, // 8 (28 + 568)
  0, 1, 0, 2, 1, 0, 2, 0, 3, 1, 3, 5, 1, 3, 2, 3, 1, 6, 2, 6, // 9 (20 + 596)
  0, 0, 0, 0, // space (4 + 616)
  0, 0, 0, 0, 2, 0, 2, 0, 1, 1, 1, 1, 0, 2, 0, 2, 2, 2, 2, 2, 1, 3, 1, 3, 0, 4, 0, 4, 2, 4, 2, 4, 1, 5, 1, 5, 0, 6, 0, 6, 2, 6, 2, 6, // unknown (44 + 620)
  0, 5, 0, 6, 1, 5, 1, 6,  // . (8 + 664)
};

class Character {
  public:
    Character(char s, int si, int w, int charBeginningOffset);
    int* linesPROGMEM = NULL; // use to store the beginning pointer to the first point
    int sizeOfLines;
    char symbol;
    int width;
    draw(int x, int y, int color);
    char linesInserted = 0;
    static Display* display;
    setDisplay(Display* d);
};

Display* Character::display = NULL;

Character::Character(char s, int si, int w, int charBeginningOffset) {
  symbol = s;
  sizeOfLines = si;
  linesPROGMEM = (int*) lineData + charBeginningOffset;
  width = w;
}

Character::setDisplay(Display* d) {
  if (display == NULL) {
    display = d;
  }
}

Character::draw(int x, int y, int color) {
  int dots = sizeOfLines * 4;
  for (int i = 0; i < dots; i += 4) {
    int* p = linesPROGMEM + i;
    display->drawLine(pgm_read_word(&p[0]) + x, pgm_read_word(&p[1]) + y, pgm_read_word(&p[2]) + x, pgm_read_word(&p[3]) + y, color);
  }
};
