#include "character.h"
#include "display.h"
#include <avr/pgmspace.h>

Display display;

Character newCharacter(char symbol, int size, int width, int charBeginningOffset) {
  Character Char {symbol, size, width, (int*) int_table + charBeginningOffset, &display};
  return Char;
}

struct Map {
  // X indicates that I have not seen how this character is rendered on the real unit
  const Character A = newCharacter('A', 4, 4, 0);
  const Character B = newCharacter('B', 6, 4, 16);   // X
  const Character C = newCharacter('C', 5, 4, 40);
  const Character D = newCharacter('D', 4, 4, 60);   // X
  const Character E = newCharacter('E', 4, 4, 76);
  const Character F = newCharacter('F', 3, 4, 92);   // X
  const Character G = newCharacter('G', 6, 4, 104);
  const Character H = newCharacter('H', 3, 4, 128);
  const Character I = newCharacter('I', 1, 1, 140);
  const Character J = newCharacter('J', 3, 4, 144);  // X
  const Character K = newCharacter('K', 3, 4, 156);
  const Character L = newCharacter('L', 2, 4, 168);
  const Character M = newCharacter('M', 4, 5, 176);
  const Character N = newCharacter('N', 3, 5, 192);
  const Character O = newCharacter('O', 4, 4, 204);
  const Character P = newCharacter('P', 4, 4, 220);
  const Character Q = newCharacter('Q', 5, 4, 236);
  const Character R = newCharacter('R', 5, 4, 256);
  const Character S = newCharacter('S', 7, 4, 276);
  const Character T = newCharacter('T', 2, 5, 304);
  const Character U = newCharacter('U', 3, 4, 312);
  const Character V = newCharacter('V', 3, 5, 324);
  const Character W = newCharacter('W', 4, 5, 336);  // X
  const Character X = newCharacter('X', 6, 5, 352);  // X
  const Character Y = newCharacter('Y', 5, 5, 376);
  const Character Z = newCharacter('Z', 4, 4, 396);
  const Character N0 = newCharacter('0', 4, 4, 412); // X
  const Character N1 = newCharacter('1', 3, 3, 428); // X
  const Character N2 = newCharacter('2', 6, 4, 440); // X
  const Character N3 = newCharacter('3', 7, 4, 464);
  const Character N4 = newCharacter('4', 4, 5, 492); // X
  const Character N5 = newCharacter('5', 6, 4, 508); // X
  const Character N6 = newCharacter('6', 6, 4, 532); // X
  const Character N7 = newCharacter('7', 3, 4, 556); // X
  const Character N8 = newCharacter('8', 7, 4, 568); // X
  const Character N9 = newCharacter('9', 5, 4, 596);
  const Character space = newCharacter(' ', 0, 1, 616);
  const Character unknown = newCharacter('\0', 11, 3, 620);
  const Character dot = newCharacter('.', 2, 2, 664);
  const Character symbols[39] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, N0, N1, N2, N3, N4, N5, N6, N7, N8, N9, space, unknown, dot};
  
  Character getCharacter(char character) {
    for (int i = 0; i < sizeof(symbols) / sizeof(Character); i++) {
      struct Character symbol = symbols[i];
      if (symbol.symbol == character) {
        return symbol;
      }
    }
    display.setCursor(0, 16);
    display.setTextColor(0xF800);
    display.setTextSize(1);
    char buf[26];
    sprintf(buf, "ERROR\nCHAR '%c'\nNOT RENDERED", character);
    display.printText(buf);
    return unknown;
  }
};
