#include <can.h>
#include <mcp2515.h>

#include <CanHacker.h>
#include <CanHackerLineReader.h>
#include <lib.h>

#include <SPI.h>

const int SPI_CS_PIN = 10;
const int INT_PIN = 3;


CanHackerLineReader *lineReader = NULL;
CanHacker *canHacker = NULL;

void setup() {
    Serial.begin(115200);
    SPI.begin();
    
    canHacker = new CanHacker(&Serial, NULL, SPI_CS_PIN);
    canHacker->enableLoopback();            // Enable Loopback mode for offline tests
    lineReader = new CanHackerLineReader(canHacker);
    
    pinMode(INT_PIN, INPUT);
}

void loop() {
    if (digitalRead(INT_PIN) == LOW) {
        canHacker->processInterrupt();
    }
    if (Serial.available()) {
        lineReader->process();
    }
}

