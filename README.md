# readsensor
Networked Temperature / Humidity / Atmospheric Temperature Sensor

# Introduction

So one day I decided to do a small project involving a [NodeMCU v3
ESP8266
board](https://www.theengineeringprojects.com/2018/10/introduction-to-nodemcu-v3.html)
which I got ridiculously cheap (about the equivalent of US$5), and a
bunch of sensors for temperature and atmospheric pressure.  After
several false starts I finally managed to get the whole thing wired up
properly and now it's sending temperature, humidity, and atmospheric
pressure data to an [RRD](https://oss.oetiker.ch/rrdtool/) on my home
server.

![ReadSensor
 Board](https://raw.githubusercontent.com/dido/readsensor/master/readme-images/board.jpg)

Yes I know it's on a breadboard, but to be honest I kinda suck at
soldering and botched several tries at putting all this together on a
prebuilt perf board, and I'm not going to even think about making a
PCB out of all this any time soon.

# Parts List and Wiring

It requires only a few parts, total price was less than US$20.

* 1 LoLin NodeMCU v3 board
* 1 [0.96" SSD1306 128×64 OLED Display](https://www.adafruit.com/product/326) (This is not exactly the same as what I got, but it seems to be close enough)
* 1 [DHT11 Temperature/Humidity Sensor](https://www.adafruit.com/product/386)
* 1 [BMP180 Barometic Pressure Sensor](https://www.adafruit.com/product/1603) (Again, not exactly the same either)
* 2 4.7kΩ resistor for I²C pullup
* 1 10kΩ resistor for DHT11 pullup

Here's a rather ugly schematic produced by Fritzing for it, should
illustrate how everything comes together though.

![ReadSensor
 Schematic](https://raw.githubusercontent.com/dido/readsensor/master/readme-images/readsensor_schem.jpg)

A breadboard illustration from Fritzing might be more illustrative.

![ReadSensor
 Fritzing Board](https://raw.githubusercontent.com/dido/readsensor/master/readme-images/readsensor_bb.jpg)

# Firmware

The firmware is in the readsensor.ino Arduino sketch. You'll need to
create an ssid.h file containing your network credentials, sort of
like this:
```c
#ifndef STASSID
#define STASSID "YOUR-SSID"
#define STAPSK  "YOUR-PRESHARED-KEY"
#endif
```
so that the NodeMCU knows how to connect to your WiFi network.

