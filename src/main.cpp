#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

#define TFT_SCLK 9
#define TFT_MOSI 10
#define TFT_DC 8
#define TFT_CS 11
#define TFT_RST 18
#define TFT_BLK 16

SPIClass hspi(HSPI);
Adafruit_ST7789 tft = Adafruit_ST7789(&hspi, TFT_CS, TFT_DC, TFT_RST);

void setup()
{
    hspi.begin(TFT_SCLK, -1, TFT_MOSI, TFT_CS);
    hspi.setFrequency(40000000);

    pinMode(TFT_BLK, OUTPUT);
    digitalWrite(TFT_BLK, LOW);

    tft.init(76, 284, SPI_MODE3);
    tft.invertDisplay(false);
    tft.setRotation(3);
    tft.fillScreen(ST77XX_BLACK);

    tft.setSPISpeed(40000000);

    tft.setTextSize(1);
    tft.setTextColor(ST77XX_WHITE);
    tft.setCursor(20, 20);
    tft.println("ESP32S3 - Test TFT");
}

const uint16_t backgroundColors[] = {
    ST77XX_BLUE,
    ST77XX_RED,
    ST77XX_GREEN,
    ST77XX_ORANGE,
    ST77XX_CYAN,
    ST77XX_MAGENTA,
    ST77XX_YELLOW};
const int numColors = sizeof(backgroundColors) / sizeof(backgroundColors[0]);

// фон
void generateRandomBackground()
{
    // Быстрая заливка случайным цветом
    tft.fillScreen(backgroundColors[random(numColors)]);

    // Добавляем быстрые графические элементы для разнообразия
    for (int i = 0; i < 20; i++)
    {
        int x = random(tft.width());
        int y = random(tft.height());
        int size = random(5, 20);
        uint16_t color = backgroundColors[random(numColors)];

        // Рисуем простые фигуры для скорости
        switch (random(3))
        {
        case 0:
            tft.fillRect(x, y, size, size, color);
            break;
        case 1:
            tft.fillCircle(x, y, size / 2, color);
            break;
        case 2:
            tft.drawFastHLine(x, y, size, color);
            break;
        }
    }
}

float spedding = 0.0;

void loop()
{
    generateRandomBackground();
    spedding = spedding + 1;

    if (spedding > 1000.0)
    {
        spedding = 0.0;
    }

    tft.setCursor(20, 50);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(2);
    tft.printf("spedding: %.2f V", spedding);

    delay(10);
}
