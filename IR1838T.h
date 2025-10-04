#ifndef IR1838T_H
#define IR1838T_H
#include <IRremote.h>

class IR1838T {
private:
    int recvPin;
    IRrecv* irrecv;
    decode_results results;
    
    unsigned long lastCode;
    unsigned long currentCode;
    unsigned long lastDecodeTime;
    unsigned long debounceDelay;
    
    bool newCodeAvailable;
    MyServo* _servo; 
    NeoPixelRing* _ring;


public:
    // ====== Các mã button ======
    static const unsigned long BTN_POWER      = 0xFFA25D;
    static const unsigned long BTN_FUNC_STOP  = 0xFFE21D;
    static const unsigned long BTN_VOL_PLUS   = 0xFF629D;
    static const unsigned long BTN_BACK       = 0xFF22DD;
    static const unsigned long BTN_PLAY_PAUSE = 0xFF02FD;
    static const unsigned long BTN_NEXT       = 0xFFC23D;
    static const unsigned long BTN_VOL_MINUS  = 0xFFE01F;
    static const unsigned long BTN_EQ         = 0xFFA857;
    static const unsigned long BTN_0          = 0xFF6897;
    static const unsigned long BTN_100_PLUS   = 0xFF9867;
    static const unsigned long BTN_200_PLUS   = 0xFFB04F;
    static const unsigned long BTN_1          = 0xFF30CF;
    static const unsigned long BTN_2          = 0xFF18E7;
    static const unsigned long BTN_3          = 0xFF7A85;
    static const unsigned long BTN_4          = 0xFF10EF;
    static const unsigned long BTN_5          = 0xFF38C7;
    static const unsigned long BTN_6          = 0xFF5AA5;
    static const unsigned long BTN_7          = 0xFF42BD;
    static const unsigned long BTN_8          = 0xFF4AB5;
    static const unsigned long BTN_9          = 0xFF52AD;

    // ====== Constructor ======
    IR1838T(int pin, MyServo* servo = nullptr, NeoPixelRing* ring = nullptr, unsigned long debounce = 150)
        : recvPin(pin),
          debounceDelay(debounce),
          lastCode(0),
          currentCode(0),
          lastDecodeTime(0),
          newCodeAvailable(false),
          _servo(servo),
          _ring(ring)
    {
        irrecv = new IRrecv(recvPin);
    }

    // ====== Khởi tạo ======
    void begin() {
        if (irrecv != nullptr) {
            irrecv->enableIRIn();
            Serial.println("IR Receiver Started...");
        }
    }

    // ====== Cập nhật & xử lý tín hiệu ======
    void update() {
        if (irrecv->decode(&results)) {
            unsigned long now = millis();
            unsigned long decodedCode = results.value;

            if (decodedCode == 0xFFFFFFFF || decodedCode == 0) {
                irrecv->resume();
                return;
            }

            // Kiểm tra debounce
            if (decodedCode != lastCode || (now - lastDecodeTime) >= debounceDelay) {
                currentCode = decodedCode;
                lastCode = decodedCode;
                lastDecodeTime = now;
                newCodeAvailable = true;
            }

            irrecv->resume();
        }

        // Khi có mã mới, xử lý theo mã
        if (newCodeAvailable) {
            newCodeAvailable = false; // reset flag ngay khi xử lý

            switch (currentCode) {
                case BTN_POWER:       handlePower();       break;
                case BTN_FUNC_STOP:   handleFuncStop();    break;
                case BTN_VOL_PLUS:    handleVolPlus();     break;
                case BTN_VOL_MINUS:   handleVolMinus();    break;
                case BTN_PLAY_PAUSE:  handlePlayPause();   break;
                case BTN_NEXT:        handleNext();        break;
                case BTN_BACK:        handleBack();        break;
                case BTN_EQ:          handleEq();          break;

                case BTN_0:           handleDigit(0);      break;
                case BTN_1:           handleDigit(1);      break;
                case BTN_2:           handleDigit(2);      break;
                case BTN_3:           handleDigit(3);      break;
                case BTN_4:           handleDigit(4);      break;
                case BTN_5:           handleDigit(5);      break;
                case BTN_6:           handleDigit(6);      break;
                case BTN_7:           handleDigit(7);      break;
                case BTN_8:           handleDigit(8);      break;
                case BTN_9:           handleDigit(9);      break;

                case BTN_100_PLUS:    handle100Plus();     break;
                case BTN_200_PLUS:    handle200Plus();     break;

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
        // bật/tắt NeoPixel
        _ring->toggle();
    }

    void handleVolPlus() {
        // tăng sáng NeoPixel
        _ring->setBrightness(10);
    }

    void handleVolMinus() {
        // giảm sáng NeoPixel
        _ring->setBrightness(-10);
    }

    void handleFuncStop() {
        Serial.println("[ACTION] Function/Stop");
    }

    void handleBack() {
    
    }

    void handlePlayPause() {
        //mở cửa
        if (_servo) {
            _servo->resetAndGo();
        }
    }

    void handleNext() {
        Serial.println("[ACTION] Next");
    }

    void handleEq() {
        Serial.println("[ACTION] EQ");
    }

    void handleDigit(int digit) {
        Serial.print("[ACTION] Number ");
        Serial.println(digit);
    }

    void handle100Plus() {
        Serial.println("[ACTION] 100+");
    }

    void handle200Plus() {
        Serial.println("[ACTION] 200+");
    }
};
#endif