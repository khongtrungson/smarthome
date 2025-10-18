#ifndef FAN_H
#define FAN_H

#include <Arduino.h>

class Fan {
private:
    int pin;               // Chân điều khiển quạt
    bool lastState;        // Trạng thái trước đó
    bool currentState;     // Trạng thái hiện tại

public:
    // Constructor - truyền vào chân điều khiển
    Fan(int fanPin) : pin(fanPin), lastState(false), currentState(false) {}

    // Khởi tạo chân
    void begin() {
        pinMode(pin, OUTPUT);
        turnOff(); // Đảm bảo quạt tắt khi khởi động
    }

    // Bật quạt
    void turnOn() {
        currentState = true;
    }

    // Tắt quạt
    void turnOff() {
        currentState = false;
    }

    // Hàm update: kiểm tra thay đổi trạng thái để cập nhật chân điều khiển
    void update() {
        if (currentState != lastState) {
            digitalWrite(pin, currentState ? HIGH : LOW);
            lastState = currentState;
        }
    }

};

#endif
