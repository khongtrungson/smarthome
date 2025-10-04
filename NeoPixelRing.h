#ifndef NEOPIXEL_RING_H
#define NEOPIXEL_RING_H

#include <Adafruit_NeoPixel.h>

class NeoPixelRing {
private:
    Adafruit_NeoPixel strip;
    bool isActive;
    unsigned long rainbowStartMillis;   // thời điểm bắt đầu
    unsigned long rainbowDuration;      // thời gian chạy rainbow rotate (ms)
    unsigned long prevMillis;
    int effectType;   // 0: none, 1: chase, 2: rainbow tĩnh, 3: rainbow xoay
    int brightness = 50;
    // Chase
    int currentIndex; 
    uint32_t chaseColor;
    int chaseDelay;

    // Rainbow
    long hue;
    int rainbowDelay;

    // ---- Các hàm xử lý hiệu ứng ----
    void updateChase() {
        unsigned long now = millis();
        if (now - prevMillis >= (unsigned long)chaseDelay) {
            prevMillis = now;
            strip.clear();
            strip.setPixelColor(currentIndex, chaseColor);
            strip.show();
            currentIndex = (currentIndex + 1) % strip.numPixels();
        }
    }

    void updateRainbowStatic() { // rainbow tĩnh
        int numLeds = strip.numPixels();
        for (int i = 0; i < numLeds; i++) {
            int pixelHue = (i * 65536L / numLeds);
            strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
        }
        strip.show();
    }

    void updateRainbowRotate() {
    unsigned long now = millis();

    // Kiểm tra hết thời gian
    if (now - rainbowStartMillis >= rainbowDuration) {
        isActive = false;
        fill(255,255,255); // đổi sang trắng khi hết thời gian
        return;
    }

    if (now - prevMillis >= (unsigned long)rainbowDelay) {
        prevMillis = now;
        int numLeds = strip.numPixels();
        for (int i = 0; i < numLeds; i++) {
            int pixelHue = (hue + i * 65536L / numLeds) % 65536;
            strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
        }
        strip.show();
        hue += 256; // tốc độ xoay
        if (hue >= 65536) hue -= 65536;
    }
}

public:
    NeoPixelRing(int pin, int numLeds = 12) 
        : strip(numLeds, pin, NEO_GRB + NEO_KHZ800) {
        isActive = false;
        prevMillis = 0;
        effectType = 0;
        currentIndex = 0;
        hue = 0;
        chaseDelay = 100;
        rainbowDelay = 20;
    }

    void begin() {
        pinMode(strip.getPin() , OUTPUT);
        strip.begin();
        strip.show();  
        strip.setBrightness(brightness); // độ sáng 0-255
    }

    void fill(uint8_t r, uint8_t g, uint8_t b) {
        strip.fill(strip.Color(r, g, b));
        strip.show();
        isActive = true;
        effectType = 0;
    }

    void setPixel(int index, uint8_t r, uint8_t g, uint8_t b) {
        if (index >= 0 && index < strip.numPixels()) {
            strip.setPixelColor(index, strip.Color(r, g, b));
            strip.show();
        }
    }

    void clear() {
        strip.clear();
        strip.show();
        isActive = false;
        effectType = 0;
    }

    void startChase(uint8_t r, uint8_t g, uint8_t b, int d = 100) {
        strip.clear();
        strip.show();
        currentIndex = 0;
        chaseColor = strip.Color(r, g, b);
        chaseDelay = d;
        effectType = 1;
        isActive = true;
    }

    void startRainbow() { // rainbow tĩnh
        effectType = 2;
        isActive = true;
    }

    void startRainbowRotate(int d = 20, unsigned long duration = 10000) { // default 10s
    hue = 0;
    rainbowDelay = d;
    rainbowStartMillis = millis();
    rainbowDuration = duration;
    effectType = 3;
    isActive = true;
}

    void update() {
        if (effectType == 1) updateChase();
        else if (effectType == 2) updateRainbowStatic();
        else if (effectType == 3) updateRainbowRotate();
    }

    bool active() {
        return isActive;
    }

    void setBrightness(int value) {
        // Serial.print("NeoPixel Brightness: "+String(value)+"\n");
        strip.show();
        strip.setBrightness(brightness + value);
        strip.show();
    }
    void turnOff() {
    strip.clear();
    strip.show();
    isActive = false;
    effectType = 0;
    currentIndex = 0;
    hue = 0;
}

void toggle() {
    if (isActive) {
        turnOff();
    } else {
        // Bật lại hiệu ứng cuối cùng
        isActive = true;
        effectType = 0;
    }
}
};

#endif
