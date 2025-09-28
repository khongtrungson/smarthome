#ifndef SONGS_H
#define SONGS_H

struct Song {
    const int *notes;       // mảng nốt nhạc
    const int *durations;   // mảng thời lượng
    int length;             // số nốt
};

// Happy Birthday
const int happyBirthdayNotes[] = {
  262, 262, 294, 262, 349, 330,
  262, 262, 294, 262, 392, 349,
  262, 262, 523, 440, 349, 330, 294,
  466, 466, 440, 349, 392, 349
};

const int happyBirthdayDurations[] = {
  300, 300, 600, 600, 600, 1200,
  300, 300, 600, 600, 600, 1200,
  300, 300, 600, 600, 600, 600, 1200,
  300, 300, 600, 600, 600, 1200
};

const Song HappyBirthday = {
  happyBirthdayNotes,
  happyBirthdayDurations,
  sizeof(happyBirthdayNotes) / sizeof(int)
};

#endif