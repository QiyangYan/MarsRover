#include <Arduino.h>
#include <string.h>
#include <stdint.h>
#include <SPI.h>
#include <Wire.h>
#include "Drive.h"
#include "ADNS3080.h"
#include "pid.h"
#include "main_function.h"
#include <Robojax_L298N_DC_motor.h>

#include <ArduinoWebsockets.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJSON.h>
#define radar_PIN 22;

const char* ssid = "CharLi"; //Enter SSID
const char* password = "5942132333"; //Enter Password
const char* get_address = "http://18.212.255.51:9000/esp/commands/get"; //Enter server adress or URL
const char* post_address = "http://18.212.255.51:9000/esp/commands/post";
const uint16_t server_port = 9000; // Enter server port


HardwareSerial Serial3(3); // create third port
String Vision_data;
// Use arduinojson.org/v6/assistant to compute the capacity.
// const size_t capacity = JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(2) + 60;

int radar_Pin = 22;
int NumOfTest = 5;
float radar_amp;
float time_2cm;




String command;
String post_data;
String instruction;
float x_axis = 0;
float y_axis = 0;
float ball_x;
float ball_y;
int direction  = 0;
float displacement = 0;

String color;
int distance;
int mid_point;
String mode = "manual";
String state = "stop";



int travelbegin=1;
int travelfinished=0;
int rotatebegin=0;
int rotatefinished=0;
int circle=0;
int temp = 0;


PID pidpointer;
Robojax_L298N_DC_motor car(IN1, IN2, ENA, CHA,  IN3, IN4, ENB, CHB);

// for http setting
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 50;
  


String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    // Serial.print("HTTP Response code: ");
    // Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}


void post_server(String post_data, unsigned long lastTime, unsigned long timerDelay, const char* post_address, 
float x_axis, float y_axis, String color, float ball_x, float ball_y){
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
      //===========================POST=======================//
      // Your Domain name with URL path or IP address with path
      http.begin(client, post_address);
      
      // HTTP request with a content type: application/json
      http.addHeader("Content-Type", "application/json");
      post_data = "{\"x_axis\":\"" + String(x_axis) + "\",\"y_axis\":\"" + String(y_axis) + "\",\"color\":\"" + String(color) + "\",\"ball_x\":\"" + String(ball_x) + "\",\"ball_y\":\"" + String(ball_y) + "\"}";
      Serial.println(post_data);
      int httpResponseCode = http.POST(post_data);
     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
  //===============================================
  
}



int slice_nth_4(int n,int k){
  while(n--){
    k/=16;
  }
  return k%16;
} 

int interpret_fpga_data(int k, String& color, int& mid_point, int& distance){

  if(slice_nth_4(1,k)==0b0000){
    Serial.print("Red Mid-pt: ");
    color = "R";
    Serial.println(slice_nth_4(0,k));
    Serial.print("\n");
    mid_point = slice_nth_4(0,k);
  }
  else if(slice_nth_4(1,k)==0b0001){
    Serial.print("Red Distance: ");
    Serial.println(slice_nth_4(0,k)*5);
    distance = slice_nth_4(0,k)*5;
    Serial.print("\n");
  }
  else if(slice_nth_4(1,k)==0b0010){
    Serial.print("Blue Mid-pt: ");
    color = "B";
    Serial.println(slice_nth_4(0,k));
    mid_point = slice_nth_4(0,k);
    Serial.print("\n");
  }
  else if(slice_nth_4(1,k)==0b0011){
    Serial.print("Blue Distance: ");
    Serial.println(slice_nth_4(0,k)*5);
    distance = slice_nth_4(0,k)*5;
    Serial.print("\n");
  }
  else if(slice_nth_4(1,k)==0b0100){
    Serial.print("Yellow Mid-pt: ");
    color = "Y";
    Serial.println(slice_nth_4(0,k));
    Serial.print("\n");
    mid_point = slice_nth_4(0,k);
  }
  else if(slice_nth_4(1,k)==0b0101){
    // Serial.print("Yellow Distance: ");
    // Serial.println(slice_nth_4(0,k)*5);
    distance = slice_nth_4(0,k)*5;
    // Serial.print("\n");
  }
  else if(slice_nth_4(1,k)==0b0110){
    // Serial.print("Green Mid-pt: ");
    color = "G";
    // Serial.println(slice_nth_4(0,k));
    // Serial.print("\n");
    mid_point = slice_nth_4(0,k);
  }
  else if(slice_nth_4(1,k)==0b0111){
    // Serial.print("Green Distance: ");
    // Serial.println(slice_nth_4(0,k)*5);
    distance = slice_nth_4(0,k)*5;
    // Serial.print("\n");
  }
  else if(slice_nth_4(1,k)==0b1000){
    // Serial.print("D_Green Mid-pt: ");
    color = "D";
    // Serial.println(slice_nth_4(0,k));
    // Serial.print("\n");
    mid_point = slice_nth_4(0,k);
  }
  else if(slice_nth_4(1,k)==0b1001){
    // Serial.print("D_Green Distance: ");
    // Serial.println(slice_nth_4(0,k)*5);
    distance = slice_nth_4(0,k)*5;
    // Serial.print("\n");
  }
  else if(slice_nth_4(1,k)==0b1010){
    // Serial.print("Pink Mid-pt: ");
    color = "P";
    // Serial.println(slice_nth_4(0,k));
    // Serial.print("\n");
    mid_point = slice_nth_4(0,k);
  }
  else if(slice_nth_4(1,k)==0b1011){
    // Serial.print("Pink Distance: ");
    // Serial.println(slice_nth_4(0,k)*5);
    distance = slice_nth_4(0,k)*5;
    // Serial.print("\n");
  }

  if(slice_nth_4(0,k) != 0b0000){
    if (distance < 40){
      return 1;
    }
  }
  return 0;
}

int read_vision_data(String& color, int& mid_point, int& distance){
  int vision_flag;
  // Serial.print("start");
  if(Serial2.available()){
      int Vision_data = Serial2.read();
      vision_flag = interpret_fpga_data(Vision_data, color, mid_point, distance);
      Serial.println(Vision_data);
      Serial.print("\n");
  }
  return vision_flag;
}


void aviod_object(PID *pointer, int mid_point){
  for(int i = 0; i < 3; i++){
    foward(&pidpointer);
  }
  if (mid_point > 8){
    left90(&pidpointer);
    foward(&pidpointer);
    for(int i = 0; i < 2; i++){
      right90(&pidpointer);
      foward(&pidpointer);
    }
  }
  else{
    right90(&pidpointer);
    foward(&pidpointer);
    for(int i = 0; i < 2; i++){
      left90(&pidpointer);
      foward(&pidpointer);
    }
  }
}

void ball_position(float x_axis, float y_axis, int distance, int mid_point, int direction, float& ball_x, float& ball_y){
  int angle = (mid_point-8)*3;
  ball_x = x_axis + direction*x_axis*sin(3.14159265*(angle/180));
  ball_y = y_axis + direction*y_axis*cos(3.14159265*(angle/180));
}




void setup() {
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1,23,22); //read data from the pins reserved for vision
  Serial2.begin(115200, SERIAL_8N1,16,17); //read data from the pins reserved for drive
  Serial3.begin(115200, SERIAL_8E1,21); //read data from the pins reserved for rador
  // Connect to wifi
  WiFi.begin(ssid, password);

  // Wait for connecting WIFI
  for(int i = 0; i < 40 && WiFi.status() != WL_CONNECTED; i++){
    Serial.print("Wifi connecting...");
    delay(100);
  }

  // Check wifi connection
  if(WiFi.status() != WL_CONNECTED) {
    Serial.println("Wifi Connection Failed");
    return;
  }

  if(WiFi.status() == WL_CONNECTED) {
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
  }

  Serial.println("Connected to Wifi, Connecting to server.");

  ADNS3080_set(PIN_SS, PIN_MISO, PIN_MOSI, PIN_SCK);

  PID_init(&pidpointer,0.04,0.01,0.01);
  car.begin();
  delay(100);
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
      //===========================GET========================//
      instruction = httpGETRequest(get_address);
      
      DynamicJsonDocument doc(1024);
      deserializeJson(doc, instruction);
      const char* mode_;
      mode_ = doc["mode"];
      mode = String(mode_);
      const char* command_;
      command_ = doc["command"];
      command = String(command_);
      Serial.println(mode);
      Serial.println(command);
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }




  if(mode =="auto"){
    Serial.print("we are in auto mode");
    direction = 1;
    // foward(&pidpointer);
    // foward(&pidpointer);
    y_axis = 20;
    // right90(&pidpointer);
    Serial.print("foward");
  //-------------------------------loop----------------------------------------------
    
    for(int i = 0; i < 8; i++){
      Serial.print("should enter second loop");
      for(int j = 0; j < 22; j++){
        Serial.print("should vision");
        if (read_vision_data(color, mid_point, distance)){
          aviod_object(&pidpointer, mid_point);
          j = j + 1;
          x_axis += direction*10;
          ball_position(x_axis, y_axis, distance, mid_point, direction, ball_x, ball_y);
        }
        foward(&pidpointer);
        x_axis += direction*10;

        Serial.print("should post 1");
        post_server(post_data, lastTime, timerDelay, post_address, x_axis, y_axis, color, ball_x, ball_y);
      }
      left90(&pidpointer);
      foward(&pidpointer);
      

      y_axis += 10;
      left90(&pidpointer);
      direction = -1*direction;
      for(int k = 0; k < 22; k++){
        if (read_vision_data(color, mid_point, distance)){
          aviod_object(&pidpointer, mid_point);
          k = k + 1;
          x_axis += direction*10;
          ball_position(x_axis, y_axis, distance, mid_point, direction, ball_x, ball_y);
        }
        foward(&pidpointer);
        x_axis += direction*10;

        Serial.print("should post 2");
        post_server(post_data, lastTime, timerDelay, post_address, x_axis, y_axis, color, ball_x, ball_y);
      }
      right90(&pidpointer);
      foward(&pidpointer);
      y_axis += 10;


      right90(&pidpointer);
      direction = -1*direction;
    }

    for(int a = 0; a < 2; a++){
      for(int b = 0; b < 22; b++){
        if (read_vision_data(color, mid_point, distance)){
          aviod_object(&pidpointer, mid_point);
          b = b + 1;
          x_axis += direction*10;
          ball_position(x_axis, y_axis, distance, mid_point, direction, ball_x, ball_y);
        }
        foward(&pidpointer);
        x_axis += direction*10;
        
        Serial.print("should post 3");
        post_server(post_data, lastTime, timerDelay, post_address, x_axis, y_axis, color, ball_x, ball_y);
        
      }
      left90(&pidpointer);
      foward(&pidpointer);
      y_axis += 10;

      post_server(post_data, lastTime, timerDelay, post_address, x_axis, y_axis, color, ball_x, ball_y);

      left90(&pidpointer);
      direction = -1*direction;
      for(int c = 0; c < 22; c++){
        if (read_vision_data(color, mid_point, distance)){
          aviod_object(&pidpointer, mid_point);
          c = c + 1;
          x_axis += direction*10;
          ball_position(x_axis, y_axis, distance, mid_point, direction, ball_x, ball_y);
        }
        foward(&pidpointer);
        x_axis += direction*10;


        Serial.print("should post 4");
        post_server(post_data, lastTime, timerDelay, post_address, x_axis, y_axis, color, ball_x, ball_y);
      }
      right90(&pidpointer);
      foward(&pidpointer);
      y_axis += 10;

      post_server(post_data, lastTime, timerDelay, post_address, x_axis, y_axis, color, ball_x, ball_y);

      right90(&pidpointer);
      direction = -1*direction;
    }
    // go back home
    foward(&pidpointer);
    x_axis += 10;
    
    post_server(post_data, lastTime, timerDelay, post_address, x_axis, y_axis, color, ball_x, ball_y);

    right90(&pidpointer);
    for(int d = 0; d < 36; d++){
        if (read_vision_data(color, mid_point, distance)){
          aviod_object(&pidpointer, mid_point);
          d = d + 1;
          y_axis -= 10;
          ball_position(x_axis, y_axis, distance, mid_point, direction, ball_x, ball_y);
        }
        foward(&pidpointer);
        y_axis -= 10;

        post_server(post_data, lastTime, timerDelay, post_address, x_axis, y_axis, color, ball_x, ball_y);
    }
    right90(&pidpointer);
    for(int e = 0; e < 24; e++){
        if (read_vision_data(color, mid_point, distance)){
          aviod_object(&pidpointer, mid_point);
          e = e + 1;
          x_axis -= 10;
          ball_position(x_axis, y_axis, distance, mid_point, direction, ball_x, ball_y);
        }
        foward(&pidpointer);
        x_axis -= 10;

        post_server(post_data, lastTime, timerDelay, post_address, x_axis, y_axis, color, ball_x, ball_y);
    }


   
  }

  if(mode=="manual")
  {
    manualcontrol(command,&pidpointer); 
  }

}




// if ((millis() - lastTime) > timerDelay) {
//     //Check WiFi connection status
//     if(WiFi.status()== WL_CONNECTED){
//       WiFiClient client;
//       HTTPClient http;
//       //===========================GET========================//
//       instruction = httpGETRequest(get_address);
      
//       DynamicJsonDocument doc(1024);
//       deserializeJson(doc, instruction);
//       const char* mode_;
//       mode_ = doc["mode"];
//       mode = String(mode_);
//       const char* command_;
//       command_ = doc["command"];
//       command = String(command_);
      
//       //===========================POST=======================//
//       // Your Domain name with URL path or IP address with path
//       http.begin(client, post_address);
      
//       // HTTP request with a content type: application/json
//       http.addHeader("Content-Type", "application/json");
//       ballData = "{\"distance\":\"" + String(distance) + "\",\"angle\":\"" + String(mid_point) + "\",\"color\":\"" + String(color) + "\"}";
//       // Serial.println(ballData);
//       int httpResponseCode = http.POST(ballData);
     
//       // Serial.print("HTTP Response code: ");
//       // Serial.println(httpResponseCode);
        
//       // Free resources
//       http.end();
//     }
//     else {
//       Serial.println("WiFi Disconnected");
//     }
//     lastTime = millis();
//   }
//   //===============================================
  