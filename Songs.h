#ifndef SONGS_H
#define SONGS_H

// Định nghĩa các nốt nhạc (tần số Hz)
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_REST 0

// Struct lưu bài hát
struct Song {
    const int *notes;       // mảng nốt nhạc
    const int *durations;   // mảng thời lượng
    int length;             // số nốt
};

// ===== BÀI HÁT 1: Piano Nhẹ Nhàng (Canon in D - đoạn đơn giản) =====
const int piano_notes[] = {
    NOTE_D4, NOTE_A4, NOTE_B4, NOTE_FS4, NOTE_G4, NOTE_D4, NOTE_G4, NOTE_A4,
    NOTE_D4, NOTE_A4, NOTE_B4, NOTE_FS4, NOTE_G4, NOTE_D4, NOTE_G4, NOTE_A4,
    NOTE_D5, NOTE_CS5, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_D4,
    NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_FS4, NOTE_D4, NOTE_E4, NOTE_FS4, NOTE_G4
};

const int piano_durations[] = {
    500, 500, 500, 500, 500, 500, 500, 500,
    500, 500, 500, 500, 500, 500, 500, 500,
    400, 400, 400, 400, 400, 400, 400, 400,
    400, 400, 400, 400, 400, 400, 400, 600
};

Song gentlePiano = {
    piano_notes,
    piano_durations,
    32  // số nốt
};

// ===== BÀI HÁT 2: Jingle Bells (đầy đủ hơn) =====
const int jingle_notes[] = {
    NOTE_E4, NOTE_E4, NOTE_E4, NOTE_REST,
    NOTE_E4, NOTE_E4, NOTE_E4, NOTE_REST,
    NOTE_E4, NOTE_G4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_REST,
    NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_E4,
    NOTE_E4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_REST, NOTE_G4
};

const int jingle_durations[] = {
    250, 250, 500, 100,
    250, 250, 500, 100,
    250, 250, 250, 250, 800, 200,
    250, 250, 250, 250, 250, 250, 250, 200,
    250, 250, 250, 250, 500, 200, 500
};

Song jingleBells = {
    jingle_notes,
    jingle_durations,
    29  // số nốt
};

// ===== BÀI HÁT 3: Welcome Chime (chào mừng vui tươi) =====
const int welcome_notes[] = {
    NOTE_C5, NOTE_E5, NOTE_G5, NOTE_C5, 
    NOTE_E5, NOTE_G5, NOTE_E5, NOTE_C5,
    NOTE_D5, NOTE_F5, NOTE_A5, NOTE_F5,
    NOTE_E5, NOTE_G5, NOTE_C5, NOTE_REST
};

const int welcome_durations[] = {
    200, 200, 300, 200,
    200, 300, 200, 300,
    200, 200, 300, 200,
    200, 300, 500, 200
};

Song welcomeChime = {
    welcome_notes,
    welcome_durations,
    16  // số nốt
};

#endif