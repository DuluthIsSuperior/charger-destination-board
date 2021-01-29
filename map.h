#include "character.h"
#include "display.h"
#include <avr/pgmspace.h>

const int *const int_table[] PROGMEM = {  // character (number of points + starting offset)
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
  0, 0, 0, 0, 2, 0, 2, 0, 1, 1, 1, 1, 0, 2, 0, 2, 2, 2, 2, 2, 1, 3, 1, 3, 0, 4, 0, 4, 2, 4, 2, 4, 1, 5, 1, 5, 0, 6, 0, 6, 2, 6, 2, 6, // unknown (66 + 616)
};

Character newCharacter(char symbol, int size, int width, int offset) {
  struct Character Char;
  Char.symbol = symbol;
  Char.sizeOfLines = size;
  Char.linesPROGMEM = (int*) int_table + offset;
  Char.display = &display;
  Char.width = width;
  return Char;
}

struct Map {
  // X indicates that I have not seen how this character is rendered on the real deal
  struct Character A = newCharacter('A', 4, 4, 0);
  struct Character B = newCharacter('B', 6, 4, 16);   // X
  struct Character C = newCharacter('C', 5, 4, 40);
  struct Character D = newCharacter('D', 4, 4, 60);   // X
  struct Character E = newCharacter('E', 4, 4, 76);
  struct Character F = newCharacter('F', 3, 4, 92);   // X
  struct Character G = newCharacter('G', 6, 4, 104);
  struct Character H = newCharacter('H', 3, 4, 128);
  struct Character I = newCharacter('I', 1, 1, 140);
  struct Character J = newCharacter('J', 3, 4, 144);  // X
  struct Character K = newCharacter('K', 3, 4, 156);
  struct Character L = newCharacter('L', 2, 4, 168);
  struct Character M = newCharacter('M', 4, 5, 176);
  struct Character N = newCharacter('N', 3, 5, 192);
  struct Character O = newCharacter('O', 4, 4, 204);
  struct Character P = newCharacter('P', 4, 4, 220);
  struct Character Q = newCharacter('Q', 5, 4, 236);
  struct Character R = newCharacter('R', 5, 4, 256);
  struct Character S = newCharacter('S', 7, 4, 276);
  struct Character T = newCharacter('T', 2, 5, 304);
  struct Character U = newCharacter('U', 3, 4, 312);
  struct Character V = newCharacter('V', 3, 5, 324);
  struct Character W = newCharacter('W', 4, 5, 336);  // X
  struct Character X = newCharacter('X', 6, 5, 352);  // X
  struct Character Y = newCharacter('Y', 5, 5, 376);
  struct Character Z = newCharacter('Z', 4, 4, 396);
  struct Character N0 = newCharacter('0', 4, 4, 412); // X
  struct Character N1 = newCharacter('1', 3, 3, 428); // X
  struct Character N2 = newCharacter('2', 6, 4, 440); // X
  struct Character N3 = newCharacter('3', 7, 4, 464);
  struct Character N4 = newCharacter('4', 4, 5, 492); // X
  struct Character N5 = newCharacter('5', 6, 4, 508); // X
  struct Character N6 = newCharacter('6', 6, 4, 532); // X
  struct Character N7 = newCharacter('7', 3, 4, 556); // X
  struct Character N8 = newCharacter('8', 7, 4, 568); // X
  struct Character N9 = newCharacter('9', 5, 4, 596);
  struct Character space = newCharacter(' ', 0, 1, 616);
  struct Character unknown = newCharacter('\0', 11, 3, 620);
  Character symbols[38] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, N0, N1, N2, N3, N4, N5, N6, N7, N8, N9, space, unknown};
  
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
    sprintf(buf, "ERROR\nCHAR '%c'\nNOT RENDERED", character);
    display.print(buf);
    return unknown;
  }
};
