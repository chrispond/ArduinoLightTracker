// MicroSD Dependancies
#include <SPI.h>
#include <SD.h>

// MicroSD Pins
// MOSI - pin 11
// MISO - pin 12
// CLK - pin 13
const int SdCsPin = 4;

// Photoresistor Pin
#define photoResistor A0

// Global Properties
File dataFile;
int analogValue = 0;
long oneMinute = 60000; // 60,000 milliseconds is 1 Minute
long oneHour = oneMinute * 60;

void setup() {
  Serial.begin(9600);
  pinMode(photoResistor, INPUT);
  SD.begin(SdCsPin);
}

void loop() {
  unsigned long currentTime = millis();
  analogValue = analogRead(photoResistor);
  CaptureData(currentTime, analogValue);
  delay(oneMinute);
}

void CaptureData(int currentTime, int lightLevel) {
  int hours = floor(currentTime/oneHour);
  int minutes = floor(currentTime/oneMinute) - (hours * oneHour);
  char timeStamp[10];
  sprintf(timeStamp, "%02d:%02d", hours, minutes);
  dataFile = SD.open("SUNDATA.csv", FILE_WRITE);

  if(dataFile){
    dataFile.println();
    dataFile.print(timeStamp);
    dataFile.print(",");
    dataFile.print(lightLevel);
    dataFile.close();
  }
}
