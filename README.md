"# Anzeige-ThingSpeak-mit-OLED" 

Stand: 20.11.2023\
Es wurde eine Uhrzeitanzeige hinzugefügt. Außerdem zeigt das O-LED Display ganz unten die letzte Uploadzeit von ThingSpeak an. Als Bibliothek muss NTP von Stefan Staub installiert werden. Außerdem wurde ein Bild hinzugefügt.\
\
Stand: 17.11.2023\
\
Dies ist eine Anzeige mit einem Arduino-Board mit integriertem O-LED Bilschirm. Es holt von ThingSpeak die Daten von, welche von einem Temperatursensor zuvor hochgeladen wurden, und zeigt diese an. Dies kann somit als Anzeige für eine Ausentemperatur verwendet werden.\
Das Projekt um mit einen DS18B20 Temperatursensor 
Daten auf ThingSpeak hochzuladen liegt hier:\
https://github.com/quiddi-github/Temperatursensor-DS18B20
\
Das hier verwendete Board zur Anzeige ist:
ideaspark\
ESP8266 0.96" OLED Module\
VR: 2.1\
\
Es muss in der Arduino-IDE als\
zusätzliche Boardverwalter-URL\
eingegeben werden:\
http://arduino.esp8266.com/stable/package_esp8266com_index.json
\
Als Board wird dann in der Arduino IDE unter "ESP8266 Boards" das Board "NodeNCU 0.9 (ESP-12 Module)" eingestellt. Alle 10 Sekunden werden die Daten von ThingSpeak gelesen.\
Bitte anpassen:\
Zeile 6 W-Lan SSID\
Zeile 7 W-Lan Passwort\
Zeile 22 ThingSpeak Channel ID\
Zeile 89 ThingSpeak FieldNr\
