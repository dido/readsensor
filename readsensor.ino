/* Networked Sensors on a NodeMCU 1.0 ESP8266 Microcontroller

   Copyright © 2019 Rafael R. Sevilla

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// include the library code:
#include <Wire.h>
#include <DHT.h>
#include <Adafruit_BMP085.h>

#define USE_SSD1306

#ifdef USE_SSD1306

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DISPLAY display

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#else

#include "Adafruit_LiquidCrystal.h"

Adafruit_LiquidCrystal lcd(0);

#define DISPLAY lcd

#endif

#define DHTPIN 2          // Digital pin connected to sensor
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085 bmp;

volatile int readsensor = 0;
float temp=NAN, hum=NAN, hidx=NAN, atm=NAN, alt=NAN;
unsigned long starttm;

#define USE_WEBSERVER

#ifdef USE_WEBSERVER

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#ifndef STASSID
#define STASSID "DIDO"
#define STAPSK  "EefkuIkPytta"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

void handleRoot() {
  char response[255];
  snprintf(response, 255, "%f:%f:%f:%f:%f", temp, hum, hidx, atm, alt);
  server.send(200, "text/plain", response);
}
void handleNotFound() {
  server.send(404, "text/plain", "404 Not Found");
}

void setup_net(void) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setCursor(0,0);
  display.print("Connecting to: ");
  display.print(ssid);
  display.display();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    display.print(".");
    display.display();
  }
  display.println("connected.");
  display.print("IP address: ");
  display.println(WiFi.localIP());
  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);
  server.begin();
  display.print("HTTP server started");
  display.display();
  delay(5000);
}

#endif

void p2dig(int v)
// print 2 digits with leading zero
{
  if (v < 10) DISPLAY.print("0");
  DISPLAY.print(v);
}

const char *dow2String(uint8_t code)
// Day of week to string. DOW 1=Sunday, 0 is undefined
{
  static const char *str[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  
  if (code > 7) code = 0;
  return(str[code]);
}

void read_sensors()
{
  if (readsensor > 0)
    return;
  readsensor = 15;
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  float hi = dht.computeHeatIndex(t, h, false);
  if (!isnan(t))
    temp = t;
  if (!isnan(h))
    hum = h;
  if (!isnan(hi))
    hidx = hi;
  float tatm = bmp.readPressure();
  float talt = bmp.readAltitude();
  if (!isnan(tatm))
    atm = tatm/100;
  if (!isnan(talt))
    alt = talt;
}

#ifdef USE_SSD1306

int brighttime = 10;

void printSensor(void)
// Print the sensor values to the LCD display
{
  static boolean toggle = true;
  read_sensors();
  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setCursor(0,0);
  display.setTextSize(3);
  if (isnan(temp))
    display.print("--");
  else
    display.printf("%.1f", temp);
  display.println("\370C");
  display.setTextSize(1);
  display.print("Hum:");
  if (isnan(hum))
    display.print("--");
  else
    display.print((int)hum);
  display.print("% ");
  display.print("HI:");
  if (isnan(hidx))
    display.print("--");
  else
    display.print(hidx);
  display.println("\370C");
  if (isnan(atm))
    display.print("--");
  else
    display.print(atm);
  display.print("hPa ");
  if (isnan(alt))
    display.print("--");
  else
    display.print(alt);
  display.println("m");
  for (int i=0; i<readsensor; i++)
    display.print("\333");
  display.println("");
  display.display();
}

void setup_ssd()
{
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) { // Address 0x3D for 128x64
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  delay(2000); // Pause for 2 seconds
  display.clearDisplay();
  display.setTextColor(WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
}

#else

void printSensor(void)
{
  read_sensors();
  lcd.clear();
  lcd.setCursor(0, 0);
  if (isnan(temp))
    lcd.print("--");
  else
    lcd.print((int)temp);
  lcd.print("\337C ");

  if (isnan(hum))
    lcd.print("--");
  else
    lcd.print((int)hum);
  lcd.print("% ");

  if (isnan(hidx))
    lcd.print("--");
  else
    lcd.print(hidx);
  lcd.print("\337");

  lcd.setCursor(0, 1);
  if (isnan(atm))
    lcd.print("--");
  else
    lcd.print(atm);
  lcd.print("hPa");
}

#endif

void setup() {
  Wire.begin();
  dht.begin();
#ifdef USE_SSD1306
  setup_ssd();
#else
  lcd.begin(16, 2);
#endif
  if (!bmp.begin()) {
    for(;;);
  }

#ifdef USE_WEBSERVER
  setup_net();
#endif
  starttm = millis();
  pinMode(0, INPUT_PULLUP);
}

void loop() {
  unsigned long tm = millis();
  if (tm - starttm >= 1000) {
    printSensor();
    readsensor--;
    starttm = tm;
    if (brighttime > 0)
      brighttime--;
  }
  display.dim(brighttime <= 0);
  if (digitalRead(0) == 0)
    brighttime = 10;
#ifdef USE_WEBSERVER
  server.handleClient();
#endif
}
