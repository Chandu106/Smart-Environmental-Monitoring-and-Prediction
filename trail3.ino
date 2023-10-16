#include <SPI.h>
#include <SD.h>
#include "DHT.h"
#define DHTTYPE DHT11
uint8_t DHTPin = 6;
DHT dht(DHTPin, DHTTYPE);
float Temperature;
float Humidity;
int Rain_Detector = analogRead(A3);
int Soil_Moisture = analogRead(A4);
int PhotoDiode = analogRead(A5);
const int chipSelect = 10;


void setup()
{
  Serial.begin(9600);
  pinMode(DHTPin, INPUT);
  dht.begin();
  Initialize_SDcard();
}

void loop()
{
  Write_SDcard();
  Read_TempHum();
  Read_RainDetector();
  Read_SoilMoisture();
  Read_PhotoDiode();
  delay(60000);
}

void Read_TempHum()
{
  Temperature = dht.readTemperature();
  Humidity = dht.readHumidity();
  Serial.print("Temperature = ");
  Serial.println(Temperature);
  Serial.print("Humidity = ");
  Serial.println(Humidity);
}

void Read_RainDetector()
{
  Rain_Detector = analogRead(A3);
  Serial.print("Rain Detector Value: ");
  Serial.println(Rain_Detector);
}

void Read_SoilMoisture()
{
  Soil_Moisture = analogRead(A4);
  Serial.print("Soil Moisture Value: ");
  Serial.println(Soil_Moisture);
}

void Read_PhotoDiode()
{
  PhotoDiode = analogRead(A5);
  Serial.print("Photon Intensity : ");
  Serial.println(PhotoDiode);
}

void Initialize_SDcard()
{
  if (!SD.begin(chipSelect))
  {
    Serial.println("CARD FAILED");
    return;
  }

  File dataFile = SD.open("data.txt", FILE_WRITE);
  if (dataFile)
  {
    dataFile.println("Temperature,Humidity,RainDetector,SoilMoisture,PhotoDiode");
    dataFile.close();
  }
}

void Write_SDcard()
{
  File dataFile = SD.open("data.txt", FILE_WRITE);

  if (dataFile)
  {
    dataFile.print(Temperature);
    dataFile.print(",");
    dataFile.print(Humidity);
    dataFile.print(",");
    dataFile.print(Rain_Detector);
    dataFile.print(",");
    dataFile.print(Soil_Moisture);
    dataFile.print(",");
    dataFile.print(PhotoDiode);
    dataFile.print(",");
    dataFile.println();
    dataFile.close();
  }

  else
  {
    Serial.println("SD card writing failed");
  }
}
