#include <Arduino.h>

#include "Buzzer.h"
#include "MyServo.h"
#include "LCDDisplay.h"
#include "MyLed.h"
#include "LightSensor.h"
#include "Guard.h"
#include "HumiditySensor.h"
#include "GasSensor.h"

#define DHTPIN 1 
// #define DHTTYPE DHT11
byte rowPins[4] = {9, 8, 7, 6};    // Chỉnh lại theo mạch của bạn
byte colPins[4] = {5, 4, 3, 2};    // Chỉnh lại theo mạch của bạn
#define GAS_PIN 10
#define BUZZER_PIN 11
#define SERVO_PIN 12
#define LED_FOR_LIGHT_PIN 13
#define LIGHT_SENSOR_PIN A0
#define HUMIDITY_SENSOR_PIN 14
#define LED_FOR_ALERT_PIN 15
Buzzer buzzer(BUZZER_PIN);
MyServo servo(SERVO_PIN);
LCDDisplay lcd(16, 2);
MyLed led1(LED_FOR_LIGHT_PIN);
MyLed led2(LED_FOR_ALERT_PIN);

HumiditySensor humiditySensor(HUMIDITY_SENSOR_PIN, &led2, &buzzer);
LightSensor lightSensor(LIGHT_SENSOR_PIN, &led1);
GasSensor gasSensor(GAS_PIN, &led2, &buzzer);
const char* PASSWORD = "1234";
Guard guard(PASSWORD, rowPins, colPins, &servo, &buzzer, &lcd);

void setup() {
  Serial.begin(9600);
  buzzer.begin();
  servo.begin();
  lcd.begin();
  led1.begin();
  led2.begin();
  humiditySensor.begin();
  lightSensor.begin();
  gasSensor.begin();
  guard.begin();

}

void loop() {
  buzzer.update();
  servo.update();
  led1.update();
  led2.update();
  humiditySensor.update();
  lightSensor.update();
  gasSensor.update();
  guard.update();
}
