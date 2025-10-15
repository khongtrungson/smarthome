#ifndef NTC_H
#define NTC_H

class TemperatureSensor {
private:
  uint8_t pin;
  float R_fixed;
  float B;
  float R0;
  float T0;
  float Vcc;
  float alpha;         
  float filteredTemp;  
  bool initialized;
  unsigned long lastReadTime;
  unsigned long interval; 
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

  // Giả sử NTC mắc xuống GND, R_fixed nối Vcc
  float readResistance() {
    int adc = analogRead(pin);
    if (adc <= 0) adc = 1;
    if (adc >= 1023) adc = 1022;
    float Vout = (adc / 1023.0) * Vcc;

    // ✅ Dùng công thức này nếu R_fixed nối Vcc, NTC nối GND
    return R_fixed * (Vcc / Vout - 1.0);
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
      float currentTemp = readTemperatureC();
      if (!initialized) {
        filteredTemp = currentTemp;
        initialized = true;
      } else {
        filteredTemp = alpha * currentTemp + (1 - alpha) * filteredTemp;
      }
      if (_lcd) {
        _lcd->setTemperature(filteredTemp + 63);
      }
      Serial.println("Temperature: " + String(filteredTemp, 2) + " °C");
    }
  }

  float getFilteredTemperature() const {
    return filteredTemp;
  }
};

#endif
