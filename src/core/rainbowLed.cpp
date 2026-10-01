#include "rainbowLed.h"
#include <Arduino.h>
#include <FastLED.h>

static CRGB led[1];
static uint8_t hue = 0;

static void rainbowTask(void *pv) {
    FastLED.addLeds<WS2812, PIN_RGB_LED, GRB>(led, 1);
    FastLED.setBrightness(50); // 0-255, baja esto si encandila
    while (true) {
        led[0] = CHSV(hue, 255, 255);
        FastLED.show();
        hue += 1;                       // más chico = más lento el cambio de color
        vTaskDelay(pdMS_TO_TICKS(30));   // más grande = más lento el refresco
    }
}

void startRainbowLed() {
    xTaskCreate(rainbowTask, "RainbowLED", 2048, NULL, 1, NULL);
}
