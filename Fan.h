#ifndef FAN_H
#define FAN_H

class Fan {
private:
    int pin;
public:
    Fan(int fanPin) : pin(fanPin) {}

    void begin() {
        pinMode(pin, OUTPUT);
        turnOff();
    }

    void turnOn() {
        digitalWrite(pin, HIGH);
    }

    void turnOff() {
        digitalWrite(pin, LOW);
    }
};
#endif
