#include "dGPS.h"
#include "SPI.h"
#include "SD.h"
#include "string.h"


dGPS dgps = dGPS();

File dataFile;

void setup() {
  Serial.end();
  Serial.begin(9600);
  Serial.println("GPS init");
  dgps.init();
  Serial.println("GPS initialized");

  Serial.println("SD init");
  if (!SD.begin(10, 11, 12, 13))
  {
    Serial.println("Failed SD initialization");
    while (1);
  }
  Serial.println("SD initialized");

  dataFile = SD.open("logs.txt", FILE_WRITE);
  if (!dataFile)
  {
    Serial.println("Error opening logs.txt");
    while (1);
  }

}

void loop()
{
  String logLine = "Date: ";
  dgps.update(0, 0);
  logLine += String(dgps.Date()) + " | Time (UTC): ";
  logLine += String(dgps.Time()) + " | Lat: ";
  logLine += String(dgps.Lat(),6) + " | Lon: ";
  logLine += String(dgps.Lon(),6) + " | Speed: ";
  logLine += String(dgps.Vel() * 1.15078) + " mph";

  dataFile.println(logLine);
  Serial.println(logLine);

  dataFile.flush();

  delay(1000);

}
