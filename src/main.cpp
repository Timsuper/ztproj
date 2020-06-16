#include <Arduino.h>
#include <avr/wdt.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <DHT.h>

// Temperatursensoren
#define DHT_1_DATA_PIN 3
#define DHT_2_DATA_PIN 4
#define DHT_TYPE DHT::DHT22

DHT dht_1;
DHT dht_2;

/* Hardware SPI beim Arduino (nur ein Gerät pro Arduino)
 UNO:  MOSI - pin 11, MISO - pin 12, CLK - pin 13, CS - pin 4 (CS pin can be changed)
  and pin #10 (SS) must be an output
 Mega:  MOSI - pin 51, MISO - pin 50, CLK - pin 52, CS - pin 4 (CS pin can be changed)
  and pin #52 (SS) must be an output
*/

// HW-SPI wird für SD-Karte verwendet
#define UNO_MOSI 11
#define UNO_MISO 12
#define UNO_CLK 13
#define UNO_SS 10

File dataFile;

unsigned long time;

const int messinterval = 10000;

/* To-Do:
- Analog Sensoren für Bodenfeuchte
- RTC einbauen?
*/

void setup() {
  Serial.begin(9600);

  // Register für WDT sicherheitshalber zurücksetzen
  MCUCR = 0;

  pinMode(UNO_SS, OUTPUT);

  if (!SD.begin(UNO_SS)) {
    Serial.println("SD Card failed, or not present");
    Serial.println("while(true)");
    while (1);
  }

  dataFile = SD.open("datalog.tsv", FILE_WRITE);
  if (! dataFile) {
    Serial.println("error opening datalog.txt");
    Serial.println("while(true)");
    while (1);
  }
  
  dht_1.setup(DHT_1_DATA_PIN, DHT_TYPE);
  dht_2.setup(DHT_2_DATA_PIN, DHT_TYPE);
}

void loop() {
  time = millis();
  String dataString;

  // Messung


  // Datenspeicherung auf der SD Karte
  dataFile.println(dataString);
  Serial.println(dataString);

  dataFile.flush();

  /* Arduino nach max. 50 Tagen Dauerberieb neustarten
  siehe millis() Maximalwerte
  Das ist notwenig, da delay() auf dem Zähler von millis() basiert! (Overflow nach 50 Tagen)
  */
  if (time >= 4294000000) {
    //wdt_enable(WDTO_1S);
    for (;;) {

    }
  }

  // Messintervall
  delay(messinterval);
}