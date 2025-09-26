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
    int brightness;       // độ sáng (0-255)
    MyLedState state;     // Trạng thái LED
    unsigned long delayMs; // thời gian sáng (ms)
    unsigned long prevMillis; // lưu thời điểm lần thay đổi cuối
    int blinkNum;        // số lần nhấp nháy đã thực hiện
    bool isActive;
  public:
    MyLed(int p) {
      pin = p;
      state = OFF;
      brightness = 255;
      delayMs = 500;
      prevMillis = 0;
      blinkNum = 0;
      isActive = false;
    }

    void begin() {
      pinMode(pin, OUTPUT);
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
      state = BLINKING;
      delayMs = intervalMs;
      isActive = true;
      blinkNum = count;
      prevMillis = millis();
    }

    void setBrightness(int value) {
      brightness = constrain(value, 0, 255);
      if (state == ON) {
        analogWrite(pin, brightness);
      }
    }

    // Gọi trong loop() để cập nhật trạng thái
    void update() {
      switch (state) {
        case OFF:
          // Không làm gì
          break;
        case ON:
          // Không làm gì
          break;
        case BLINKING:
          unsigned long currentMillis = millis();
          if(blinkNum > 0){
            // do something
            bool isPass = currentMillis - prevMillis >= delayMs;
            if(isActive && !isPass){
             analogWrite(pin, brightness);
            }
            else if(isActive && isPass){
              isActive = false;
              prevMillis = currentMillis;
              analogWrite(pin, 0);
              blinkNum--;
            }
            else if(!isActive && !isPass){
              analogWrite(pin, 0);
            }
            else{
              isActive = true;
              prevMillis = currentMillis;
              analogWrite(pin, brightness);
            }
          }else{
            off();
            isActive = false;
          }
          break;
      }
    }
};
#endif