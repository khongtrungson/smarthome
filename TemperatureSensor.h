#ifndef NTC_H
#define NTC_H

#include <Arduino.h>
#include <math.h>
#include "LCDDisplay.h"

// ====== HẰNG SỐ CỐ ĐỊNH CHO CẢ DỰ ÁN ======
constexpr float R_FIXED = 20000.0;     // Điện trở cố định (Ohm)
constexpr float B_CONST = 3950.0;      // Hằng số B của NTC
constexpr float R0 = 20000.0;          // Điện trở tại T0 (Ohm)
constexpr float T0 = 298.15;           // Nhiệt độ chuẩn (K) = 25°C
constexpr float VCC = 5.0;             // Điện áp nguồn (V)
constexpr float ALPHA = 0.2;           // Hệ số lọc mượt
constexpr unsigned long READ_INTERVAL = 10000; // Chu kỳ đọc (ms)

class TemperatureSensor {
private:
  uint8_t pin;
  float filteredTemp;
  bool initialized;
  unsigned long lastReadTime;
  LCDDisplay* _lcd;

public:
  TemperatureSensor(uint8_t pin, LCDDisplay* lcd)
    : pin(pin), filteredTemp(0), initialized(false),
      lastReadTime(0), _lcd(lcd) {}

  void begin() {
    pinMode(pin, INPUT);
  }

  // NTC nối GND, R_FIXED nối VCC
  float readResistance() {
    int adc = analogRead(pin);
    if (adc <= 0) adc = 1;
    if (adc >= 1023) adc = 1022;

    float Vout = (adc / 1023.0f) * VCC;
    return R_FIXED * (VCC / Vout - 1.0f);
  }

  float readTemperatureK() {
    float Rntc = readResistance();
    return 1.0f / ((1.0f / T0) + (1.0f / B_CONST) * log(Rntc / R0));
  }

  float readTemperatureC() {
    return readTemperatureK() - 273.15f;
  }

  void update() {
    unsigned long currentTime = millis();
    if (currentTime - lastReadTime >= READ_INTERVAL) {
      lastReadTime = currentTime;

      float currentTemp = readTemperatureC();
      if (!initialized) {
        filteredTemp = currentTemp;
        initialized = true;
      } else {
        filteredTemp = ALPHA * currentTemp + (1 - ALPHA) * filteredTemp;
      }

      if (_lcd) {
        _lcd->setTemperature(filteredTemp + 63); // tuỳ logic hiển thị
      }
    }
  }

  float getFilteredTemperature() const {
    return filteredTemp;
  }
};

#endif
