#ifndef HUMIDITY_SENSOR_H
#define HUMIDITY_SENSOR_H


class HumiditySensor {
private:
    int _pin;           // chân digital cảm biến
    MyLed* _led;        // pointer LED cảnh báo
    Buzzer* _buzzer;    // pointer Buzzer cảnh báo

public:
    // Constructor: truyền chân cảm biến, pointer LED và Buzzer
    HumiditySensor(int pin, MyLed* led = nullptr, Buzzer* buzzer = nullptr)
        : _pin(pin), _led(led), _buzzer(buzzer) {}

    // Khởi tạo chân
    void begin() {
        pinMode(_pin, INPUT);
    }

    // Cập nhật trạng thái, bật/tắt LED và buzzer
    void update() {
        int val = digitalRead(_pin); // HIGH nếu độ ẩm vượt ngưỡng
        if (val == HIGH) {
            if (_led) _led->blink(300, 6); // nhấp nháy LED 6 lần
            if (_buzzer) _buzzer->alert(6, 500, 500); // cảnh báo 6 lần
            Serial.println("Humidity high! Warning!");
        }
    }
};

#endif
