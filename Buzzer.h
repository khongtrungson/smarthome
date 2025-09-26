#ifndef BUZZER_H
#define BUZZER_H

class Buzzer {
    private:
        int pin;

        // Alert pattern
        int alertCount = 0;
        unsigned long alertOnDuration = 0;
        unsigned long alertOffDuration = 0;
        unsigned long nextChange = 0;
        bool alertOn = false;

        // Melody
        const int *melody = nullptr;
        const int *noteDuration = nullptr;
        int melodyLength = 0;
        int melodyIndex = 0;
        unsigned long melodyNextChange = 0;
        bool playingMelody = false;

    public:
        Buzzer(int buzzerPin) : pin(buzzerPin) {}

        void begin() {
            pinMode(pin, OUTPUT);
            off();
        }

        void on(unsigned int freq = 1000) {
            tone(pin, freq);  // bật vô hạn với tần số mặc định 1kHz
        }

        void off() {
            noTone(pin);
        }

        // beep đơn: tần số + thời gian
        void beep(unsigned int freq = 1000, unsigned long duration = 200) {
            tone(pin, freq, duration);
        }

        // tone với thời gian (Arduino tự quản lý tắt)
        void tonePlay(unsigned int frequency, unsigned long duration = 0) {
            if (duration > 0) {
                tone(pin, frequency, duration);
            } else {
                tone(pin, frequency);
            }
        }

        void stopTone() {
            noTone(pin);
        }

        // Alert: lặp pattern beep on/off
        void alert(int times = 3, unsigned long onDuration = 200, unsigned long offDuration = 200, unsigned int freq = 1000) {
            alertCount = times * 2 - 1;   // số lần bật/tắt
            alertOnDuration = onDuration;
            alertOffDuration = offDuration;
            alertOn = true;
            tone(pin, freq, onDuration);
            nextChange = millis() + onDuration;
        }

        // Melody: nhiều nốt nhạc
        void playMelody(const int *notes, const int *durations, int length) {
            melody = notes;
            noteDuration = durations;
            melodyLength = length;
            melodyIndex = 0;
            playingMelody = true;
            if (melodyLength > 0) {
                tone(pin, melody[0], noteDuration[0]);
                melodyNextChange = millis() + noteDuration[0] + 50; // nghỉ 50ms
            }
        }

        bool isPlayingMelody() const {
            return playingMelody;
        }

        // Cập nhật cho alert và melody
        void update() {
            unsigned long now = millis();

            // Alert
            if (alertCount > 0 && now >= nextChange) {
                if (alertOn) {
                    off();
                    nextChange = now + alertOffDuration;
                } else {
                    tone(pin, 1000, alertOnDuration); // beep tiếp
                    nextChange = now + alertOnDuration;
                }
                alertOn = !alertOn;
                alertCount--;
            }

            // Melody
            if (playingMelody && now >= melodyNextChange) {
                melodyIndex++;
                if (melodyIndex < melodyLength) {
                    tone(pin, melody[melodyIndex], noteDuration[melodyIndex]);
                    melodyNextChange = now + noteDuration[melodyIndex] + 50;
                } else {
                    stopTone();
                    playingMelody = false;
                }
            }
        }
};

#endif
