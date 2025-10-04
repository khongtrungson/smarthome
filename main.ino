#include <Arduino.h>

#include "Buzzer.h"
#include "MyServo.h"
#include "LCDDisplay.h"
#include "MyLed.h"
#include "NeoPixelRing.h"
#include "LightSensor.h"
#include "Guard.h"
#include "VibrationSensor.h"
#include "IR1838T.h"
// #include "HumiditySensor.h"
// #include "GasSensor.h"



// #define DHTTYPE DHT11
byte rowPins[4] = {9, 8, 7, 6};    // Chỉnh lại theo mạch của bạn
byte colPins[4] = {5, 4, 3, 2};    // Chỉnh lại theo mạch của bạn
#define LED_RING_PIN 10
#define BUZZER_PIN 11
#define SERVO_PIN 12
#define LED_PIN 13

#define LIGHT_SENSOR_PIN A1
#define VIBRATION_SENSOR_PIN A2
#define IR1838T_PIN A3

Buzzer buzzer(BUZZER_PIN);
MyServo servo(SERVO_PIN);
LCDDisplay lcd(0x27, 16, 2);
MyLed led(LED_PIN);
NeoPixelRing ring(LED_RING_PIN);


LightSensor lightSensor(LIGHT_SENSOR_PIN, &led, &ring, &lcd);
VibrationSensor vibrationSensor(VIBRATION_SENSOR_PIN, &ring, &lcd, &buzzer, &led, 3, 300);
const char* PASSWORD = "1234";
Guard guard(PASSWORD, rowPins, colPins, &servo, &buzzer, &lcd, &ring);
IR1838T irReceiver(IR1838T_PIN, &servo, &ring);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  buzzer.begin();
  servo.begin();
  lcd.begin();
  lightSensor.begin();
  ring.begin();
  led.begin();
  guard.begin();
  vibrationSensor.begin();
  irReceiver.begin();
}

void loop() {
  guard.update();
  lightSensor.update();
  vibrationSensor.update();
  irReceiver.update();
  led.update();
  ring.update();
  servo.update();
  buzzer.update();
  // humiditySensor.update();
  // gasSensor.update();
}