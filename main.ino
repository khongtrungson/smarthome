#include <Arduino.h>

#include "Buzzer.h"
#include "MyServo.h"
#include "LCDDisplay.h"
#include "MyLed.h"
#include "NeoPixelRing.h"
#include "Fan.h"
#include "LightSensor.h"
#include "Guard.h"
#include "VibrationSensor.h"
#include "IR1838T.h"
#include "TemperatureSensor.h"
#include "GasSensor.h"
#include "RainSensor.h"




#define LED_RING_PIN 10
#define BUZZER_PIN 11
#define SERVO_PIN 12
#define LED_PIN 13
#define TemperatureSensor_PIN A0
#define LIGHT_SENSOR_PIN A1
#define VIBRATION_SENSOR_PIN A2
#define IR_PIN A3
#define GAS_PIN A4
#define RAIN_SENSOR_PIN A5
#define RAIN_SERVO_PIN 0
#define FAN_PIN 1
byte rowPins[4] = {2, 3, 4, 5};    // Chỉnh lại theo mạch của bạn
byte colPins[4] = {6, 7, 8, 9};    // Chỉnh lại theo mạch của bạn
Buzzer buzzer(BUZZER_PIN);
MyServo servo(SERVO_PIN);
LCDDisplay lcd(0x27, 16, 2);
MyLed led(LED_PIN);
NeoPixelRing ring(LED_RING_PIN);
Fan fan(FAN_PIN);
MyServo rainServo(RAIN_SERVO_PIN);

LightSensor lightSensor(LIGHT_SENSOR_PIN, &led, &ring, &lcd, &rainServo);
VibrationSensor vibrationSensor(VIBRATION_SENSOR_PIN, &ring, &lcd, &buzzer, &led);
const char* PASSWORD = "1234";
Guard guard(PASSWORD, rowPins, colPins, &servo, &buzzer, &lcd, &ring, &rainServo);
IR1838T irReceiver(IR_PIN, &servo, &ring, &buzzer, &led);
TemperatureSensor temperatureSensor(TemperatureSensor_PIN, &lcd);
RainSensor rainSensor(RAIN_SENSOR_PIN, &rainServo);
GasSensor gasSensor(GAS_PIN, &led, &buzzer, &ring, &fan);

void setup() {
  Wire.begin();
  temperatureSensor.begin();
  buzzer.begin();
  servo.begin();
  servo.setWaitEnabled(true);
  rainServo.begin();
  rainServo.setWaitEnabled(false);
  rainSensor.begin();
  gasSensor.begin();
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
  temperatureSensor.update();
  led.update();
  ring.update();
  servo.update();
  buzzer.update();
  lcd.update();
  gasSensor.update();
  rainSensor.update();
}