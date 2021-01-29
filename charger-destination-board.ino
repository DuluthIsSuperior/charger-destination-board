#include "map.h"

const int TOP_LEFT_CORNER[] = {0, 0};
const int BOTTOM_RIGHT_CORNER[] = {49, 14};
  
const int AMBER = 0xFFB400;
const int BLACK = 0x000000;

const char chicago[] PROGMEM = "CHICAGO";
const char pere_marquette[] PROGMEM = "PERE MARQUETTE";
const char blue_water[] PROGMEM = "BLUE WATER";

const char *const destinations[] PROGMEM = {chicago, pere_marquette, blue_water};
const int numberOfMessages = sizeof(destinations) / sizeof(char*);

void clearBoard() {
  display.fillRect(TOP_LEFT_CORNER[0], TOP_LEFT_CORNER[1], BOTTOM_RIGHT_CORNER[0], BOTTOM_RIGHT_CORNER[1], BLACK); // start x, start y, end x, end y  
}

int x = 1;
void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  
  display.begin();
  display.fillScreen(0x0);
  display.drawRect(TOP_LEFT_CORNER[0], TOP_LEFT_CORNER[1], BOTTOM_RIGHT_CORNER[0] + 1, BOTTOM_RIGHT_CORNER[1] + 1, AMBER);
  clearBoard();

  Serial.println(sizeof(destinations) / sizeof(char*));
}

bool scrolling = true;
bool messageChanged = true; // initalized to true to let the message initially show up
bool old_A0 = false;
char str[50];
int messageWidth = 0;
int y = 3;
struct Map char_map;
long lastMoved = millis();
int messageId = 0;

void printMessage(bool findWidth) {
  clearBoard();
  int tempX = x;
  if (findWidth) {
    messageWidth = 0;
  }
  
  for (int i = 0; i < sizeof(str) / sizeof(char) - 1; i++) {
    if (str[i] != 0) {
      struct Character c = char_map.getCharacter(str[i]);
      c.draw(tempX, y, AMBER);
      int add = c.width + 1;
      tempX += add;
      if (findWidth) {
        messageWidth += add;
      }
    } else {
      break;
    }
  }
}

void loop() {
  if (messageChanged) {
    x = scrolling ? BOTTOM_RIGHT_CORNER[0] + 3 : 1;
    memset(str, 0, sizeof(str));  // zeros out the string
    strncpy_P(str, pgm_read_word(&destinations[messageId]), 50);
    printMessage(true);
    messageChanged = false;
  }
  if (scrolling && millis() - lastMoved >= 50) {
    if (x < -messageWidth) {
      x = BOTTOM_RIGHT_CORNER[0] + 3;
    } else {
      x--;
    }
    printMessage(false);
    lastMoved = millis();
  }
  if (digitalRead(A0) == HIGH) {
    if (!old_A0) {
      messageId++;
      if (messageId % numberOfMessages == 0) {  // loops list back to the beginning if the last message is reached
        messageId = 0;
      }
      messageChanged = true;
      old_A0 = true;
    }
  } else {
    old_A0 = false;
  }
}
