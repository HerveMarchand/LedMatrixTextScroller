#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "matrixTextScroller.h"

const char *ssid     = "YOUR_SSID";
const char *password = "YOUR_PWD";


int pinCLK = 10;
int pinCS  = 11;
int pinDIN = 12;

MatrixTextScrollerClass myTestMatrix = MatrixTextScrollerClass(pinCLK, pinCS, pinDIN);

const long utcOffsetInSeconds = 3600;

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

void setup(){

  myTestMatrix.setTextUpdatePeriod(30);

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
  
  timeClient.update();
}

unsigned long lastNtpUpdate = 0;

void loop() {

  String dateStr;

  // update ntp every hour
  if(millis() - lastNtpUpdate > (60 * 60 * 1000) || lastNtpUpdate == 0) {
    lastNtpUpdate = millis();
    timeClient.update();
  }

  // Update date when text is no more displayed
  if(false == myTestMatrix.getDisplayStatus()) {
    // The text is no mode displayed
    dateStr = timeClient.getFormattedTime();
    myTestMatrix.setTextToDisplayWithLoopNumber(dateStr, 1);
    myTestMatrix.startDisplay();
  }
  
  myTestMatrix.refresh();

}
