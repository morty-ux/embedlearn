#include <Arduino.h>
#include <math.h>
//test git
// 呼吸灯（PWM 渐变），适用于 ESP8266 开发板
// 注意：大多数开发板的板载 LED 为低电平点亮（ACTIVE LOW），因此输出取反

const int ledPin = LED_BUILTIN;

const int pwmRange = 1023;
const unsigned long period = 3000UL; // 一个完整呼吸周期（毫秒）

void setup() {
  pinMode(ledPin, OUTPUT);
  analogWriteRange(pwmRange);
  analogWriteFreq(500);
  analogWrite(ledPin, pwmRange); // 初始为关闭（针对 ACTIVE LOW）
}

void loop() {
  unsigned long t = millis() % period;
  float phase = (float)t / (float)period; // 0..1
  float angle = phase * 2.0 * PI;
  float val = (sin(angle - PI/2.0) + 1.0) / 2.0; // 平滑 0..1
  int duty = (int)(val * pwmRange + 0.5);
  // 若板载 LED 为低电平点亮（如 NodeMCU），需要取反输出
  analogWrite(ledPin, pwmRange - duty);
  delay(20);
}