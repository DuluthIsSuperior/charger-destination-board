#include "map.h"

const int TOP_LEFT_CORNER[] = {0, 0};
const int BOTTOM_RIGHT_CORNER[] = {49, 14};

void setup() {
  Serial.begin(9600);
  
  const int AMBER = 0xFFB400;
  const int BLACK = 0x000000;
  
  display.begin();
  display.fillScreen(0x0);
  display.fillRect(TOP_LEFT_CORNER[0], TOP_LEFT_CORNER[1], BOTTOM_RIGHT_CORNER[0], BOTTOM_RIGHT_CORNER[1], AMBER); // start x, start y, end x, end y

  struct Map char_map;
  char str[] = "KYLE DICK";
  int x = 1;
  int y = 3;
  for (int i = 0; i < sizeof(str) / sizeof(char) - 1; i++) {
    struct Character c = char_map.getCharacter(str[i]);
    c.draw(x, y, BLACK);
    x += c.width + 1;
  }
}

bool scrolling = false;

void loop() {
  
}
