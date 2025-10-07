#ifndef MY_SERVO_H
#define MY_SERVO_H
#include <Servo.h>
enum ServoState {
    IDLEE,
    TO_TARGET,
    BACK_TO_INITIAL
};

class MyServo {
 private:
    Servo servo;
    int pin;
    int initialAngle;
    int targetAngle;
    unsigned long lastMoveTime;
    unsigned long delayTime;
    ServoState state = IDLEE;


public:
    // Constructor
    MyServo(int servoPin, int startAngle = 90, int moveAngle = 0, unsigned long delayMs = 3000) {
        pin = servoPin;
        initialAngle = startAngle;
        targetAngle = moveAngle;
        delayTime = delayMs;
        lastMoveTime = 0;
        state = IDLEE;
    }

    // Khởi tạo servo
    void begin() {
        servo.attach(pin);
        // servo.write(initialAngle);  // Đưa servo về vị trí ban đầu
    }
    

    // Tùy chọn: Hàm để reset và quay lại target
    void resetAndGo() {
        state = IDLEE;
    } 

    // Gọi hàm này trong loop() để cập nhật trạng thái servo
    void update() {
        unsigned long currentMillis = millis();

        switch (state) {
            case IDLEE:
                servo.write(targetAngle);
                lastMoveTime = currentMillis;
                state = TO_TARGET;
                break;

            case TO_TARGET:
                if (currentMillis - lastMoveTime >= delayTime) {
                    servo.write(initialAngle);
                    lastMoveTime = currentMillis;
                    state = BACK_TO_INITIAL;
                }
                break;

            case BACK_TO_INITIAL:
                break;
        }
    }
};
#endif