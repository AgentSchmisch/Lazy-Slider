# Lazy Slider

## The Project

🥅 The Goal of the project is to provide a simple and quick solution for photography and DIY enthusiasts.
The project combines the a Lazy Susan and a camera slider into one Project with one control unit.

This Project contains all the Arduino Sketches as well as the server files that you need in order to setup the Project on an ESP8266.

## Prerequisites

In order to setup the project quickly and easily it is mandatory to make some preparations

- Setup the ESP8266 in the Arduino IDE as it is shown [here](https://randomnerdtutorials.com/how-to-install-esp8266-board-arduino-ide/)
- install the SPIFFS library in the Arduino IDE [here](https://github.com/esp8266/arduino-esp8266fs-plugin)
- clone this repository

## Installation

- Enter your wifi credentials into `credentials-example.h`

```c++
//add your WIFI credentials here
#define WIFI_SSID1 "your_routers_SSID"
#define WIFI_PASSWORD1 "your_routers_Password"
```

- if you have a second router, that you might want to connect to, you can add the credentials to the file as well
- after that, rename the file to `credentials.h` and move it into the sketch folder
- upload the file to your ESP8266 and check whether the connection to your AP was successful via the serial monitor

## Additional Information

- if you want to use a static IP Address in the `credentials.h` file
- therefore you just have to set the variable `STATIC`to `true` and enter the IP Address and the Gateway that you want to have the ESP8266 running on
