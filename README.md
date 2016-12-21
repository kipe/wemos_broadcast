# Wemos temperature broadcast

This is an example project for [LUT](http://www.lut.fi) course
[Johdanto sulautettuihin järjestelmiin](http://moodle.lut.fi/course/info.php?id=4044).


## Introduction to the idea

The project consists of two main parts:

* an embedded application running on [Wemos D1 mini](https://www.wemos.cc/product/d1-mini.html),
  which broadcasts temperature measurements from [DHT-11 shield](https://www.wemos.cc/product/dht-shield.html)
  to local network with UDP
* a minimal Python -server to receive the data

For the third part, the idea is to use the various
[shields](https://www.wemos.cc/D1-mini-Shields) available for the Wemos D1 to
utilize the data. The third part is to be implemented by the groups during the course.

Some examples include:

* logging the values to a SD card
* displaying the current value on OLED display
* step / servo motor to control shunt
* relay to control heating
* RGB LED to translate the current value as color
    * could also be used to show relay / shunt status
* HTTP server (accessible with phone, tablet, PC, ...) to display the measurement data


## Programming

The programming language is [Arduino](https://www.arduino.cc/), which is

> merely a set of C/C++ functions that can be called from your code.
>
> -- <cite>[Arduino FAQ](https://www.arduino.cc/en/Main/FAQ)</cite>


### Setting up the development environment

Setting up the development environment can be done following the manual at the
[Wemos website](https://www.wemos.cc/tutorial/get-started-arduino.html).


## Sources

To be done.
