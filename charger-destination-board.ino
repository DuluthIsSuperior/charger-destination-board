#include "map.h"
#include "display.h"
#include <stdarg.h>
#include <math.h>

const char voltage[] PROGMEM = "";
const char chicago[] PROGMEM = "CHICAGO";
const char pere_marquette[] PROGMEM = "PERE MARQUETTE";
const char blue_water[] PROGMEM = "BLUE WATER";

const char *const destinations[] PROGMEM = {voltage, chicago, pere_marquette, blue_water};
const int numberOfMessages = sizeof(destinations) / sizeof(char*);

int x = 2;

bool scrolling = true;
bool messageChanged = true; // initalized to true to let the message initially show up
bool old_A0 = false;
char str[50];
int messageWidth = 0;
int y = 3;
struct Map char_map;
long lastMoved = millis();
int messageId = 0;

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  
  display.begin();
  display.clearDestinationBoard();
}

int charsToIntValue(int argc, ...) {
  va_list argp;
  va_start(argp, argc);
  int multiplier = (int) pow(10, argc - 1); // truncation error
  if (argc == 1) {
    multiplier = 1;
  } else if (multiplier % 10 != 0) {
    multiplier += 10 - multiplier % 10;
  }
  int result = 0;
  for (int i = 0; i < argc; i++) {
    char c = va_arg(argp, int);
    result += (c - 48) * multiplier;
    multiplier /= 10;
  }
  
  return result;
}

void printMessage(bool findWidth) {
  display.clearDestinationBoard();
  int tempX = x;
  if (findWidth) {
    messageWidth = 0;
  }
  
  for (int i = 0; i < sizeof(str) / sizeof(char) - 1; i++) {
    if (str[i] != 0) {
      struct Character c = char_map.getCharacter(str[i]);
      int index = char_map.getCharacterData(str[i]);
      char symbol = (char) pgm_read_word(&characterData[index]);
      int numberOfLines = charsToIntValue(2, pgm_read_word(&characterData[index + 1]), pgm_read_word(&characterData[index + 2]));
      int width = charsToIntValue(1, pgm_read_word(&characterData[index + 3]));
      int offset = charsToIntValue(4, pgm_read_word(&characterData[index + 4]), pgm_read_word(&characterData[index + 5]), pgm_read_word(&characterData[index + 6]), pgm_read_word(&characterData[index + 7]));
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

  scrolling = messageWidth > 47;
}

void loop() {
  if (messageChanged) {
    if (messageId != 0) {
      x = 2;
      memset(str, 0, sizeof(str));  // zeros out the string
      strncpy_P(str, pgm_read_word(&destinations[messageId]), 50);
      printMessage(true);
    }
    messageChanged = false;
    Serial.println(messageId);
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
  if (messageId == 0) {
    int value = analogRead(A1);
    float R1 = 47000.00;
    float R2 = 22000.00;
    float voltage = value * (5.0 / 1024) * ((R1 + R2) / R2);
    memset(str, 0, 8);  // zeros out the string
    char buffer[8];
    sprintf(str, "%s%d.%02dV", (voltage < 10.00 ? "0" : ""), (int) voltage, (int) (voltage * 100.0) % 100);
    x = 2;
    printMessage(true);
  }
  if (digitalRead(A0) == HIGH) {  // if using a button to test this, no code accounts for the button bounce problem
    if (!old_A0) {
      messageId++;
      if (messageId % numberOfMessages == 0) {
        messageId = 0;
      }
      messageChanged = true;
      old_A0 = true;
    }
  } else {
    old_A0 = false;
  }
}
