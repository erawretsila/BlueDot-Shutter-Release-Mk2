#include "BlueDot.h"
#include "BluetoothSerial.h"

//BluetoothSerial ESP_32;
BlueDot shutter(5);

void setup() {
}

void loop() {
  // put your main code here, to run repeatedly:
  shutter.dot();
}
