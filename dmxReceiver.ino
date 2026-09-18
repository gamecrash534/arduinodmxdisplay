#include "Conceptinetics.h"
#include <Wire.h>
#include "Waveshare_LCD1602_RGB.h"

#define SLAVE_CHANNELS 512
#define RXEN_PIN 2

DMX_Slave dmx_slave(SLAVE_CHANNELS, RXEN_PIN);
Waveshare_LCD1602_RGB lcd(16, 2);

uint8_t lastRead[SLAVE_CHANNELS];

void setup() {
    dmx_slave.enable();
    dmx_slave.setStartAddress(1);

    lcd.init();
    lcd.setCursor(0, 0);
    lcd.send_string("Ch000: 000");
}

void loop() {
    for (uint16_t ch = 1; ch <= SLAVE_CHANNELS; ch++) {
        uint8_t val = dmx_slave.getChannelValue(ch);

        if (val == lastRead[ch - 1]) continue;

        lastRead[ch - 1] = val;

        char buf[11];
        snprintf(buf, sizeof(buf), "Ch%03u: %03u", ch, val);

        write0(buf);
    }
}

void write0(String str) {
    lcd.setCursor(0, 0);
    lcd.send_string(str.c_str());
}

void write1(String str) {
    lcd.setCursor(0, 1);
    lcd.send_string(str.c_str());
}