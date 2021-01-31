#include "character.h"
#include "display.h"
#include <avr/pgmspace.h>

Display display;

// String format: Symbol (first character), number of lines (next 2 digits), width (next digit), starting line data offset (last 4 digits)
const int LENGTH_OF_CHAR_DATA = 8;
const char *const characterData[320] PROGMEM = {
'A','0','4','4','0','0','0','0',
'B','0','6','4','0','0','1','6',   // X
'C','0','5','4','0','0','4','0',
'D','0','4','4','0','0','6','0',   // X
'E','0','4','4','0','0','7','6',
'F','0','3','4','0','0','9','2',   // X
'G','0','6','4','0','1','0','4',
'H','0','3','4','0','1','2','8',
'I','0','1','1','0','1','4','0',
'J','0','3','4','0','1','4','4',  // X
'K','0','3','4','0','1','5','6',
'L','0','2','4','0','1','6','8',
'M','0','4','5','0','1','7','6',
'N','0','3','5','0','1','9','2',
'O','0','4','4','0','2','0','4',
'P','0','4','4','0','2','2','0',
'Q','0','5','4','0','2','3','6',
'R','0','5','4','0','2','5','6',
'S','0','7','4','0','2','7','6',
'T','0','2','5','0','3','0','4',
'U','0','3','4','0','3','1','2',
'V','0','3','5','0','3','2','4',
'W','0','4','5','0','3','3','6',  // X
'X','0','6','5','0','3','5','2',  // X
'Y','0','5','5','0','3','7','6',
'Z','0','4','4','0','3','9','6',
'0','0','4','4','0','4','1','2', // X
'1','0','3','3','0','4','2','8', // X
'2','0','6','4','0','4','4','0', // X
'3','0','7','4','0','4','6','4',
'4','0','4','5','0','4','9','2', // X
'5','0','6','4','0','5','0','8', // X
'6','0','6','4','0','5','3','2', // X
'7','0','3','4','0','5','5','6', // X
'8','0','7','4','0','5','6','8', // X
'9','0','5','4','0','5','9','6',
' ','0','0','1','0','6','1','6',
'\0','1','1','3','0','6','2','0',
'.','0','2','2','0','6','6','4'
};

struct Map {
  // X indicates that I have not seen how this character is rendered on the real unit
  const Character A {'A', 4, 4, 0};
  const Character B {'B', 6, 4, 16};   // X
  const Character C {'C', 5, 4, 40};
  const Character D {'D', 4, 4, 60};   // X
  const Character E {'E', 4, 4, 76};
  const Character F {'F', 3, 4, 92};   // X
  const Character G {'G', 6, 4, 104};
  const Character H {'H', 3, 4, 128};
  const Character I {'I', 1, 1, 140};
  const Character J {'J', 3, 4, 144};  // X
  const Character K {'K', 3, 4, 156};
  const Character L {'L', 2, 4, 168};
  const Character M {'M', 4, 5, 176};
  const Character N {'N', 3, 5, 192};
  const Character O {'O', 4, 4, 204};
  const Character P {'P', 4, 4, 220};
  const Character Q {'Q', 5, 4, 236};
  const Character R {'R', 5, 4, 256};
  const Character S {'S', 7, 4, 276};
  const Character T {'T', 2, 5, 304};
  const Character U {'U', 3, 4, 312};
  const Character V {'V', 3, 5, 324};
  const Character W {'W', 4, 5, 336};  // X
  const Character X {'X', 6, 5, 352};  // X
  const Character Y {'Y', 5, 5, 376};
  const Character Z {'Z', 4, 4, 396};
  const Character N0 {'0', 4, 4, 412}; // X
  const Character N1 {'1', 3, 3, 428}; // X
  const Character N2 {'2', 6, 4, 440}; // X
  const Character N3 {'3', 7, 4, 464};
  const Character N4 {'4', 4, 5, 492}; // X
  const Character N5 {'5', 6, 4, 508}; // X
  const Character N6 {'6', 6, 4, 532}; // X
  const Character N7 {'7', 3, 4, 556}; // X
  const Character N8 {'8', 7, 4, 568}; // X
  const Character N9 {'9', 5, 4, 596};
  const Character space {' ', 0, 1, 616};
  const Character unknown {'\0', 11, 3, 620};
  const Character dot {'.', 2, 2, 664};
  const Character symbols[39] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, N0, N1, N2, N3, N4, N5, N6, N7, N8, N9, space, unknown, dot};

  Map() {
    A.setDisplay(&display);
  }

  int getCharacterData(char character) {
    //sizeof(characterData) / sizeof(char*) / 8
    for (int i = 0; i < sizeof(characterData) / sizeof(char*); i += 8) {
      if ((char) pgm_read_word(&characterData[i]) == character) {
        return i;
      }
    }
    return 304;
  }

//  char* getCharacterData(char character) {
//    char buffer[LENGTH_OF_CHAR_DATA + 1];
//    buffer[LENGTH_OF_CHAR_DATA] = 0;
//    memset(buffer, 0, sizeof(buffer));  // zeros out the string
//    char symbol[2];
//    symbol[1] = 0;
//    for (int i = 0; i < sizeof(characterData) / sizeof(char*); i++) {
//      strncpy_P(symbol, pgm_read_word(&characterData[i]), 1);
//      if (symbol[i] == character) {
//        strncpy_P(buffer, pgm_read_word(&characterData[i]), 9);
//        return buffer;
//      }
//    }
//    strncpy(buffer, pgm_read_word(&UNKNOWN), 9);
//    return buffer;
//  }
  
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
