#include <Arduino.h>
#include <avr/wdt.h>
#include <EEPROM.h>
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

// SD-Karte
#define UNO_HW_MOSI 11
#define UNO_HW_MISO 12
#define UNO_HW_CLK 13
#define UNO_HW_SS 10

File dataFile;

// Bodenfeuchtesensoren

#define BFS_1 A1
#define BFS_2 A2

#define BFS_1_BOTTOM_EEPROM_ADDR 0
#define BFS_2_BOTTOM_EEPROM_ADDR 1
#define BFS_1_TOP_EEPROM_ADRR 2
#define BFS_2_TOP_EEPROM_ADRR 3

// RTC

unsigned long time;

const int messinterval = 10000;

uint8_t bfs_1_bottom_value;
uint8_t bfs_2_bottom_value;
uint8_t bfs_1_top_value;
uint8_t bfs_2_top_value;

/* To-Do:
- Analog Sensoren für Bodenfeuchte
- RTC einbauen?
*/

void setup() {
  Serial.begin(9600);

  // WDT
  // Register für WDT sicherheitshalber zurücksetzen
  MCUCR = 0;

  // SD Karte
  pinMode(UNO_HW_SS, OUTPUT);

  if (!SD.begin(UNO_HW_SS)) {
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
  
  // DHT
  dht_1.setup(DHT_1_DATA_PIN, DHT_TYPE);
  dht_2.setup(DHT_2_DATA_PIN, DHT_TYPE);

  // RTC

  // BFS
  pinMode(BFS_1, INPUT);
  pinMode(BFS_2, INPUT);

  wdt_enable(WDTO_500MS);

  bfs_1_bottom_value = EEPROM.read(BFS_1_BOTTOM_EEPROM_ADDR);
  bfs_2_bottom_value = EEPROM.read(BFS_2_BOTTOM_EEPROM_ADDR);
  bfs_1_top_value = EEPROM.read(BFS_1_TOP_EEPROM_ADRR);
  bfs_2_top_value = EEPROM.read(BFS_2_TOP_EEPROM_ADRR);

  wdt_reset();
  wdt_disable();
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

bool bfs_calibrate() {
  uint8_t bfs_1_bottom;
  uint8_t bfs_2_bottom;
  uint8_t bfs_1_top;
  uint8_t bfs_2_top;

  Serial.println("Kablibrierung der Bodenfeuchtesensoren");
  Serial.println("Reihenfolge:");
  Serial.println("1. Sensor 1 (trocken an der Luft");
  Serial.println("2. Sensor 2 (trocken an der Luft");
  Serial.println("3. Sensor 1 (in feuchte Erde stecken)");
  Serial.println("4. Sensor 2 (in feuchte Erde stecken)");
  Serial.println();
  Serial.println("Die Werte werden im EEPROM automatisch gespeichert!");

  Serial.println();
  Serial.print("warte: ");

  for (size_t i = 5; i < 0; i--)
  {
    Serial.print(i + "  ");
    delay(1000);
  }

  Serial.println();

  /// BFS Sensor 1 trocken ermitteln
  Serial.println("Sensor 1 trocken:");
  Serial.println();
  Serial.print("warte: ");
  
  for (size_t i = 5; i < 0; i--)
  {
    Serial.print(i + "  ");
    delay(1000);
  }

  // Messung
  bfs_1_bottom = analogRead(BFS_1);
  
  Serial.println();
  /// Ende

  /// BFS Sensor 2 trocken ermitteln
  Serial.println("Sensor 2 trocken:");
  Serial.println();
  Serial.print("warte: ");

  for (size_t i = 5; i < 0; i--)
  {
    Serial.print(i + "  ");
    delay(1000);
  }

  // Messung
  bfs_2_bottom = analogRead(BFS_2);

  Serial.println();
  /// Ende

  /// BFS Sensor 1 feucht ermitteln
  Serial.println("Sensor 1 feucht:");
  Serial.println();
  Serial.print("warte: ");

  for (size_t i = 5; i < 0; i--)
  {
    Serial.print(i + "  ");
    delay(1000);
  }

  // Messung
  bfs_1_top = analogRead(BFS_1);

  Serial.println();
  /// Ende

  // BFS Sensor 2 feucht ermitteln
  Serial.println("Sensor 2 feucht:");
  Serial.println();
  Serial.print("warte: ");

  for (size_t i = 5; i < 0; i--)
  {
    Serial.print(i + "  ");
    delay(1000);
  }

  // Messung
  bfs_2_top = analogRead(BFS_2);

  Serial.println();

  ///Ende

  Serial.println("Alle Werte wurden ermittelt!");
  Serial.println("Werte werden in EEPROM übernommen");

  wdt_enable(WDTO_500MS);
  
  EEPROM.update(BFS_1_BOTTOM_EEPROM_ADDR, bfs_1_bottom);
  EEPROM.update(BFS_2_BOTTOM_EEPROM_ADDR, bfs_2_bottom);
  EEPROM.update(BFS_1_TOP_EEPROM_ADRR, bfs_1_top);
  EEPROM.update(BFS_2_TOP_EEPROM_ADRR, bfs_2_top);

  wdt_reset();
  wdt_disable();

  return true;
}