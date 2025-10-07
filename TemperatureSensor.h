#ifndef NTC_H
#define NTC_H

#include <Arduino.h>

class TemperatureSensor {
private:
  uint8_t pin;
  float R_fixed;
  float B;
  float R0;
  float T0;
  float Vcc;
  float alpha;         // hệ số lọc
  float filteredTemp;  // giá trị đã lọc
  bool initialized;
  unsigned long lastReadTime;
  unsigned long interval; // thời gian giữa 2 lần đọc (ms)
  LCDDisplay* _lcd;

public:
  TemperatureSensor(uint8_t pin, LCDDisplay* lcd, float R_fixed = 20000.0, float B = 3950.0,
      float R0 = 20000.0, float T0 = 298.15, float Vcc = 5.0,
      float alpha = 0.2, unsigned long interval = 10000)
    : pin(pin), _lcd(lcd), R_fixed(R_fixed), B(B), R0(R0), T0(T0), Vcc(Vcc),
      alpha(alpha), filteredTemp(0), initialized(false),
      lastReadTime(0), interval(interval) {}

  void begin() {
    pinMode(pin, INPUT);
  }

  float readResistance() {
    int adc = analogRead(pin);
    if (adc <= 0) adc = 1; // tránh chia cho 0
    float Vout = (adc / 1023.0) * Vcc;
    return R_fixed * (Vout / (Vcc - Vout));
  }

  float readTemperatureK() {
    float Rntc = readResistance();
    return 1.0 / ((1.0 / T0) + (1.0 / B) * log(Rntc / R0));
  }

  float readTemperatureC() {
    return readTemperatureK() - 273.15;
  }

  void update() {
    unsigned long currentTime = millis();
    if (currentTime - lastReadTime >= interval) {
      lastReadTime = currentTime;
      Serial.println("Reading temperature...");
    Serial.println("Resistance: " + String(readResistance()) + " Ohms");
    Serial.println("Temperature: " + String(readTemperatureC()) + " C");
      float currentTemp = readTemperatureC();
      if (!initialized) {
        filteredTemp = currentTemp;
        initialized = true;
      } else {
        filteredTemp = alpha * currentTemp + (1 - alpha) * filteredTemp - 120;
        if (_lcd) {
          _lcd->printAt(0, 8, "T:"+String(filteredTemp, 1)+" C");
        }
      }
    }
  }

  float getFilteredTemperature() const {
    return filteredTemp;
  }
};

#endif
