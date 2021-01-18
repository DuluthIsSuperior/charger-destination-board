#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>

class Character {
  public:
    char** lines; // using char for 8 bit integer
    int sizeOfLines;
    char symbol;
    Adafruit_SSD1331* display;
    int width;
    draw(int x, int y, int color);
    addNewLine(char startX, char startY, char endX, char endY);
    char linesInserted = 0;
};

Character::draw(int x, int y, int color) {
//  if (linesInserted < sizeOfLines) {
//    display->setCursor(0, 39);
//    display->setTextColor(0xF800);
//    display->setTextSize(1);
//    char buf[30];
//    sprintf(buf, "SYMBOL %c\nWASTED MEMORY", symbol);
//    Serial.println(symbol);
//    Serial.print(linesInserted);
//    Serial.print(" ");
//    Serial.println(sizeOfLines);
//    display->print(buf);
//  }
  for (int i = 0; i < sizeOfLines; i++) {
    char* line = lines[i];
    display->drawLine(line[0] + x, line[1] + y, line[2] + x, line[3] + y, color);
  }
};

Character::addNewLine(char startX, char startY, char endX, char endY)  {
  linesInserted++;
  if (linesInserted > sizeOfLines) {
    display->setCursor(0, 15);
    display->setTextColor(0xF800);
    display->setTextSize(1);
    char buf[30];
    sprintf(buf, "ERROR\nSYMBOL %c\nTOO MANY LINES", symbol);
    display->print(buf);
  } else {
    lines[linesInserted - 1] = new char[4]{startX, startY, endX, endY};
  }
};
