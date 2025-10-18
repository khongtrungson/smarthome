#ifndef RAINSENSOR_H
#define RAINSENSOR_H

class RainSensor {
private:
    int pin;               // Chân digital kết nối cảm biến
    bool lastRaining;      // Trạng thái mưa trước đó
    MyServo* _servo;    // Con trỏ đến đối tượng MyServo để điều khiển cần mưa
public:
    // Constructor - truyền vào chân digital
    RainSensor(int digitalPin, MyServo* servo)
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
               _servo->toTarget(); // Mưa bắt đầu - mở cần mưa
            }
        }
    }

};

#endif
