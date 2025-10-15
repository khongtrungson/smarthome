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

public:
    LightSensor(uint8_t pin, MyLed* led, NeoPixelRing* ring, LCDDisplay* lcd) 
        : _pin(pin), _led(led), _ring(ring), _lcd(lcd),
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
            Serial.print("Light Level: ");
            Serial.println(_level);

            // Cập nhật LED theo level
            if (_led) {
                if (_level == 0) {
                    _led->off();   // tối -> bật LED
                } else {
                    _led->on();  // sáng -> tắt LED
                }
            }

            _lastLevel = _level;
        }
    }
};

#endif
