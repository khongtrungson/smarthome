#ifndef GAS_SENSOR_H
#define GAS_SENSOR_H

#include <Arduino.h>
#include "MyLed.h"
#include "Buzzer.h"

class GasSensor {
private:
    int _pin;           // chân digital của cảm biến
    MyLed* _led;        // pointer đến object MyLed
    Buzzer* _buzzer;    // pointer đến object Buzzer

public:
    // Constructor: truyền vào chân cảm biến, pointer LED và Buzzer
    GasSensor(int pin, MyLed* led = nullptr, Buzzer* buzzer = nullptr)
        : _pin(pin), _led(led), _buzzer(buzzer) {}

    // Khởi tạo chân cảm biến
    void begin() {
        pinMode(_pin, INPUT);
        if (_led) _led->off();        // đảm bảo LED tắt lúc khởi động
        if (_buzzer) _buzzer->off();  // đảm bảo buzzer tắt lúc khởi động
    }

    // Cập nhật trạng thái: nếu gas được phát hiện thì bật LED và Buzzer
    void update() {
        int val = digitalRead(_pin); // HIGH nếu phát hiện gas
        if (val == HIGH) {
            if (_led) _led->blink(300, 6); // nhấp nháy LED 6 lần
            if (_buzzer) _buzzer->alert(6, 500, 500); // cảnh báo 6 lần
            Serial.println("Gas detected! Warning!");
        }
    }
};

#endif
