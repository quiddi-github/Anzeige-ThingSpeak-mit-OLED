

// Anfang: Bibs udn Konfig für W-Lan ESP8266
#include <ESP8266WebServer.h> // <WebServer.h> for ESP32
#define PORT 80
const char* ssid = "Hier W-Lan SSOD Eintragen";;" ;
const char* pass = "Hier W-Lan Passwort eintragen";;" ;
ESP8266WebServer server(PORT); // WebServer server(PORT); for ESP32
// Ende: Bibs udn Konfig für W-Lan ESP8266

//Anfang: Bibs und Konfig für O-LED 

#define SDA_PIN 12 //GPIO12 / 6
#define SCL_PIN 14 //GPIO14 / 5
#include <Wire.h>                                   // library for I2C comunication
#include "SSD1306Wire.h"                      // library for display
SSD1306Wire display(0x3c,  SDA_PIN, SCL_PIN);   // I2C address of display

//Ende: Bibs und Konfig für O-LED

#include <ThingSpeak.h>  // ThinkSpeak Bib zum lesen der Temperatur
unsigned long myChannelNumber = Hier ThingSpeak Channel Nr eintragen;         
WiFiClient  client;

// Variablen für Systemzeiten
unsigned long AktuelleZeit=0;                   //aktuelle Zeit-Variable um delay nicht benutzen zu müssen
unsigned long LetzterLauf=0;
 
void setup(){
// Anfang: O-LED  
display.init();                                         // initializing display
display.flipScreenVertically();               //command to rotate orientation of display
display.clear();   
//Ende: O-LED


  ThingSpeak.begin(client); //ThingSpeak

  //Anfang: W-Lan
  Serial.begin(9600); 
  Serial.print("Verbinden zu: ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
   // Status zur W-Lan-Verbindung auf O-LED anzeigen
  display.setFont(ArialMT_Plain_16);                        // initializing the font type and size
  display.drawString(0, 0, "W-Lan verbinden");               //(  row number , column number, "text")
  display.display();
  String index_w_lan = "";
  int index = 0;
  
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    // Status zur W-Lan-Verbindung auf O-LED anzeigen
    index++;
    index_w_lan = index_w_lan + "ü";
    display.drawString(0, 20,index_w_lan);
    display.display();
    // Variable index resetten, wenn sie größer ist als 12, da der Arduino-Bildschirm nur 12 Zeichen in einer Zeile kann
    if(index > 12) {
      index = 0;
      index_w_lan = "";
      display.clear();
      display.setFont(ArialMT_Plain_16);                        // initializing the font type and size
      display.drawString(0, 0, "W-Lan verbinden");               //(  row number , column number, "text")
      display.display();    
    }
    // Status zur W-Lan Verbindung auf Seriellem-Monitor ausgeben
    Serial.print("ü");
  }
  Serial.println("xx");
  Serial.println("WiFi connected");
  Serial.print("IP-Address of ESP8266 module: ");
  Serial.println(WiFi.localIP());
  // Status zur W-Lan-Verbindung auf O-LED anzeigen
  display.drawString(0, 40,"W-Lan verbunden!");
  display.display();
//Ende: W-Lan
  
  server.begin();
}
  
void loop(){
AktuelleZeit = millis();  
if(LetzterLauf > AktuelleZeit){ // Sollte aus unerklärlichen Gründen LetzterLauf größer als AktuelleZeit sein, so setzen wir die Variable zurück
  LetzterLauf = AktuelleZeit;
}

if ( (AktuelleZeit - LetzterLauf) > 10000){ //alle 10 Sekunden die Daten aktualisieren
float temperatureInF = ThingSpeak.readFloatField(myChannelNumber, 1);
String stringOne = String(temperatureInF, 2);
Serial.println(temperatureInF);
display.clear();  
display.setFont(ArialMT_Plain_16);                        // initializing the font type and size
display.drawString(0, 15, "Temp. Stuttgart");               //(  row number , column number, "text")
display.drawString(0, 35, " " + stringOne + "°C");
display.display(); 
LetzterLauf = AktuelleZeit;
}

}
