#include "I2CIO.h"
#include "ScreenBuffer.h"
#include "SSD1306.h"
#include "GraphicsPrint.h"

using namespace g3rb3n;

I2CIO io(0x3C);
SSD1306 ssd(&io);
ScreenBuffer screenBuffer(128, 64, 1);
GraphicsPrint gfx(&screenBuffer);

long start;
long now;
long count;
int value = 0;

void setup()
{
  setupSerial();
  setupSSD();
  status();
}

void setupSSD()
{
  screenBuffer.begin();
  ssd.begin();

  gfx.begin();
  gfx.clear();
  ssd.display(screenBuffer);
}

void setupSerial()
{
  Serial.begin(230400);
  Serial.println();
}

void status()
{
  String value;
  value += "WiFi: woonkamer\n";
  value += "MQTT: 10.0.0.66\n";
  value += "IP  : 10.0.0.201\n";
  value += "Sampling @ 988 Hz\n";
  value += "Sending  @ 0.95 Hz\n";
  value += "Running      \n";
  #ifdef DEBUG
  Serial.println(value);
  #endif
  gfx.clear();
  gfx.setCursor(0,0);
  gfx.print(value);
  ssd.display(screenBuffer);
  setRunningValue(0.95);
  delay(1000);
  start = millis();
}

void loop()
{
  ++value;
  ++count;
  Serial.println(value);
  setRunningValue(static_cast<float>(value) / 100);
  setDisplayHzValue();
  //ssd.display(screenBuffer, 11*8, 48, 18*8, 48 + 7);
  ssd.display(screenBuffer, 11*8, 40, 18*8, 40 + 15);
  //ssd.display(screenBuffer, 2, 48, 18*8, 48 + 7);
  now = millis();
}

void setRunningValue(float value)
{
  gfx.setCursor(5, 11);
  gfx.print(value);
}

void setDisplayHzValue()
{
  float rate = count;
  #ifdef DEBUG
  Serial.println(rate, 10);
  #endif
  rate /= (now - start);
  #ifdef DEBUG
  Serial.println(rate, 10);
  #endif
  rate *= 1000;
  #ifdef DEBUG
  Serial.println(rate, 10);
  #endif
  gfx.setCursor(6, 11);
  gfx.print(rate, 4);
}