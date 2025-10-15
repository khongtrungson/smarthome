#ifndef LCDDISPLAY_H
#define LCDDISPLAY_H
#include <LiquidCrystal_I2C.h>

class LCDDisplay {
private:
    LiquidCrystal_I2C lcd;
    float lastTemperature;
    float temperature;
    uint8_t _lastFailCount;
    uint8_t _failCount;

public:
    // Constructor
    LCDDisplay(uint8_t address = 0x27, uint8_t cols = 16, uint8_t rows = 2)
        : lcd(address, cols, rows),
          temperature(0),
          lastTemperature(25),  // ép in lần đầu
          _failCount(0),
          _lastFailCount(255)     // ép in lần đầu
    {}

    // Khởi tạo LCD
    void begin() {
        lcd.init();
        backlightOn();
        lcd.clear();
        printAt(0, 0, 4, "F: 0");
        printAt(0, 8, 8, "T: 0.0C");
        printLine(1, "PASS:");
    }

    // Xóa màn hình
    void clear() {
        lcd.clear();
    }

    // In chuỗi ra vị trí x, y
    void printAt(uint8_t row, uint8_t col, uint8_t length, const String &text) {
        lcd.setCursor(col, row);
        // Xóa vùng cũ
        if (length == 0) {
            for (uint8_t i = col; i < 16; i++) {
                lcd.print(" ");
            }
        } else {
            for (uint8_t i = 0; i < length; i++) {
                lcd.print(" ");
            }
        }
        lcd.setCursor(col, row);
        lcd.print(text);
    }

    // In 1 dòng (ghi đè toàn bộ dòng)
    void printLine(uint8_t row, const String &text) {
        lcd.setCursor(0, row);
        lcd.print("                "); // xóa dòng (16 ký tự)
        lcd.setCursor(0, row);
        lcd.print(text);
    }

    // Bật/tắt đèn nền
    void backlightOn() {
        lcd.backlight();
    }
    void backlightOff() {
        lcd.noBacklight();
    }

    // ====== Setter ======
    void setFailCount(uint8_t count) {
        _failCount = count;
    }

    void setTemperature(float temp) {
        temperature = temp;
    }

    // ====== Update ======
    void update() {
        bool updated = false;

        // Nếu fail count thay đổi → in lại
        if (_failCount != _lastFailCount) {
            _lastFailCount = _failCount;
            printAt(0, 0, 4, "F: " + String(_failCount));
            updated = true;
        }

        // Nếu temperature thay đổi (làm tròn 1 chữ số thập phân để tránh nhiễu)
        if (fabs(temperature - lastTemperature) >= 0.1) {
            lastTemperature = temperature;
            String tempStr = "T: " + String(temperature, 1) + "C";
            printAt(0, 8, 8, tempStr);
            updated = true;
        }

        // Nếu có cập nhật, có thể thêm log hoặc nháy đèn nhẹ (nếu muốn)
        if (updated) {
            // ví dụ: nháy nhanh đèn nền (tùy chọn)
            // backlightOff();
            // delay(20);
            // backlightOn();
        }
    }
};

#endif
