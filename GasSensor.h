#ifndef GAS_SENSOR_H
#define GAS_SENSOR_H


class GasSensor {
private:
    int _pin;           // chân digital của cảm biến
    int lastState=0;    // trạng thái trước đó
    MyLed* _led;        // pointer đến object MyLed
    Buzzer* _buzzer;    // pointer đến object Buzzer
    NeoPixelRing* _ring; // pointer đến object NeoPixelRing (nếu cần)
    Fan* _fan;          // pointer đến object Fan (nếu cần)
public:
    // Constructor: truyền vào chân cảm biến, pointer LED và Buzzer
    GasSensor(int pin, MyLed* led = nullptr, Buzzer* buzzer = nullptr, NeoPixelRing* ring = nullptr, Fan* fan = nullptr)
        : _pin(pin), _led(led), _buzzer(buzzer), _ring(ring), _fan(fan) {}

    // Khởi tạo chân cảm biến
    void begin() {
        pinMode(_pin, INPUT);
    }

    // Cập nhật trạng thái: nếu gas được phát hiện thì bật LED và Buzzer
    void update() {
        int val = digitalRead(_pin); // HIGH nếu phát hiện gas
        if (val != lastState) {
            lastState = val;
            if (val == HIGH) {
            // _led->blink(300, 6); // nhấp nháy LED 6 lần
            // _buzzer->beep(5000); // cảnh báo 6 lần
            // _ring->fill(255, 255, 0); // Vàng
            // _fan->turnOn(); // bật quạt
            Serial.println("[GasSensor] Gas detected! Activating alarm and fan.");
            }
        }
    }
};

#endif
