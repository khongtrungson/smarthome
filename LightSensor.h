#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

class LightSensor {
private:
    uint8_t _pin;          
    int _lastValue;        
    int _level;            // 0 = tối, 1 = sáng
    int _lastLevel;        
    unsigned long _prevUpdateMillis; 
    MyLed* _led;           
    NeoPixelRing* _ring;   
    LCDDisplay* _lcd;
    MyServo* _servo;      

public:
    LightSensor(uint8_t pin, MyLed* led, NeoPixelRing* ring, LCDDisplay* lcd, MyServo* servo) 
        : _pin(pin), _led(led), _ring(ring), _lcd(lcd), _servo(servo),
          _lastValue(0), _level(0), _lastLevel(-1), _prevUpdateMillis(0) {}

    void begin() {
        pinMode(_pin, INPUT);  // digital input
        _lastValue = 0;
        _level = 0;
        _lastLevel = -1;
    }

    void update() {
        unsigned long now = millis();
        const unsigned long updateInterval = 500; // kiểm tra mỗi 0.5s
        if (now - _prevUpdateMillis < updateInterval) return;
        _prevUpdateMillis = now;

        // Đọc giá trị digital (0 hoặc 1)
        _lastValue = digitalRead(_pin);  
        _level = (_lastValue == HIGH) ? 1 : 0;

        // Chỉ cập nhật khi level thay đổi
        if (_level != _lastLevel) {
            // Cập nhật LED theo level
            
                if (_level == 0) {
                    _led->off();   // tối -> bật LED
                    // _servo->toInitial(); // gập cần mưa
                } else {
                    _led->on();  // sáng -> tắt LED
                    // _servo->toTarget(); // mở cần mưa
                }
        

            _lastLevel = _level;
        }
    }
};

#endif
