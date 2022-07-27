/* ESP32 Libraries */
#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>

/* C++ Libraries */
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

/* Firebase Libraries */
#include <FirebaseESP32.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

/* NTP Libraries */
#include <NTPClient.h>
#include <WiFiUdp.h>

/* Project Libraries */
#include "AS5600.h"

/* Firebase Defines */
#define DATABASE_URL ""
#define API_KEY ""
#define USER_EMAIL ""
#define USER_PASSWORD ""

/* NTP Defines */
#define dirstr  "Direction"
#define spdstr  "Speed"
#define peakstr "Peak"

/* Project Defines */
#define WIFI_SSID ""                    // Wifi Name
#define WIFI_PASSWORD ""                // WiFi Password
#define LED 2                           // LED GPIO number
#define HALL 15                         // HAL GPIO number
#define USTOSEC 1000000                 // Convert timer factor to seconds 

/* Firebase DB Variables */
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
unsigned long sendDataPrevMillis = 0;
unsigned long count = 0;

/* NTP variables */
String formattedDate;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

/* Project Variables */
AMS_5600 ams5600;
hw_timer_t *My_timer = NULL;
unsigned long int pulseCounter = 0;
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
const float factor = 226.19467;
unsigned int avgCounter = 0;
float windDirection = 0;
float windSpeedAvg = 0;
float windSpeed = 0;
float windPeak = 0;
bool flag = 0;

// Anemometer speed calculus 
// Anemometer Radius = 3 cm
// Anemometer Circunference = 18.85 cm
// Anemometer Unitary pulse distance 6.283 cm (3 pulses per revolution)
// Anemometer Convertion to km/h = 36 -> ((cm / 100) / (miliseconds / 1000)) * 3.6
// Anemometer final factor = 226.19467

void IRAM_ATTR wifiTimer(){
  flag = 1;
}

void IRAM_ATTR pulseInterrupt(){
  pulseCounter++;
}

void setup()
{
  Serial.begin(115200);
  
  /* I2C Config*/
  Wire.begin();
  
  /* WIFI Config */
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);}

  /* Firebase DB Config*/
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  Firebase.setDoubleDigits(5); 

  /* NTP Config */
  timeClient.begin();
  timeClient.setTimeOffset(-10800); // Brazil - GMT -3 
  while(!timeClient.update()){
    timeClient.forceUpdate();}

  /* Timers Config */
  pinMode(LED, OUTPUT);
  My_timer = timerBegin(0, 80, true);
  timerAttachInterrupt(My_timer, &wifiTimer, true);
  timerAlarmWrite(My_timer, 60*USTOSEC, true); // Value in Seconds
  timerAlarmEnable(My_timer); 
  
  /* Sensor Hall Config */
  pinMode(HALL, INPUT);
  attachInterrupt(HALL, pulseInterrupt, FALLING);
}

void loop()
{ 
  
  // Get speed
  currentMillis = millis();
  if((currentMillis - previousMillis) > 1000){

    if (pulseCounter == 0){
      windSpeed = 0;}
    else {
      windSpeed = ((factor * pulseCounter) / ((currentMillis - previousMillis)));}

    windSpeedAvg += windSpeed;
    if(windSpeed > windPeak){
      windPeak = windSpeed;}

    avgCounter++;
    pulseCounter = 0;
    previousMillis = currentMillis;}

  
  if(flag == 1){

    // Get wind direction
    windDirection = ams5600.getRawAngle() * 0.087;

    // Calculate average wind speed
    windSpeedAvg = windSpeedAvg/avgCounter;
    
    // Save data on Firebase DB using wifi
    timeClient.update();
    formattedDate = timeClient.getFormattedDate();
    if (Firebase.ready()){      
      Firebase.setFloat(fbdo, (formattedDate+dirstr)  , windDirection);
      Firebase.setFloat(fbdo, (formattedDate+spdstr)  , windSpeedAvg);
      Firebase.setFloat(fbdo, (formattedDate+peakstr) , windPeak);}

    // Reset data to get new ones
    flag = 0;
    windSpeedAvg = 0;
    avgCounter = 0;
    windPeak = 0;
  }
}
