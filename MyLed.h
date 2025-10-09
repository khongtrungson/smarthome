#ifndef MY_LED_H
#define MY_LED_H

enum MyLedState {
    OFF,
    ON,
    BLINKING
};

class MyLed {
  private:
    int pin;
    int brightness;         // độ sáng (0-255)
    MyLedState state;       // Trạng thái hiện tại
    MyLedState prevState;   // Trạng thái trước khi blink
    unsigned long delayMs;  // thời gian sáng/tắt mỗi chu kỳ (ms)
    unsigned long prevMillis;
    int blinkNum;           // số lần nhấp nháy còn lại
    bool isActive;          // đang bật trong chu kỳ blink

  public:
    MyLed(int p) {
      pin = p;
      brightness = 255;
      state = OFF;
      prevState = OFF;
      delayMs = 500;
      prevMillis = 0;
      blinkNum = 0;
      isActive = false;
    }

    void begin() {
      pinMode(pin, OUTPUT);
      analogWrite(pin, 0);
    }

    void on() {
      state = ON;
      analogWrite(pin, brightness);
    }

    void off() {
      state = OFF;
      analogWrite(pin, 0);
    }

    void blink(unsigned long intervalMs, int count) {
      prevState = state;      // Lưu trạng thái trước khi nhấp nháy
      state = BLINKING;
      delayMs = intervalMs;
      blinkNum = count * 2;   // mỗi chu kỳ gồm sáng + tắt
      isActive = true;
      prevMillis = millis();
    }

    void setBrightness(int value) {
      brightness = constrain(value, 0, 255);
      if (state == ON) {
        analogWrite(pin, brightness);
      }
    }

    void update() {
      if (state == BLINKING) {
        unsigned long currentMillis = millis();
        if (currentMillis - prevMillis >= delayMs) {
          prevMillis = currentMillis;
          isActive = !isActive; // Đảo trạng thái sáng/tắt
          blinkNum--;

          if (isActive) analogWrite(pin, brightness);
          else analogWrite(pin, 0);

          // Hết số lần blink → khôi phục trạng thái trước đó
          if (blinkNum <= 0) {
            state = prevState;
            if (prevState == ON) analogWrite(pin, brightness);
            else analogWrite(pin, 0);
          }
        }
      }
    }
};

#endif
