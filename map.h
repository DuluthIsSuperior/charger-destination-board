#include "character.h"
#include "display.h"
#include <avr/pgmspace.h>

Display display;

// String format: Symbol (first character), number of lines (next 2 digits), width (next digit), starting line data offset (last 4 digits)
const int LENGTH_OF_CHAR_DATA = 8;
const char AA[]  PROGMEM = "A0440000";
const char BB[]  PROGMEM = "B0640016";   // X
const char CC[]  PROGMEM = "C0540040";
const char DD[]  PROGMEM = "D0440060";   // X
const char EE[]  PROGMEM = "E0440076";
const char FF[]  PROGMEM = "F0340092";   // X
const char GG[]  PROGMEM = "G0640104";
const char HH[]  PROGMEM = "H0340128";
const char II[]  PROGMEM = "I0110140";
const char JJ[]  PROGMEM = "J0340144";  // X
const char KK[]  PROGMEM = "K0340156";
const char LL[]  PROGMEM = "L0240168";
const char MM[]  PROGMEM = "M0450176";
const char NN[]  PROGMEM = "N0350192";
const char OO[]  PROGMEM = "O0440204";
const char PP[]  PROGMEM = "P0440220";
const char QQ[]  PROGMEM = "Q0540236";
const char RR[]  PROGMEM = "R0540256";
const char ss[]  PROGMEM = "S0740276";
const char TT[]  PROGMEM = "T0250304";
const char UU[]  PROGMEM = "U0340312";
const char VV[]  PROGMEM = "V0350324";
const char WW[]  PROGMEM = "W0450336";  // X
const char XX[]  PROGMEM = "X0650352";  // X
const char YY[]  PROGMEM = "Y0550376";
const char ZZ[]  PROGMEM = "Z0440396";
const char N00[] PROGMEM = "00440412"; // X
const char N11[] PROGMEM = "10330428"; // X
const char N22[] PROGMEM = "20640440"; // X
const char N33[] PROGMEM = "30740464";
const char N44[] PROGMEM = "40450492"; // X
const char N55[] PROGMEM = "50640508"; // X
const char N66[] PROGMEM = "60640532"; // X
const char N77[] PROGMEM = "70340556"; // X
const char N88[] PROGMEM = "80740568"; // X
const char N99[] PROGMEM = "90540596";
const char SPACE[] PROGMEM = " 0010616";
const char UNKNOWN[] PROGMEM = "\01130620";
const char DOT[] PROGMEM = ".0220664";
const char *const characterData[39] PROGMEM = {AA, BB, CC, DD, EE, FF, GG, HH, II, JJ, KK, LL, MM, NN, OO, PP, QQ, RR, ss, TT, UU, VV, WW, XX, YY, ZZ, N00, N11, N22, N33, N44, N55, N66, N77, N88, N99, SPACE, UNKNOWN, DOT};

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

  char* getCharacterData(char character) {
    char buffer[LENGTH_OF_CHAR_DATA + 1];
    buffer[LENGTH_OF_CHAR_DATA] = 0;
    memset(buffer, 0, sizeof(buffer));  // zeros out the string
    char symbol[2];
    symbol[1] = 0;
    for (int i = 0; i < sizeof(characterData) / sizeof(char*); i++) {
      strncpy_P(symbol, pgm_read_word(&characterData[i]), 1);
      if (symbol[i] == character) {
        strncpy_P(buffer, pgm_read_word(&characterData[i]), 9);
        delete symbol;
        return buffer;
      }
    }
    delete symbol;
    strncpy(buffer, pgm_read_word(&UNKNOWN), 9);
    return buffer;
  }
  
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
