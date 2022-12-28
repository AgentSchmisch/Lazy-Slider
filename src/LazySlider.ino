/*##############################################
  used pins:
  
  Stepper Motor:
  D12
  D13
  D14
  D15
  
  Endstop switches for slider:
  D9
  D10

*/


#include "config.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <FS.h>   // Include the SPIFFS library
#include <AccelStepper.h>

int stepsPerRevolution=2048;

AccelStepper stepper(AccelStepper::HALF4WIRE,12,13,14,15);


ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'
ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80


String getContentType(String filename); // convert the file extension to the MIME type
bool handleFileRead(String path);       // send the right file to the client (if it exists)

void setup() {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  IPAddress IPADDRESS(_IPADDRESS);
  IPAddress GATEWAY(_GATEWAY);
  IPAddress SUBNET(_SUBNET);

if(STATICIP){
  
   if (!WiFi.config(IPADDRESS, GATEWAY, SUBNET)) {
    Serial.println("STA Failed to configure");
    }
    Serial.println("success");
}


 wifiMulti.addAP(WIFI_SSID1, WIFI_PASSWORD1);   // add Wi-Fi networks you want to connect to
 wifiMulti.addAP(WIFI_SSID2, WIFI_PASSWORD2);

  Serial.println("Connecting ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(250);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           // Send the IP address of the ESP8266 to the computer

  if (MDNS.begin("esp8266")) {              // Start the mDNS responder for esp8266.local
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }

  SPIFFS.begin();                           // Start the SPI Flash Files System
  
  server.onNotFound([]() {                              // If the client requests any URI
    if (!handleFileRead(server.uri()))                  // send it if it exists
      server.send(404, "text/plain", "404: Not Found"); // otherwise, respond with a 404 (Not Found) error
  });

  server.begin();                           // Actually start the server
  Serial.println("HTTP server started");
  
  server.on("/api/v1/slider",HTTP_POST,slider);
  server.on("/api/v1/turntable",HTTP_POST,turntable);
}


void loop(void) {
  server.handleClient();
}


String getContentType(String filename) { // convert the file extension to the MIME type
  
  if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  return "text/plain";
}

bool handleFileRead(String path) { // send the right file to the client (if it exists)
  Serial.println("handleFileRead: " + path);
  Serial.println(path);
  if (path.endsWith("/"))
  path += "index.html";         
  String contentType = getContentType(path);            // Get the MIME type
  if (SPIFFS.exists(path)) {                            // If the file exists
    File file = SPIFFS.open(path, "r");                 // Open it
    size_t sent = server.streamFile(file, contentType); // And send it to the client
    file.close();                                       // Then close the file again
    return true;
  }
  Serial.println("\tFile Not Found");
  return false;                                         // If the file doesn't exist, return false
}

void handlenotfound(){
server.send(404,"text/plain","404: Page not found");
}

void redirect(String location){
server.sendHeader("Location", String("localhost:80/"+location), true);
server.send ( 302, "text/html", "");
}


//documentation step()
//This function turns the motor a specific number of steps, at a speed determined by the most recent call to setSpeed().
//This function is blocking; that is, it will wait until the motor has finished moving to pass control to the next line in your sketch.
//For example, if you set the speed to, say, 1 RPM and called step(100) on a 100-step motor, this function would take a full minute to run.
//For better control, keep the speed high and only go a few steps with each call to step().
// functions for the turntable
//TODO: change the library from <stepper.h> to the A4988 library

void turntable(){

  String direction;
  redirect("turntable.html");
  if(server.hasArg("direction"))
  direction=server.arg("direction");


  String speed=server.arg("speed");
  String angle=server.arg("angle");
  Serial.println(speed);
  Serial.println(angle);
  Serial.println(direction);

  stepper.setSpeed(speed.toInt());
  
  if(direction=="right"){
    stepper.moveTo(angle.toInt()/stepsPerRevolution);
    stepper.run();
  }

  else{
    stepper.moveTo((angle.toInt()/stepsPerRevolution)*(-1));
    stepper.run();
  }

}


void slider(){
  //redirect to the slider menu page
  redirect("slider.html");
  //get the returned values for the slider
  if(server.hasArg("direction"))
    String direction=server.arg("direction");

  String speed=server.arg("speed");
  String time=server.arg("time");
  
  
  
  //set the pins for the variables and whether they are in- or output pins
  int endstop1=9;
  int endstop2=10;
  pinMode(endstop1,INPUT_PULLUP);
  pinMode(endstop2,INPUT_PULLUP);

}