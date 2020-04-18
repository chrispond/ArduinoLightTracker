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
int oneMinute = 60000; // 60,000 milliseconds is 1 Minute
int hours = 22; // Start Time
int minutes = 30; // Start Time

void setup() {
  Serial.begin(9600);
  pinMode(photoResistor, INPUT);
  SD.begin(SdCsPin);
}

void loop() {  
  CaptureData(UpdatedTimeStamp(), analogRead(photoResistor));
  delay(oneMinute);
}

String UpdatedTimeStamp() {
  if(minutes >= 59){
    minutes = 0;
  }else{
    minutes = minutes + 1;
  }

  if(minutes == 0){
    hours = hours + 1;

    if(hours >= 24){
      hours = 0;
    }
  }
  
  char timeStamp[100];
  sprintf(timeStamp, "%02d:%02d", hours, minutes);
  return timeStamp;
}

void CaptureData(String timeStamp, int lightLevel) {
  dataFile = SD.open("SUNDATA.csv", FILE_WRITE);

  if(dataFile){
    dataFile.println();
    dataFile.print(timeStamp);
    dataFile.print(",");
    dataFile.print(lightLevel);
    dataFile.close();
  }
}
