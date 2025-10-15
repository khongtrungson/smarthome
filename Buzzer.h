#ifndef BUZZER_H
#define BUZZER_H

class Buzzer {
private:
    int pin;

    int remainingBeeps = 0;
    unsigned long beepDuration = 0;
    unsigned long nextToggleTime = 0;
    bool isOn = false;
    unsigned long pauseBetweenBeeps = 500; // nghỉ giữa các beep

public:
    Buzzer(int buzzerPin) : pin(buzzerPin) {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
    }
    void begin() {
        // Khởi tạo nếu cần
    }   

    // Bíp 1 lần
    void beep(unsigned long duration) {
        beep(duration, 1);
    }

    // Bíp nhiều lần
    void beep(unsigned long duration, int count) {
        beepDuration = duration;
        remainingBeeps = count;
        isOn = false;
        nextToggleTime = millis();
    }

    // Phải gọi trong loop() liên tục
    void update() {
        unsigned long now = millis();
        if (remainingBeeps == 0) {
            digitalWrite(pin, LOW);
            return;
        }

        if (now >= nextToggleTime) {
            if (isOn) {
                digitalWrite(pin, LOW);
                isOn = false;
                remainingBeeps--;
                nextToggleTime = now + pauseBetweenBeeps;
            } else {
                digitalWrite(pin, HIGH);
                isOn = true;
                nextToggleTime = now + beepDuration;
            }
        }
    }
};

#endif
