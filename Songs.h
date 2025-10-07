#ifndef SONGS_H
#define SONGS_H

// Định nghĩa các nốt nhạc (tần số Hz)
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_REST 0

// Struct lưu bài hát
struct Song {
    const int *notes;       // mảng nốt nhạc
    const int *durations;   // mảng thời lượng
    int length;             // số nốt
};

// ===== BÀI HÁT 1: Jingle Bells (đơn giản) =====
const int jingle_notes[] = {
    NOTE_E4, NOTE_E4, NOTE_E4, NOTE_REST,
    NOTE_E4, NOTE_E4, NOTE_E4, NOTE_REST,
    NOTE_E4, NOTE_G4, NOTE_C4, NOTE_D4, NOTE_E4
};

const int jingle_durations[] = {
    250, 250, 500, 100,
    250, 250, 500, 100,
    250, 250, 250, 250, 1000
};

Song jingleBells = {
    jingle_notes,
    jingle_durations,
    13  // số nốt
};

// ===== BÀI HÁT 2: Happy Birthday =====
const int birthday_notes[] = {
    NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_F4, NOTE_E4, NOTE_REST,
    NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_G4, NOTE_F4, NOTE_REST,
    NOTE_C4, NOTE_C4, NOTE_C5, NOTE_A4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_REST,
    NOTE_B4, NOTE_B4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_F4
};

const int birthday_durations[] = {
    200, 200, 400, 400, 400, 800, 200,
    200, 200, 400, 400, 400, 800, 200,
    200, 200, 400, 400, 400, 400, 400, 200,
    200, 200, 400, 400, 400, 800
};

Song happyBirthday = {
    birthday_notes,
    birthday_durations,
    28  // số nốt
};

// ===== BÀI HÁT 3: Twinkle Twinkle =====
const int twinkle_notes[] = {
    NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_REST,
    NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4
};

const int twinkle_durations[] = {
    400, 400, 400, 400, 400, 400, 800, 200,
    400, 400, 400, 400, 400, 400, 800
};

Song twinkleTwinkle = {
    twinkle_notes,
    twinkle_durations,
    15
};

// ===== BÀI HÁT 4: Welcome Chime (tự sáng tác) =====
const int welcome_notes[] = {
    NOTE_C5, NOTE_E5, NOTE_G4, NOTE_C5, NOTE_E5
};

const int welcome_durations[] = {
    200, 200, 300, 200, 500
};

Song welcomeChime = {
    welcome_notes,
    welcome_durations,
    5
};

#endif