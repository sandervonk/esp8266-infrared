# esp8266-infrared [![Build Status](https://travis-ci.org/sandervonk/esp8266-infrared.svg?branch=master)](https://travis-ci.org/sandervonk/esp8266-infrared#)
Describes how to use an ESP8266 and infrared LED to let Google Assistant control infrared enabled devices.

Have you ever wondered why you should buy new devices just because the old ones don't support IoT?   Any device controlled by an infrared remote can be transferred into an IoT device with a Adafruit ESP8266, an infrared receiver and LED, and your remote control. With the help of an IR code library, I was able to make a program that does just that.

![image](dialog.svg)

Software dependencies
* [Arduino 1.8.5 IDE](https://www.arduino.cc/)
* [ESP8266 2.4.0 board support](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/using-arduino-ide")
* [Library WiFiManager 0.12.0](https://github.com/tzapu/WiFiManager)
* [Library ESP8266_Framework 1.0.0](https://github.com/cvonk/esp8266-framework)
* [Library ESP8266_Fatal 1.0.0](https://github.com/cvonk/esp8266-fatal)
* [Library IRremoteESP8266 2.3.1](https://github.com/markszabo/IRremoteESP8266)

Hardware dependencies
* [Infrared Receiver (Vishay TSOP38238)](https://www.mouser.com/ds/2/427/tsop382-531411.pdf)
* [Infrared Diode 875nm (Everlight EL-SIR333-A)](http://www.everlight.com/file/ProductFile/SIR333-A.pdf)
* [NPN Transistor (PN2222A)](https://www.mouser.com/ds/2/308/PN2222A-1121407.pdf)
* [ESP8266 dev board (Feather HUZZAH ESP8266 or equiv.)](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/downloads)
* Resistor (1k&#x2126; &frac14;W)
* Resistor (39&#x2126; &frac14;W)
* [Feather Proto board or equiv.](https://www.adafruit.com/product/2884)

Continue reading at [coertvonk.com](https://coertvonk.com/sw/embedded/google-home-ifttt-esp8266-integration-23066).
