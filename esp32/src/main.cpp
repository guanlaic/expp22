#include <Arduino.h>
#include <WiFi.h>
#include <iostream>
#include <sstream>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>




#define UP 1
#define down  2
#define LEFT 3 
#define RIGHT 4
#define STOP 0

#define RIGHT_MOTOR 0
#define LEFT_MOTOR 1

#define FORWORD 1
#define BACKWARD -1

const int PWMreq = 1000; // 1KHz
const int PWMResolution =8;
const int PWMSpeedChanel =4;


const char* ssid ="guanlaic";
const char* password = "410419aA";

AsyncWebServer server(80);
AsyncWebServer wsCarInput("/CarInput");


struct MOTOR_PINS 
{
  int pinEn;
  int PinIN1;
  int PinIN2;
};
std :: vector<MOTOR_PINS> motorPins =
{
  {22,16,17}, //Right motor) EnA,IN1,IN2)
  {23,18,19}, //Left moto (EnB,IN3,IN4)
};
void   setUpPinModes() {

ledcSetup(PWMSpeedChanel,PWMreq,PWMSpeedChanel);

for (int i=0; i<motorPins.size(); i++){
  pinMode(motorPins[i].pinEn, OUTPUT);
  pinMode(motorPins[i].PinIN1, OUTPUT);
  pinMode(motorPins[i].PinIN2, OUTPUT);

  //ledcAttachPin(motorPins[i],pinEn,PWMSpeedChanel);
}
void handleRoot(AsyncWebServerRequest*request){
  requesst -> send(200,"test/html",htmlHomePage)
}

void handleNotFound(AsyncWebServerRequest*request){
  requesst -> send(404,"test/plain","404 not found")
}
void setup() {
  setUpPinModes();
  Serial.begin(115200);

  WiFi.softAP(ssid, password);
  IPAddress IP =  WiFi.softAPIP();
  Serial.print("AP IP address");
  Serial.println(IP);

  server.on ("/",HTTP_GET, handleRoot);
  server.onNotFound(handleNotFound);
  

  wsCarInput.onEvent(onCarInputWebSocketEvent);
  server.addHandler(&wsCarInput);
  server.begin();
  Serial.println("HTTP Serber started");

  
}

void loop() {
  // put your main code here, to run repeatedly:
}

