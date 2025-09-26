# MyLed - Arduino LED Manager

`MyLed` là một class giúp quản lý LED trong Arduino theo cách dễ dàng và linh hoạt hơn.  
Hỗ trợ bật/tắt, điều chỉnh độ sáng (PWM), nhấp nháy bằng `millis()` mà không chặn chương trình.

---

## 🔑 Chức năng chính

### 1. Quản lý trạng thái LED

- `on()` → bật LED
- `off()` → tắt LED
- `toggle()` → đảo trạng thái

### 2. Quản lý độ sáng (PWM)

- `setBrightness(value)` → đặt độ sáng (0–255)
- `getBrightness()` → lấy độ sáng hiện tại

### 3. Quản lý nhấp nháy (dùng millis)

- `setBlink(onTime, offTime)` → cấu hình sáng/tắt theo chu kỳ (ms)
- `stopBlink()` → dừng nhấp nháy
- `update()` → phải gọi trong `loop()` để cập nhật trạng thái

### 4. Khởi tạo

- `begin()` → setup `pinMode` và trạng thái ban đầu

---

## 🛠️ Cách sử dụng

````cpp
#include "MyLed.h"

MyLed led(9); // LED gắn vào chân PWM số 9

void setup() {
  led.begin();
  led.setBrightness(128);   // sáng 50%
  led.setBlink(500, 300);   // sáng 500ms, tắt 300ms
}

void loop() {
  led.update(); // luôn gọi để cập nhật LED
}
# MyServo - Arduino Servo Manager

`MyServo` là một class giúp điều khiển Servo trong Arduino một cách **linh hoạt và không chặn chương trình**.
Khác với cách dùng `delay()` thông thường, class này quản lý servo bằng `millis()`, cho phép servo quay dần dần đến góc mục tiêu trong khi các tác vụ khác vẫn hoạt động bình thường.

---

## 🔑 Chức năng chính

### 1. Khởi tạo
- `MyServo(int pin)` → tạo servo gắn vào chân `pin`
- `begin()` → gắn servo (`attach`) và đặt về góc mặc định (0°)

### 2. Điều khiển góc
- `rotateTo(int angle, unsigned long speed = 20)`
  Quay servo đến `angle` (0–180°) với tốc độ `speed` ms mỗi bước (mặc định 20ms).

### 3. Quản lý trạng thái
- `update()` → phải gọi trong `loop()`, giúp servo di chuyển dần đến mục tiêu
- `isMoving()` → trả về `true` nếu servo đang quay
- `getAngle()` → trả về góc hiện tại của servo

---

## 🛠️ Cách sử dụng

### Ví dụ 1: Quay servo đến góc cố định
```cpp
#include <Servo.h>
#include "MyServo.h"

MyServo myServo(9); // servo gắn vào chân số 9

void setup() {
  myServo.begin();
  myServo.rotateTo(90, 15); // quay tới 90° với tốc độ 15ms mỗi bước
}

void loop() {
  myServo.update(); // luôn gọi trong loop
}
# Buzzer - Arduino Buzzer Manager

`Buzzer` là một class giúp điều khiển buzzer trong Arduino một cách **linh hoạt và không chặn chương trình**.
Khác với cách dùng `delay()` thông thường, class này quản lý buzzer bằng `millis()`, cho phép phát **beep, alert, melody** trong khi các tác vụ khác vẫn hoạt động bình thường.

---

## 🔑 Chức năng chính

### 1. Khởi tạo
- `Buzzer(int pin)` → tạo buzzer gắn vào chân `pin`
- `begin()` → cấu hình chân output và tắt buzzer ban đầu

### 2. Điều khiển cơ bản
- `on(unsigned int freq = 1000)` → bật buzzer với tần số `freq` (mặc định 1000Hz)
- `off()` → tắt buzzer
- `beep(unsigned int freq = 1000, unsigned long duration = 200)` → phát 1 beep trong `duration` ms
- `tonePlay(unsigned int freq, unsigned long duration = 0)` → phát tone với tần số `freq`, có thể kèm thời gian
- `stopTone()` → dừng phát tone

### 3. Cảnh báo (Alert)
- `alert(int times = 3, unsigned long onDuration = 200, unsigned long offDuration = 200, unsigned int freq = 1000)`
  Phát chuỗi beep cảnh báo: `times` lần, mỗi lần **on** và **off** theo thời gian chỉ định.

### 4. Phát giai điệu (Melody)
- `playMelody(const int *notes, const int *durations, int length)` → phát dãy nốt nhạc với độ dài và thời lượng riêng
- `isPlayingMelody()` → trả về `true` nếu melody đang phát

### 5. Quản lý trạng thái
- `update()` → phải gọi trong `loop()`, giúp quản lý **alert** và **melody** không bị chặn chương trình

---

## 🛠️ Cách sử dụng

### Ví dụ 1: Bật và tắt buzzer
```cpp
#include "Buzzer.h"

Buzzer buzzer(8);

void setup() {
  buzzer.begin();   // khởi tạo buzzer
  buzzer.on(2000);  // bật với tần số 2000Hz
  delay(500);
  buzzer.off();     // tắt buzzer
}

void loop() {}
````
