#pragma once

//your primary access point
#define WIFI_SSID1 "your_routers_SSID"
#define WIFI_PASSWORD1 "your_routers_Password"

//add other credentials here if you want to connect to an alternative network
#define WIFI_SSID2 "your_routers_SSID"
#define WIFI_PASSWORD2 "your_routers_Password"

//if you want to use a  staticIP adress
//set the variable STATICIP to true
//and enter your settings to the variables below

#define STATICIP false
#define  _IPADDRESS (192,168,0,5)
#define  _GATEWAY (192,168,0,1)
#define  _SUBNET (255, 255, 255, 0)