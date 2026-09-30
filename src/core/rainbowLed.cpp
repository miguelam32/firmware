#include "rainbowLed.h"
#include <Arduino.h>

static Adafruit_NeoPixel rgbLed(1, PIN_RGB_LED, NEO_GRB + NEO_KHZ800);
static uint16_t hue = 0;

static void rainbowTask(void *pv) {
    rgbLed.begin();
    rgbLed.setBrightness(50); // 0-255, baja esto si encandila
    while (true) {
        uint32_t color = rgbLed.gamma32(rgbLed.ColorHSV(hue));
        rgbLed.setPixelColor(0, color);
        rgbLed.show();
        hue += 100;                     // más chico = más lento el cambio de color
        vTaskDelay(pdMS_TO_TICKS(30));   // más grande = más lento el refresco
        if (hue >= 65536) hue = 0;
    }
}

void startRainbowLed() {
    xTaskCreate(rainbowTask, "RainbowLED", 2048, NULL, 1, NULL);
}
