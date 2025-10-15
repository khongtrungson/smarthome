#ifndef RAINSENSOR_H
#define RAINSENSOR_H

class RainSensor {
private:
    int pin;               // Chân digital kết nối cảm biến
    bool lastRaining;      // Trạng thái mưa trước đó
    RainServo* _servo; // pointer đến object RainServo (nếu cần)
public:
    // Constructor - truyền vào chân digital
    RainSensor(int digitalPin, RainServo* servo=nullptr)
        : pin(digitalPin),
          lastRaining(false),
          _servo(servo)
    {}


    // Khởi tạo chân
    void begin() {
        pinMode(pin, INPUT);
        int value = digitalRead(pin);
        lastRaining = (value == LOW);
    }

    // Cập nhật giá trị cảm biến (gọi liên tục trong loop)
    void update() {
        int value = digitalRead(pin);
        bool currentReading = (value == LOW); // LOW = có mưa, HIGH = không mưa

        unsigned long currentTime = millis();

        if (currentReading != lastRaining) {
            lastRaining = currentReading;
            if (currentReading == LOW) {
                // Có mưa
                // _servo->setRaining(true);
                Serial.println("[RainSensor] It is raining.");
            } else {
                // _servo->setRaining(false);
                Serial.println("[RainSensor] It stopped raining.");
            }
        }
    }

    // Kiểm tra có mưa không


    // Kiểm tra xem có thay đổi trạng thái (mưa bắt đầu / mưa tạnh)

};

#endif
