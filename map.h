#include "character.h"
#include "display.h"
#include <avr/pgmspace.h>

Display display;

struct Map {
  // X indicates that I have not seen how this character is rendered on the real unit
  const Character A {'A', 4, 4, 0, &display};
  const Character B {'B', 6, 4, 16, &display};   // X
  const Character C {'C', 5, 4, 40, &display};
  const Character D {'D', 4, 4, 60, &display};   // X
  const Character E {'E', 4, 4, 76, &display};
  const Character F {'F', 3, 4, 92, &display};   // X
  const Character G {'G', 6, 4, 104, &display};
  const Character H {'H', 3, 4, 128, &display};
  const Character I {'I', 1, 1, 140, &display};
  const Character J {'J', 3, 4, 144, &display};  // X
  const Character K {'K', 3, 4, 156, &display};
  const Character L {'L', 2, 4, 168, &display};
  const Character M {'M', 4, 5, 176, &display};
  const Character N {'N', 3, 5, 192, &display};
  const Character O {'O', 4, 4, 204, &display};
  const Character P {'P', 4, 4, 220, &display};
  const Character Q {'Q', 5, 4, 236, &display};
  const Character R {'R', 5, 4, 256, &display};
  const Character S {'S', 7, 4, 276, &display};
  const Character T {'T', 2, 5, 304, &display};
  const Character U {'U', 3, 4, 312, &display};
  const Character V {'V', 3, 5, 324, &display};
  const Character W {'W', 4, 5, 336, &display};  // X
  const Character X {'X', 6, 5, 352, &display};  // X
  const Character Y {'Y', 5, 5, 376, &display};
  const Character Z {'Z', 4, 4, 396, &display};
  const Character N0 {'0', 4, 4, 412, &display}; // X
  const Character N1 {'1', 3, 3, 428, &display}; // X
  const Character N2 {'2', 6, 4, 440, &display}; // X
  const Character N3 {'3', 7, 4, 464, &display};
  const Character N4 {'4', 4, 5, 492, &display}; // X
  const Character N5 {'5', 6, 4, 508, &display}; // X
  const Character N6 {'6', 6, 4, 532, &display}; // X
  const Character N7 {'7', 3, 4, 556, &display}; // X
  const Character N8 {'8', 7, 4, 568, &display}; // X
  const Character N9 {'9', 5, 4, 596, &display};
  const Character space {' ', 0, 1, 616, &display};
  const Character unknown {'\0', 11, 3, 620, &display};
  const Character dot {'.', 2, 2, 664, &display};
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
