#ifndef RAINSERVO_H
#define RAINSERVO_H

class RainServo : public MyServo {
private:
    bool isLight;
    bool isRaining;
    bool isOpen;  // <-- chỉ RainServo cần biết cửa mở hay đóng

public:
    RainServo(int servoPin, int rainSensorPin,
              int startAngle = 90, int moveAngle = 0,
              unsigned long delayMs = 0, unsigned long stepDelayMs = 20)
        : MyServo(servoPin, startAngle, moveAngle, delayMs, stepDelayMs)
    {
        isRaining = false;
        isLight = false;
        isOpen = false;
    }

    void begin() {
        MyServo::begin();
        MyServo::setWaitEnabled(false);
    }

    void setRaining(bool raining) { isRaining = raining; }
    void setLight(bool light) { isLight = light; }
    bool getIsOpen() const { return isOpen; }

    void update() {
        // 1️⃣ Nếu trời mưa => đóng cửa
        if (isRaining) {
            if (isOpen && !isMoving()) {
                toInitial();
                isOpen = false;
            }
        }
        // 2️⃣ Nếu trời sáng và không mưa => mở cửa
        else if (isLight) {
            if (!isOpen && !isMoving()) {
                toTarget();
                isOpen = true;
            }
        }
        // 3️⃣ Nếu trời tối => đóng cửa
        else {
            if (isOpen && !isMoving()) {
                toInitial();
                isOpen = false;
            }
        }

        // 4️⃣ Luôn gọi update() cha để servo hoạt động từng bước
        MyServo::update();
    }

    bool isMoving() const {
        return getState() != IDLEE;
    }

    ServoState getState() const {
        // giả sử bạn có getter trong MyServo (hoặc chuyển state thành protected)
        extern ServoState state;
        return state;
    }
};

#endif
