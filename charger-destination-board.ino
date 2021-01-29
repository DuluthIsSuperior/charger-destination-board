#include "map.h"

const int TOP_LEFT_CORNER[] = {0, 0};
const int BOTTOM_RIGHT_CORNER[] = {49, 14};
  
const int AMBER = 0xFFB400;
const int BLACK = 0x000000;

void clearBoard() {
  display.fillRect(TOP_LEFT_CORNER[0], TOP_LEFT_CORNER[1], BOTTOM_RIGHT_CORNER[0], BOTTOM_RIGHT_CORNER[1], BLACK); // start x, start y, end x, end y  
}

int x = 1;
void setup() {
  Serial.begin(9600);
  
  display.begin();
  display.fillScreen(0x0);
  display.drawRect(TOP_LEFT_CORNER[0], TOP_LEFT_CORNER[1], BOTTOM_RIGHT_CORNER[0] + 1, BOTTOM_RIGHT_CORNER[1] + 1, AMBER);
  clearBoard();
}

bool scrolling = true;
bool messageChanged = true; // initalized to true to let the message initially show up
char str[50] = "PERE MARQUETTE";
int messageWidth = 0;
int y = 3;
struct Map char_map;
long lastMoved = millis();

void loop() {
  if (messageChanged) {
    clearBoard();
    x = scrolling ? BOTTOM_RIGHT_CORNER[0] + 3 : 1;
    int tempX = x;
    messageWidth = 0;
    for (int i = 0; i < sizeof(str) / sizeof(char) - 1; i++) {
      if (str[i] != 0) {
        struct Character c = char_map.getCharacter(str[i]);
        c.draw(tempX, y, AMBER);
        int add = c.width + 1;
        messageWidth += add;
        tempX += add;
      } else {
        break;
      }
    }
    messageChanged = false;
  }
  if (scrolling && millis() - lastMoved >= 50) {
    clearBoard();
    if (x < -messageWidth) {
      x = BOTTOM_RIGHT_CORNER[0] + 3;
    } else {
      x--;
    }
    int tempX = x;
    for (int i = 0; i < sizeof(str) / sizeof(char) - 1; i++) {
      if (str[i] != 0) {
        struct Character c = char_map.getCharacter(str[i]);
        c.draw(tempX, y, AMBER);
        tempX += c.width + 1;
      } else {
        break;
      }
    }
    lastMoved = millis();
  }
}
