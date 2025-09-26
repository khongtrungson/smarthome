#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

class LightSensor {
private:
    uint8_t _pin;          // Chân cảm biến analog
    int _lastValue;        // Giá trị đọc lần gần nhất
    int _level;            // Cấp độ sáng (0-4)
    int _lastLevel = -1;  // lưu level trước đó, -1 = chưa có giá trị
    int _thresholds[4] = {200, 400, 600, 800};  // Ngưỡng chia cấp độ
    MyLed* _led;            // Đối tượng MyLed để điều khiển LED
public:
    // Constructor
    LightSensor(uint8_t pin, MyLed& led) : 
    _pin(pin), _lastValue(0), _level(0), _led(&led) {
    
    }

    // Hàm begin() để khởi tạo
    void begin() {
        pinMode(_pin, INPUT);  // Đặt chân là input
        _lastValue = 0;
        _level = 0;
        _led->on();
    }

    // Hàm đọc và cập nhật trạng thái
    void update() {
        _lastValue = analogRead(_pin);
        _level = calculateLevel(_lastValue);
         if (_level != _lastLevel) {
            // do something when level changes
            _led->setBrightness((_level + 1) * 51); // Cấp độ 0-4 tương ứng với độ sáng 0-255
            _lastLevel = _level;
             Serial.print("Light level changed: ");
             Serial.println(_level);
        }
    }

    // Xác định cấp độ sáng từ giá trị analog
    int calculateLevel(int value) {
        if (value < _thresholds[0]) return 0;
        else if (value < _thresholds[1]) return 1;
        else if (value < _thresholds[2]) return 2;
        else if (value < _thresholds[3]) return 3;
        else return 4;
    }

    // Getter
    int getValue() const { return _lastValue; }
    int getLevel() const { return _level; }

};

#endif
