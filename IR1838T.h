#ifndef IR1838T_H
#define IR1838T_H

#include <IRremote.hpp>

class IR1838T {
private:
    int recvPin;
    unsigned long lastCode;
    unsigned long currentCode;
    unsigned long lastDecodeTime;
    unsigned long debounceDelay;
    bool newCodeAvailable;
    
    MyServo* _servo;
    NeoPixelRing* _ring;
    Buzzer* _buzzer;
    MyLed* _led;

public:
    // ====== Các mã button ======
    constexpr static unsigned long BTN_POWER      = 0xBA45FF00;
    constexpr static unsigned long BTN_MENU       = 0xB847FF00;
    constexpr static unsigned long BTN_TEST       = 0xBB44FF00;
    constexpr static unsigned long BTN_VOL_PLUS   = 0xBF40FF00; // +
    constexpr static unsigned long BTN_BACK       = 0xBC43FF00;
    constexpr static unsigned long BTN_LEFT       = 0xF807FF00;
    constexpr static unsigned long BTN_PAUSE      = 0xEA15FF00;
    constexpr static unsigned long BTN_RIGHT      = 0xF609FF00;
    constexpr static unsigned long BTN_VOL_MINUS  = 0xE619FF00; // -
    constexpr static unsigned long BTN_C          = 0xF20DFF00;

    // ====== Các mã số ======
    constexpr static unsigned long BTN_0          = 0xE916FF00;
    constexpr static unsigned long BTN_1          = 0xF30CFF00;
    constexpr static unsigned long BTN_2          = 0xE718FF00;
    constexpr static unsigned long BTN_3          = 0xA15EFF00;
    constexpr static unsigned long BTN_4          = 0xF708FF00;
    constexpr static unsigned long BTN_5          = 0xE31CFF00;
    constexpr static unsigned long BTN_6          = 0xA55AFF00;
    constexpr static unsigned long BTN_7          = 0xBD42FF00;
    constexpr static unsigned long BTN_8          = 0xAD52FF00;
    constexpr static unsigned long BTN_9          = 0xB54AFF00;

    // ====== Constructor ======
    IR1838T(int pin, MyServo* servo = nullptr, NeoPixelRing* ring = nullptr, 
            Buzzer* buzzer = nullptr, MyLed* led = nullptr, unsigned long debounce = 150)
        : recvPin(pin),
          debounceDelay(debounce),
          lastCode(0),
          currentCode(0),
          lastDecodeTime(0),
          newCodeAvailable(false),
          _servo(servo),
          _ring(ring),
          _buzzer(buzzer),
          _led(led)
    {}

    // ====== Khởi tạo ======
    void begin() {
        IrReceiver.begin(recvPin, DISABLE_LED_FEEDBACK);
        // Chỉ enable protocol 8
        Serial.println("IR Receiver Started...");
    }

    // ====== Cập nhật & xử lý tín hiệu ======
    void update() {
        if (IrReceiver.decode()) {
            unsigned long now = millis();
            unsigned long decodedCode = IrReceiver.decodedIRData.decodedRawData;

            // Bỏ qua mã lặp lại
            if (decodedCode == 0xFFFFFFFF || decodedCode == 0) {
                IrReceiver.resume();
                return;
            }

            // Kiểm tra debounce
            if (decodedCode != lastCode || (now - lastDecodeTime) >= debounceDelay) {
                currentCode = decodedCode;
                lastCode = decodedCode;
                lastDecodeTime = now;
                newCodeAvailable = true;
               Serial.print("Decoded IR code: ");
                Serial.println(currentCode, HEX);
                Serial.println(IrReceiver.decodedIRData.protocol);

            }

            IrReceiver.resume();
        }

        // Xử lý khi có mã mới
        if (newCodeAvailable) {
            newCodeAvailable = false;

            switch (currentCode) {
                case BTN_POWER:      handlePower();         break;
                case BTN_MENU:       handleMenu();          break;
                case BTN_TEST:       handleTest();          break;
                case BTN_VOL_PLUS:   handleVolPlus();       break;
                case BTN_VOL_MINUS:  handleVolMinus();      break;
                case BTN_PAUSE:      handlePause();         break;
                case BTN_BACK:       handleBack();          break;
                case BTN_LEFT:       handleLeft();          break;
                case BTN_RIGHT:      handleRight();         break;
                case BTN_C:          handleC();             break;

                case BTN_0: case BTN_1: case BTN_2: case BTN_3:
                case BTN_4: case BTN_5: case BTN_6: case BTN_7:
                case BTN_8: case BTN_9:
                    handleDigit(currentCode);
                    break;

                default:
                    Serial.print("Unknown code: ");
                    Serial.println(currentCode, HEX);
                    break;
            }
        }
    }

private:
    // ====== Các hàm xử lý hành động ======
    void handlePower() {
        Serial.println("[ACTION] Power");
        _led->blink(100,2);
        if (_ring) _ring->turnOff();
    }

    void handleMenu() {
        _led->blink(100,2);
        Serial.println("[ACTION] Menu");
        // if (_buzzer) _buzzer->playMelody(welcomeChime.notes, welcomeChime.durations, welcomeChime.length);
    }

    void handleTest() {
        _led->blink(100,2);
        Serial.println("[ACTION] Test");
        if (_ring) _ring->startRainbowRotate(2, 3000);
    }

    void handleVolPlus() {
        _led->blink(100,2);
        Serial.println("[ACTION] Volume +");
        if (_ring) _ring->setBrightness(10);
    }

    void handleVolMinus() {
        _led->blink(100,2);
        Serial.println("[ACTION] Volume -");
        if (_ring) _ring->setBrightness(-10);
    }

    void handlePause() {
        _led->blink(100,2);
        Serial.println("[ACTION] Pause");
        if (_servo) _servo->toTarget();
    }

    void handleBack() {
        _led->blink(100,2);
        Serial.println("[ACTION] Back");
    }

    void handleLeft() {
        _led->blink(100,2);
        Serial.println("[ACTION] Left - Jingle Bells");
        // if (_buzzer) _buzzer->playMelody(jingleBells.notes, jingleBells.durations, jingleBells.length);
    }

    void handleRight() {
        _led->blink(100,2);
        Serial.println("[ACTION] Right - Gentle Piano");
        // if (_buzzer) _buzzer->playMelody(gentlePiano.notes, gentlePiano.durations, gentlePiano.length);
    }

    void handleC() {
        _led->blink(100,2);
        Serial.println("[ACTION] C (Clear)");
        if (_ring) _ring->fill(0, 0, 0); // Tắt hết LED
    }

    void handleDigit(unsigned long code) {
        _led->blink(100,2);
        int digit = -1;
        if (_ring->getBrightness() < 50) {
            _ring->setBrightness(50); // đảm bảo đủ sáng để thấy màu
        }
        if (code == BTN_0) {
            if (_ring) _ring->fill(255, 255, 255); // Trắng
            digit = 0;
        }
        else if (code == BTN_1) {
            if (_ring) _ring->fill(255, 0, 0); // Đỏ
            digit = 1;
        }
        else if (code == BTN_2) {
            if (_ring) _ring->fill(255, 165, 0); // Cam
            digit = 2;
        }
        else if (code == BTN_3) {
            if (_ring) _ring->fill(255, 255, 0); // Vàng
            digit = 3;
        }
        else if (code == BTN_4) {
            if (_ring) _ring->fill(0, 255, 0); // Xanh lá
            digit = 4;
        }
        else if (code == BTN_5) {
            if (_ring) _ring->fill(0, 255, 255); // Xanh cyan
            digit = 5;
        }
        else if (code == BTN_6) {
            if (_ring) _ring->fill(0, 0, 255); // Xanh dương
            digit = 6;
        }
        else if (code == BTN_7) {
            if (_ring) _ring->fill(128, 0, 255); // Tím
            digit = 7;
        }
        else if (code == BTN_8) {
            if (_ring) _ring->fill(255, 0, 255); // Hồng tím (Magenta)
            digit = 8;
        }
        else if (code == BTN_9) {
            if (_ring) _ring->fill(255, 192, 203); // Hồng nhạt
            digit = 9;
        }

        if (digit != -1) {
            Serial.print("[ACTION] Number ");
            Serial.println(digit);
        }
    }
};

#endif