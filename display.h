#ifndef display_h
#define display_h

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>

#define sclk 13
#define mosi 11
#define cs   4
#define rst  3
#define dc   2

const int TOP_LEFT_CORNER[] = {1, 1};
const int BOTTOM_RIGHT_CORNER[] = {49, 14};
const int boardWidth = BOTTOM_RIGHT_CORNER[0] - TOP_LEFT_CORNER[0] + 1;
const int boardHeight = BOTTOM_RIGHT_CORNER[1] - TOP_LEFT_CORNER[1] + 1;
//int image[boardWidth][boardHeight]; // [x][y] = color
const int BLACK = 0x000000;
const int AMBER = 0xFFB400;

class Display {
  public:
    begin();
    drawLine(int startX, int startY, int endX, int endY, int color);
    setCursor(int x, int y);
    setTextColor(int color);
    setTextSize(int size);
    printText(char* str);
    fillRect(int startX, int startY, int endX, int endY, int color);
    drawRect(int startX, int startY, int endX, int endY, int color);
    fillScreen(int color);
    clearDestinationBoard();
    drawImage();
  private:
    static Adafruit_SSD1331 display;
    static bool running;
};

Adafruit_SSD1331 Display::display = Adafruit_SSD1331(&SPI, cs, dc, rst);
bool Display::running = false;

Display::begin() {
  Serial.println(sizeof(int));;
  if (!running) {
    display.begin();
    fillScreen(0x0);
    drawRect(TOP_LEFT_CORNER[0] - 1, TOP_LEFT_CORNER[1] - 1, BOTTOM_RIGHT_CORNER[0] + 2, BOTTOM_RIGHT_CORNER[1] + 2, AMBER);
    running = true;
  }
};

Display::drawLine(int startX, int startY, int endX, int endY, int color) {
  display.drawLine(startX + TOP_LEFT_CORNER[0], startY + TOP_LEFT_CORNER[1], endX + TOP_LEFT_CORNER[0], endY + TOP_LEFT_CORNER[1], color);
};

Display::setCursor(int x, int y) {
  display.setCursor(x, y);
};

Display::setTextColor(int color) {
  display.setTextColor(color);
};

Display::setTextSize(int size) {
  display.setTextSize(size);
};

Display::printText(char* str) {
  display.print(str);
};

Display::fillRect(int startX, int startY, int endX, int endY, int color) {
  display.fillRect(startX, startY, endX, endY, color);
};

Display::drawRect(int startX, int startY, int endX, int endY, int color) {
  display.drawRect(startX, startY, endX, endY, color);
//  for (int x = startX; x <= endX; x++) {
//    for (int y = startY; y <= endY; y++) {
//      if (image[x][y] != color) {
//        image[x][y] = color;
//        display.drawPixel(1, 1, color);
//      }
//    }
//  }
};

Display::fillScreen(int color) {
  display.fillScreen(color);
  for (int x = 0; x < boardWidth; x++) {
    for (int y = 0; y < boardHeight; y++) {
//      image[x][y] = color;
//      image[x][y][1] = false;
    }
  }
};

Display::clearDestinationBoard() {
  fillRect(TOP_LEFT_CORNER[0], TOP_LEFT_CORNER[1], BOTTOM_RIGHT_CORNER[0], BOTTOM_RIGHT_CORNER[1], BLACK); // start x, start y, end x, end y
};

Display::drawImage() {
  
};

#endif
