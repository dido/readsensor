# readsensor
Networked Temperature / Humidity / Atmospheric Temperature Sensor

# Introduction

So one day I decided to do a small project involving a [NodeMCU v3
ESP8266
board](https://www.theengineeringprojects.com/2018/10/introduction-to-nodemcu-v3.html)
which I got ridiculously cheap (about the equivalent of $5), and a
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