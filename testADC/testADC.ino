int batteryCurrentPin = 6;
int batteryVoltagePin = 3;

void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  
  //set the resolution to 12 bits (0-4096)
  analogReadResolution(13);
}

void loop() {
  // read the analog / millivolts value for pin 2:
  int batteryCurrentValue = analogRead(batteryCurrentPin);
  int batteryCurrentMilliVoltage = analogReadMilliVolts(batteryCurrentPin);
  float batteryCurrentVoltage = batteryCurrentMilliVoltage / 1000.0;
  float batteryCurrent = (batteryCurrentVoltage - 1.43f) / 100.0f / 0.005f;
  
  // print out the values you read:
  Serial.printf("Battery value: %d, millivolts: %d, voltage: %f, current: %f\n",
    batteryCurrentValue, batteryCurrentMilliVoltage, batteryCurrentVoltage, batteryCurrent);
  
  delay(1000);  // delay in between reads for clear read from serial
}
