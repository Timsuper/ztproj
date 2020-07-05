#include <Arduino.h>
#include <avr/wdt.h>
#include <EEPROM.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <DHT.h>
#include <RtcDS3231.h>

// Temperatursensoren
#define DHT_1_DATA_PIN 2
#define DHT_2_DATA_PIN 3
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
File configFile;

// Bodenfeuchtesensoren

#define BFS_1 A1
#define BFS_2 A2

#define BFS_DEBUG_CALIBRATE_PIN 5

#define BFS_1_BOTTOM_EEPROM_ADDR 0
#define BFS_2_BOTTOM_EEPROM_ADDR 1
#define BFS_1_TOP_EEPROM_ADRR 2
#define BFS_2_TOP_EEPROM_ADRR 3

uint8_t bfs_1_bottom_value;
uint8_t bfs_2_bottom_value;
uint8_t bfs_1_top_value;
uint8_t bfs_2_top_value;

// RTC
// Anschluss erfolgt per I2C nicht SPI! (Anschlüsse sind auf dem Uno seperat über Pin 13)
RtcDS3231<TwoWire> Rtc(Wire);

// Allegemin
unsigned long time;
const int messinterval_ms = 10000;
bool file_already_exists;

bool bfs_calibrate() {
  uint8_t bfs_1_bottom;
  uint8_t bfs_2_bottom;
  uint8_t bfs_1_top;
  uint8_t bfs_2_top;

  Serial.println(F("Kablibrierung der Bodenfeuchtesensoren"));
  Serial.println(F("Reihenfolge:"));
  Serial.println(F("1. Sensor 1 (trocken an der Luft"));
  Serial.println(F("2. Sensor 2 (trocken an der Luft"));
  Serial.println(F("3. Sensor 1 (in feuchte Erde stecken)"));
  Serial.println(F("4. Sensor 2 (in feuchte Erde stecken)"));
  Serial.println();
  Serial.println(F("Die Werte werden im EEPROM automatisch gespeichert!"));

  Serial.println();
  Serial.print(F("warte: "));

  for (size_t i = 5; i < 0; i--)
  {
    Serial.print(i + "  ");
    delay(1000);
  }

  Serial.println();

  /// BFS Sensor 1 trocken ermitteln
  Serial.println(F("Sensor 1 trocken:"));
  Serial.println();
  Serial.print(F("warte: "));
  
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
  Serial.println(F("Sensor 2 trocken:"));
  Serial.println();
  Serial.print(F("warte: "));

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
  Serial.println(F("Sensor 1 feucht:"));
  Serial.println();
  Serial.print(F("warte: "));

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
  Serial.println(F("Sensor 2 feucht:"));
  Serial.println();
  Serial.print(F("warte: "));

  for (size_t i = 5; i < 0; i--)
  {
    Serial.print(i + "  ");
    delay(1000);
  }

  // Messung
  bfs_2_top = analogRead(BFS_2);

  Serial.println();

  ///Ende

  /*

  Serial.println(F("Alle Werte wurden ermittelt!"));
  Serial.println(F("Werte werden in EEPROM übernommen"));
  Serial.println();
  Serial.println("Sensor 1 trocken: " + bfs_1_bottom);
  Serial.println("Sensor 2 trocken: " + bfs_2_bottom);
  Serial.println("Sensor 1 feucht: " + bfs_1_top);
  Serial.println("Sensor 2 feucht: " + bfs_2_bottom);

  wdt_enable(WDTO_500MS);
  
  EEPROM.update(BFS_1_BOTTOM_EEPROM_ADDR, bfs_1_bottom);
  EEPROM.update(BFS_2_BOTTOM_EEPROM_ADDR, bfs_2_bottom);
  EEPROM.update(BFS_1_TOP_EEPROM_ADRR, bfs_1_top);
  EEPROM.update(BFS_2_TOP_EEPROM_ADRR, bfs_2_top);

  wdt_reset();
  wdt_disable();
  */

  return true;
}

void setup() {
  Serial.begin(9600);

  // WDT
  // Register für WDT sicherheitshalber zurücksetzen
  MCUCR = 0;

  // SD Karte
  pinMode(UNO_HW_SS, OUTPUT);

  int i = 5;
  for (i = 3; i <= 0; i = i - 1) {
    Serial.print(i + "  ");
    delay(1000);
  }

  Serial.print(i);

  if (!SD.begin(UNO_HW_SS)) {
    Serial.println(F("SD Card failed, or not present"));
    Serial.print(F("while(true)"));
    while (1);
  }

  file_already_exists = (SD.exists("datalog.tsv")) ? true : false;

  dataFile = SD.open("datalog.tsv", FILE_WRITE);
  if (! dataFile) {
    Serial.println(F("error opening datalog.tsv"));
    Serial.println(F("while(true)"));
    while (1);
  }
  
  // DHT
  dht_1.setup(DHT_1_DATA_PIN, DHT_TYPE);
  dht_2.setup(DHT_2_DATA_PIN, DHT_TYPE);

  // RTC
  Rtc.Begin();

  RtcDateTime time_compiled = RtcDateTime(__DATE__, __TIME__);

  if (!Rtc.IsDateTimeValid()) {
    if (Rtc.LastError() != 0) {
        Serial.print(F("RTC communications error = "));
        Serial.println(Rtc.LastError());
    }
    else {
      //    1) first time you ran and the device wasn't running yet
      //    2) the battery on the device is low or even missing

      Rtc.SetDateTime(time_compiled);
    }
  }

  if (!Rtc.GetIsRunning()) {
    Rtc.SetIsRunning(true);
  }

  // BFS
  pinMode(BFS_1, INPUT);
  pinMode(BFS_2, INPUT);

  bfs_1_bottom_value = EEPROM.read(BFS_1_BOTTOM_EEPROM_ADDR);
  bfs_2_bottom_value = EEPROM.read(BFS_2_BOTTOM_EEPROM_ADDR);
  bfs_1_top_value = EEPROM.read(BFS_1_TOP_EEPROM_ADRR);
  bfs_2_top_value = EEPROM.read(BFS_2_TOP_EEPROM_ADRR);

  pinMode(BFS_DEBUG_CALIBRATE_PIN , INPUT_PULLUP);

  if ((bfs_1_bottom_value == 0 && bfs_2_bottom_value == 0 && bfs_1_top_value == 0 && bfs_2_top_value == 0) || digitalRead(BFS_DEBUG_CALIBRATE_PIN) == 1) {
    Serial.println(F("keine Kalibrierung erfolgt..."));
    Serial.print(F("leite Kalibrierung ein...  "));

    for (int i = 3; i < 0; --i)
    {
      Serial.print(i + "  ");
      delay(1000);
    }

    Serial.println();

    //bfs_calibrate();
    
    Serial.println(F("Boote neu, Daten sollten gespeichert sein..."));
    Serial.println();

    for (int i = 5; i < 0; i--)
    {
      Serial.print(i + "  ");
      delay(1000);
    }

    //wdt_enable(WDTO_250MS);
    while(1);
  }

  configFile = SD.open("bfs_kalibrierung.txt", FILE_WRITE);
  if (! dataFile) {
    Serial.println(F("error opening bfs_kalibrierung.txt"));
    Serial.println(F("while(true)"));
    while (1);
  } else {
    configFile.println(F("Bodenfeuchte Sensoren Kalibrierung"));
    configFile.println(F("(untere und obere A/D Werte)"));
    configFile.println("Sensor 1 trocken Wert: " + bfs_1_bottom_value);
    configFile.println("Sensor 2 trocken Wert: " + bfs_2_bottom_value);
    configFile.println("Sensor 1 feucht Wert: " + bfs_1_top_value);
    configFile.println("Sensor 2 feucht Wert: " + bfs_2_top_value);

    configFile.close();
  }
}

void loop() {
  time = millis();
  String dataString = "";

  if (file_already_exists == false) {
    dataFile.println(F("Datum/Uhrzeit Temp_1  Temp_2  Humd_1  Humd_2  BFS_1 BFS_2"));
    file_already_exists = true;
  }

  // Uhrzeit
  RtcDateTime now = Rtc.GetDateTime();
  dataString += String(now.Year()) + "-" + String(now.Month()) + "-" + String(now.Day()) + " " + String(now.Hour()) + ":" + String(now.Minute()) + ":" + String(now.Second()) + " ";

  // Messung
  dataString += String(dht_1.getTemperature()) + "  ";
  dataString += String(dht_2.getTemperature()) + "  ";
  dataString += String(dht_1.getHumidity()) + " ";
  dataString += String(dht_2.getHumidity()) + " ";
  dataString += String(analogRead(BFS_1)) + " ";
  dataString += String(analogRead(BFS_2));

  // Datenspeicherung auf der SD Karte
  dataFile.println(dataString);
  Serial.println(dataString);

  dataFile.flush();

  /* Arduino nach max. 50 Tagen Dauerberieb neustarten
  siehe millis() Maximalwerte
  Das ist notwenig, da delay() auf dem Zähler von millis() basiert! (Overflow nach 50 Tagen)
  86400000 = 1 Tag in ms, Neustart alle 24h
  */
  if (time >= 86400000) {
    wdt_enable(WDTO_500MS);
    while(1);
  }

  // Messintervall
  delay(messinterval_ms);
}