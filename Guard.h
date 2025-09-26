#ifndef GUARD_H
#define GUARD_H

#include <Keypad.h>

// Lớp Guard: Điều khiển thiết bị bằng mật khẩu với bàn phím ma trận 4x4
class Guard {
    private:
    const char* _password;      // Mật khẩu đúng
    String _input;              // Chuỗi nhập từ keypad
    Keypad* _keypad;            // Đối tượng keypad
    uint8_t _maxAttempts;       // Số lần nhập sai tối đa
    uint8_t _failCount;         // Số lần nhập sai hiện tại
    bool _lockedOut;            // Đã bị khóa do nhập sai quá số lần
    MyServo* _servo;          // Đối tượng servo để mở khóa (nếu cần)
    Buzzer* _buzzer;          // Đối tượng buzzer để cảnh báo (nếu cần)
    LCDDisplay* _lcd;        // Đối tượng LCD để hiển thị (nếu cần)
    // Kiểm tra mật khẩu nhập vào
    bool checkPassword() {
      if (_input == _password) {
        // Mật khẩu đúng, thực hiện hành động mở khóa ở đây
        _servo->resetAndGo(); // quay servo về vị trí mở khóa
        _failCount = 0; // reset số lần nhập sai
        _lockedOut = false;
        return true;
      } else {
        // Mật khẩu sai, có thể thêm hành động cảnh báo ở đây
        if (_failCount >= _maxAttempts) {
          _lockedOut = true;
          _buzzer->alert(5, 300, 300); // cảnh báo 5 lần
          _lcd->printLine(1, "Locked out!");
        }
        _failCount++;
        return false;
      }
    }

  public:
    // Khởi tạo với mật khẩu, mảng chân hàng và cột của keypad
    Guard(const char* password, byte* rowPins, byte* colPins, MyServo* servo = nullptr, Buzzer* buzzer = nullptr, LCDDisplay* lcd = nullptr, uint8_t maxAttempts = 3  )
      : _password(password), _input(""), _servo(servo), _buzzer(buzzer), _lcd(lcd), _maxAttempts(maxAttempts), _failCount(0), _lockedOut(false)
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
      char key = _keypad->getKey();
      if (key) {
        if (key == '#') {
          checkPassword();
          _input = "";
        } else if (key == '*') {
          _input = "";
        } else {
          _input += key;
          if (_input.length() > 4) { // giới hạn độ dài nhập
            _input = "";
          }
          _lcd->printLine(2,"PASS: " +  _input); // hiển thị chuỗi nhập trên LCD
        }
      }
    }


};

#endif