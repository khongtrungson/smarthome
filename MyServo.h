#ifndef MY_SERVO_H
#define MY_SERVO_H
#include <Servo.h>

enum ServoState {
    IDLEE,
    TO_TARGET,
    WAIT_AT_TARGET,
    BACK_TO_INITIAL
};

class MyServo {
 protected:
    Servo servo;
    int pin;
    int initialAngle;
    int targetAngle;
    int currentAngle;
    unsigned long lastMoveTime;
    unsigned long delayTime;
    unsigned long stepDelay;   // tốc độ quay (thời gian giữa 2 bước)
    ServoState state = IDLEE;
    bool movingToTarget = true;
    bool waitEnabled = true;   // cờ bật/tắt đợi tại target

 public:
    MyServo(int servoPin, int startAngle = 90, int moveAngle = 0,
             unsigned long delayMs = 3000, unsigned long stepDelayMs = 20)
    {
        pin = servoPin;
        initialAngle = startAngle;
        targetAngle = moveAngle;
        delayTime = delayMs;
        stepDelay = stepDelayMs;
        lastMoveTime = 0;
        currentAngle = startAngle;
        state = IDLEE;
    }

    void begin() {
        servo.attach(pin);
        servo.write(initialAngle);
    }

    void toIDLE() {
        state = IDLEE;
    }

    // ==== Bật hoặc tắt việc chờ tại target ====
    void setWaitEnabled(bool enabled) {
        waitEnabled = enabled;
    }

    // ==== Chỉ đổi trạng thái ====
    void toTarget() {
        state = TO_TARGET;
        movingToTarget = true;
    }

    void toInitial() {
        state = BACK_TO_INITIAL;
        movingToTarget = false;
    }

    // ==== Logic chính (giữ nguyên + sửa nhẹ ở WAIT_AT_TARGET) ====
    void update() {
        unsigned long currentMillis = millis();

        switch (state) {
            case IDLEE:
                // Không làm gì khi idle
                break;

            case TO_TARGET:
                if (currentMillis - lastMoveTime >= stepDelay) {
                    lastMoveTime = currentMillis;

                    if (currentAngle < targetAngle) {
                        currentAngle++;
                        servo.write(currentAngle);
                    } else if (currentAngle > targetAngle) {
                        currentAngle--;
                        servo.write(currentAngle);
                    } else {
                        // Đã tới target
                        lastMoveTime = currentMillis;
                        if (waitEnabled) {
                            state = WAIT_AT_TARGET;
                        } else {
                            // Bỏ qua chờ, dừng lại luôn
                            movingToTarget = false;
                            state = IDLEE;
                        }
                    }
                }
                break;

            case WAIT_AT_TARGET:
                if (currentMillis - lastMoveTime >= delayTime) {
                    movingToTarget = false;
                    state = BACK_TO_INITIAL;
                }
                break;

            case BACK_TO_INITIAL:
                if (currentMillis - lastMoveTime >= stepDelay) {
                    lastMoveTime = currentMillis;

                    if (currentAngle < initialAngle) {
                        currentAngle++;
                        servo.write(currentAngle);
                    } else if (currentAngle > initialAngle) {
                        currentAngle--;
                        servo.write(currentAngle);
                    } else {
                        state = IDLEE;
                    }
                }
                break;
        }
    }
};

#endif
