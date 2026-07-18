#include <Conceptinetics.h>
#include <Wire.h>
#include "Waveshare_LCD1602_RGB.h"

#define SLAVE_CHANNELS 512
#define RXEN_PIN 2

DMX_Slave dmx_slave (SLAVE_CHANNELS, RXEN_PIN);
Waveshare_LCD1602_RGB lcd(16, 2);

uint8_t lastRead[512];

void setup() {
  pinMode(13, OUTPUT);
  dmx_slave.enable();
  dmx_slave.setStartAddress(1);

  lcd.init();
  lcd.setCursor(0, 0);
  lcd.send_string("begin");

  for (uint8_t i : lastRead) {
    lastRead[i] = 0;
  }
}

void loop() {
  //noInterrupts();
  for (int i = 1; i <= SLAVE_CHANNELS; i++) {
    uint8_t v = dmx_slave.getChannelValue(i);

    uint8_t lv = lastRead[i - 1];
    if (v == lv) continue;

    lastRead[i - 1] = v;

    String s = String("Ch" + prependNullsToNum(i) + ": " + prependNullsToNum(v));
    write1(s.c_str());
  }
  //interrupts();
}

void write0(String str) {
  lcd.setCursor(0, 0);
  lcd.send_string(str.c_str());
}

void write1(String str) {
  lcd.setCursor(0, 1);
  lcd.send_string(str.c_str());
}

String prependNullsToNum(int val) {
  if (val > 99) return String(val);
  else if (val > 9) return "0" + String(val);
  else return "00" + String(val);
}