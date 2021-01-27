#include "character.h"
#include <avr/pgmspace.h>

#define sclk 13
#define mosi 11
#define cs   10
#define rst  9
#define dc   8

Adafruit_SSD1331 display = Adafruit_SSD1331(&SPI, cs, dc, rst);

const int *const int_table[] PROGMEM = {
  0, 0, 0, 6, 1, 0, 3, 0, 1, 3, 2, 3, 1, 6, 3, 6  // E
};
int* ad = (int*) int_table;

Character newCharacter(char symbol, int size, int width, int offset) {
  struct Character Char;
  Char.symbol = symbol;
  Char.sizeOfLines = size;
  Char.lines = (char**) malloc(sizeof(char*) * Char.sizeOfLines);
  if (offset != -1) {
    Char.linesPROGMEM = (int*) int_table + offset;
  }
  Char.display = &display;
  Char.width = width;
  return Char;
}

//const int EL[16] PROGMEM = {0, 0, 0, 6, 1, 0, 3, 0, 1, 3, 2, 3, 1, 6, 3, 6};

struct Map {
//  struct Character A = newCharacter('A', 4, 4);
//  struct Character C = newCharacter('C', 5, 4);
  struct Character E = newCharacter('E', 4, 4, 0);
//  struct Character G = newCharacter('G', 6, 4);
//  struct Character H = newCharacter('H', 3, 4);
  struct Character I = newCharacter('I', 1, 1, -1);
  struct Character L = newCharacter('L', 2, 4, -1);
//  struct Character K = newCharacter('K', 3, 4);
//  struct Character M = newCharacter('M', 4, 5);
//  struct Character N = newCharacter('N', 3, 5);
  struct Character O = newCharacter('O', 4, 4, -1);
//  struct Character P = newCharacter('P', 4, 4);
//  struct Character Q = newCharacter('Q', 5, 4);
//  struct Character R = newCharacter('R', 5, 4);
//  struct Character S = newCharacter('S', 7, 4);
  struct Character T = newCharacter('T', 2, 5, -1);
//  struct Character U = newCharacter('U', 3, 4);
  struct Character V = newCharacter('V', 3, 5, -1);
//  struct Character Y = newCharacter('Y', 5, 5);
//  struct Character Z = newCharacter('Z', 4, 4);
//  struct Character N3 = newCharacter('3', 7, 4);
//  struct Character N9 = newCharacter('9', 5, 4);
//  struct Character space = newCharacter(' ', 0, 1);
  struct Character unknown = newCharacter('\0', 11, 3, -1);
//  Character symbols[22] = {A, C, E, G, H, I, K, L, M, N, O, P, Q, R, S, T, V, Y, Z, N3, N9, space};
  Character symbols[6] = {E, I, L, O, T, V};

  Map() {
    int intBuf = pgm_read_word(&int_table[0]);
    Serial.println(intBuf);

    intBuf = pgm_read_word(&ad[1]);
    Serial.println(intBuf);
//    A.addNewLine(1, 0, 2, 0);)
//    A.addNewLine(0, 1, 0, 6);
//    A.addNewLine(3, 1, 3, 6);
//    A.addNewLine(1, 4, 2, 4);
//
//    C.addNewLine(0, 1, 0, 5);
//    C.addNewLine(1, 0, 2, 0);
//    C.addNewLine(3, 1, 3, 1);
//    C.addNewLine(1, 6, 2, 6);
//    C.addNewLine(3, 5, 3, 5);

    E.addNewLine(0, 0, 0, 6);
    E.addNewLine(1, 0, 3, 0);
    E.addNewLine(1, 3, 2, 3);
    E.addNewLine(1, 6, 3, 6);
    Serial.println(pgm_read_word(&E.linesPROGMEM[1]));
    
//    G.addNewLine(0, 1, 0, 5);
//    G.addNewLine(1, 0, 2, 0);
//    G.addNewLine(3, 1, 3, 1);
//    G.addNewLine(1, 6, 2, 6);
//    G.addNewLine(3, 3, 3, 5);
//    G.addNewLine(2, 3, 2, 3);
//
//    H.addNewLine(0, 0, 0, 6);
//    H.addNewLine(1, 3, 2, 3);
//    H.addNewLine(3, 0, 3, 6);

    I.addNewLine(0, 0, 0, 6);
//
//    K.addNewLine(0, 0, 0, 6);
//    K.addNewLine(1, 2, 3, 0);
//    K.addNewLine(1, 4, 3, 6);

    L.addNewLine(0, 0, 0, 6);
    L.addNewLine(1, 6, 3, 6);

//    M.addNewLine(0, 0, 0, 6);
//    M.addNewLine(1, 1, 2, 2);
//    M.addNewLine(3, 1, 3, 1);
//    M.addNewLine(4, 0, 4, 6);
//
//    N.addNewLine(0, 0, 0, 6);
//    N.addNewLine(0, 0, 4, 6);
//    N.addNewLine(4, 0, 4, 6);

    O.addNewLine(0, 1, 0, 5);
    O.addNewLine(1, 0, 2, 0);
    O.addNewLine(3, 1, 3, 5);
    O.addNewLine(1, 6, 2, 6);

//    P.addNewLine(0, 0, 0, 6);
//    P.addNewLine(1, 0, 2, 0);
//    P.addNewLine(1, 3, 2, 3);
//    P.addNewLine(3, 1, 3, 2);
//
//    Q.addNewLine(0, 1, 0, 5);
//    Q.addNewLine(1, 0, 2, 0);
//    Q.addNewLine(3, 1, 3, 4);
//    Q.addNewLine(1, 6, 1, 6);
//    Q.addNewLine(2, 5, 3, 6);
//
//    R.addNewLine(0, 0, 0, 6);
//    R.addNewLine(1, 0, 2, 0);
//    R.addNewLine(1, 3, 2, 3);
//    R.addNewLine(3, 1, 3, 2);
//    R.addNewLine(1, 4, 3, 6);
//
//    S.addNewLine(3, 1, 3, 1);
//    S.addNewLine(2, 0, 1, 0);
//    S.addNewLine(0, 1, 0, 2);
//    S.addNewLine(1, 3, 2, 3);
//    S.addNewLine(3, 4, 3, 5);
//    S.addNewLine(2, 6, 1, 6);
//    S.addNewLine(0, 5, 0, 5);

    T.addNewLine(0, 0, 4, 0);
    T.addNewLine(2, 1, 2, 6);

//    U.addNewLine(0, 0, 0, 5);
//    U.addNewLine(1, 6, 2, 6);
//    U.addNewLine(3, 0, 3, 5);

    V.addNewLine(2, 6, 2, 4);
    V.addNewLine(2, 4, 0, 0);
    V.addNewLine(2, 4, 4, 0);

//    Y.addNewLine(2, 6, 2, 3);
//    Y.addNewLine(2, 4, 0, 0);
//    Y.addNewLine(2, 4, 4, 0);
//    Y.addNewLine(1, 1, 1, 1);
//    Y.addNewLine(1, 1, 3, 1);
//
//    Z.addNewLine(0, 0, 3, 0);
//    Z.addNewLine(3, 1, 0, 4);
//    Z.addNewLine(0, 5, 0, 5);
//    Z.addNewLine(0, 6, 3, 6);
//
//    N3.addNewLine(0, 1, 0, 1);
//    N3.addNewLine(1, 0, 2, 0);
//    N3.addNewLine(3, 1, 3, 2);
//    N3.addNewLine(1, 3, 2, 3);
//    N3.addNewLine(3, 4, 3, 5);
//    N3.addNewLine(1, 6, 2, 6);
//    N3.addNewLine(0, 5, 0, 5);

//    N9.addNewLine(0, 1, 0, 2);
//    N9.addNewLine(1, 0, 2, 0);
//    N9.addNewLine(3, 1, 3, 5);
//    N9.addNewLine(1, 3, 2, 3);
//    N9.addNewLine(1, 6, 2, 6);

    unknown.addNewLine(0, 0, 0, 0);
    unknown.addNewLine(2, 0, 2, 0);
    unknown.addNewLine(1, 1, 1, 1);
    unknown.addNewLine(0, 2, 0, 2);
    unknown.addNewLine(2, 2, 2, 2);
    unknown.addNewLine(1, 3, 1, 3);
    unknown.addNewLine(0, 4, 0, 4);
    unknown.addNewLine(2, 4, 2, 4);
    unknown.addNewLine(1, 5, 1, 5);
    unknown.addNewLine(0, 6, 0, 6);
    unknown.addNewLine(2, 6, 2, 6);
  }
  Character getCharacter(char character) {
    for (int i = 0; i < sizeof(symbols) / sizeof(Character); i++) {
      struct Character symbol = symbols[i];
      if (symbol.symbol == character) {
        return symbol;
      }
    }
    display.setCursor(0, 15);
    display.setTextColor(0xF800);
    display.setTextSize(1);
    char buf[26];
    sprintf(buf, "ERROR\nCHAR %c\nNOT RENDERED", character);
    display.print(buf);
    return unknown;
  }
};
