#ifndef VIBRATION_SENSOR_H
#define VIBRATION_SENSOR_H

class VibrationSensor {
private:
    int _pin;                   
    unsigned long _debounceTime; 
    unsigned int _threshold;    
    unsigned long _lastTrigger;
    unsigned int _count;
    NeoPixelRing* _ring;
    LCDDisplay* _lcd;
    Buzzer* _buzzer;
    MyLed* _led;

public:
    // Constructor
    VibrationSensor(int pin, NeoPixelRing* ring, LCDDisplay* lcd, Buzzer* buzzer, MyLed* led, unsigned int threshold = 30, unsigned long debounceTime = 400) {
        _pin = pin;
        _ring = ring;
        _lcd = lcd;
        _buzzer = buzzer;
        _led = led;
        _threshold = threshold;
        _debounceTime = debounceTime;
        _lastTrigger = 0;
        _count = 0;
    }

    void begin() {
        pinMode(_pin, INPUT);
    }

    void update() {
        if (checkTrigger()) {
            incrementCount();
            checkThreshold();
        }
    }

    // ---- Các hàm tiện ích ----
    bool checkTrigger() {
        unsigned long now = millis();
        int state = digitalRead(_pin);

        if (state == HIGH && (now - _lastTrigger > _debounceTime)) {
            _lastTrigger = now;
            return true;
        }
        return false;
    }

    void incrementCount() {
        _count++;
        Serial.print("Rung hien tai: ");
        Serial.println(_count);
    }

    void checkThreshold() {
        if (_count >= _threshold) {
            _buzzer->beep(2000); // beep 2s
            _led->blink(500, 5); // nhấp nháy LED 5 lần
            _ring->fill(255, 0, 0); // đỏ
            _count = 0; // reset count sau khi đạt ngưỡng
        }
    }

    unsigned int getCount() {
        return _count;
    }


    void setThreshold(unsigned int threshold) {
        _threshold = threshold;
    }
};

#endif
