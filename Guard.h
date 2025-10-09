#ifndef GUARD_H
#define GUARD_H

#include <Keypad.h>
#include "Songs.h"
// Lớp Guard: Điều khiển thiết bị bằng mật khẩu với bàn phím ma trận 4x4
class Guard {
    private:
    const char* _password;      // Mật khẩu đúng
    String _input;              // Chuỗi nhập từ keypad
    Keypad* _keypad;            // Đối tượng keypad
    uint8_t _maxAttempts;       // Số lần nhập sai tối đa
    uint8_t _failCount = 0;         // Số lần nhập sai hiện tại
    bool _lockedOut;            // Đã bị khóa do nhập sai quá số lần
    unsigned long _lockStartMillis = 0;  // thời điểm bắt đầu khóa
    const unsigned long _lockDuration = 10000; // 10 giây
    MyServo* _servo;          // Đối tượng servo để mở khóa (nếu cần)
    Buzzer* _buzzer;          // Đối tượng buzzer để cảnh báo (nếu cần)
    LCDDisplay* _lcd;        // Đối tượng LCD để hiển thị (nếu cần)
    NeoPixelRing* _ring; // Đối tượng vòng LED để cảnh báo (nếu cần)
    // Kiểm tra mật khẩu nhập vào
    bool checkPassword() {
      _lcd->setFailCount(_failCount);
      if (_input == _password) {
        // Mật khẩu đúng, thực hiện hành động mở khóa ở đây
        _servo->resetAndGo(); // quay servo về vị trí mở khóa
        _failCount = 0; // reset số lần nhập sai
        _lcd->setFailCount(_failCount);
        _lockedOut = false;
        // _buzzer->playMelody(welcomeChime.notes, welcomeChime.durations, welcomeChime.length);
        _ring->startRainbowRotate(2,3000); // hiệu ứng rainbow xoay
        return true;
      } else {
        // Mật khẩu sai, có thể thêm hành động cảnh báo ở đây
        if (_failCount >= _maxAttempts) {
          _lockedOut = true;
          _lockStartMillis = millis();   // bắt đầu khóa
          // _buzzer->alert(4, 400, 400);
          // quá 3 lần thì đợi 10s mới nhập tiếp được
        }
        if (_failCount >= _maxAttempts) {
          _buzzer->beep(200,2);
        }else{
          _buzzer->beep(200);
        }
        _failCount++;
        _lcd->setFailCount(_failCount);
        return false;
      }
    }

  public:
    // Khởi tạo với mật khẩu, mảng chân hàng và cột của keypad
    Guard(const char* password, byte* rowPins, byte* colPins, MyServo* servo = nullptr, Buzzer* buzzer = nullptr, LCDDisplay* lcd = nullptr, NeoPixelRing* ring = nullptr, uint8_t maxAttempts = 3  )
      : _password(password), _input(""), _servo(servo), _buzzer(buzzer), _lcd(lcd), _ring(ring), _maxAttempts(maxAttempts), _failCount(0), _lockedOut(false)
    {
      // Ma trận phím 4x4 mặc định
      static char keys[4][4] = {
        {'1','2','3','A'},
        {'4','5','6','B'},
        {'7','8','9','C'},
        {'*','0','#','D'}
      };
      _keypad = new Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);
    }
    void begin() {
      
    }

    // Hàm xử lý chính, gọi liên tục trong loop()
    void update() {
       if (_lockedOut) {
        unsigned long elapsed = millis() - _lockStartMillis;
        if (elapsed >= _lockDuration) {
            // Hết 10 giây, mở khóa
            _lockedOut = false;
            _failCount = 0;
            _lcd->printLine(1, "PASS:");
        } else {
            // Hiển thị đếm ngược 10s nhưng chỉ khi số giây thay đổi
            static int prevSecond = -1;
            int secondsLeft = (_lockDuration - elapsed) / 1000;
            if (secondsLeft != prevSecond) {
                _lcd->printLine(1, "Locked: " + String(secondsLeft) + "s");
                prevSecond = secondsLeft;
            }
            return; // không nhận phím
        }
    }
      char key = _keypad->getKey();
      if (key) {
        if (key == '#') {
          checkPassword();
          _input = "";
        } else if (key == '*') {
          _input = "";
           _lcd->printLine(1,"PASS:" +  _input);
        } else {
          _input += key;
          if (_input.length() > 4) { // giới hạn độ dài nhập
            _input = "";
            _lcd->printLine(1,"PASS:" +  _input);
          }
          _lcd->printLine(1,"PASS:" +  _input); // hiển thị chuỗi nhập trên LCD
        }
      }
    }


};

#endif