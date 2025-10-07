#ifndef LCDDISPLAY_H
#define LCDDISPLAY_H
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class LCDDisplay {
private:
    LiquidCrystal_I2C lcd;

public:
    // Constructor: truyền địa chỉ I2C (thường là 0x27 hoặc 0x3F), số cột, số hàng của màn hình LCD
    LCDDisplay(uint8_t address = 0x27, uint8_t cols = 16, uint8_t rows = 2)
        : lcd(address, cols, rows) {}

    // Khởi tạo LCD
    void begin() {
        lcd.init();
        lcd.noBacklight();
        lcd.clear();
        printLine(0, "LCD Initialized");
        printLine(1, "PASS:");
    }

    // Xóa màn hình
    void clear() {
        lcd.clear();
    }

    // In chuỗi ra vị trí x, y
 void printAt(uint8_t row, uint8_t col, const String &text) {
    lcd.setCursor(col, row);
    // Xóa vùng cũ (ví dụ: 10 ký tự)
    for (uint8_t i = col; i < 16; i++) {
        lcd.print(" ");
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

    // Tạo ký tự custom (0–7)
    void createChar(uint8_t location, uint8_t charmap[]) {
        lcd.createChar(location, charmap);
    }

    // Hiển thị ký tự custom
    void printCustom(uint8_t col, uint8_t row, uint8_t location) {
        lcd.setCursor(col, row);
        lcd.write(location);
    }
};

#endif
