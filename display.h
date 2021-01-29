#define sclk 13
#define mosi 11
#define cs   4
#define rst  3
#define dc   2

Adafruit_SSD1331 display = Adafruit_SSD1331(&SPI, cs, dc, rst);
