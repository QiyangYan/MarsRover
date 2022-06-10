#include <Arduino.h>
#include "SPI.h"
#include "ADNS3080.h"
#include <vector>
#include "pid.h"
#include "Drive.h"


float total_x = 0;
float total_y = 0;


float total_x1 = 0;
float total_y1 = 0;

float distance_x=0;
float distance_y=0;

Pid_control b;
PID a;


volatile byte movementflag=0;
volatile int xydat[2];


void setup()
 {
ADNS3080_set(PIN_SS, PIN_MISO, PIN_MOSI, PIN_SCK);
  Serial.begin(115200);

  if(mousecam_init()==-1)
  {
    Serial.println("Mouse cam failed to init");
    while(1);
  }
  b.PID_init(&a, 0.8,0,0);
}

void loop() {
  // put your main code here, to run repeatedly:

 #if 0
/*
    if(movementflag){

    tdistance = tdistance + convTwosComp(xydat[0]);
    Serial.println("Distance = " + String(tdistance));
    movementflag=0;
    delay(3);
    }

  */
  // if enabled this section grabs frames and outputs them as ascii art

  if(mousecam_frame_capture(frame)==0)
  {
    int i,j,k;
    for(i=0, k=0; i<ADNS3080_PIXELS_Y; i++)
    {
      for(j=0; j<ADNS3080_PIXELS_X; j++, k++)
      {
        Serial.print(asciiart(frame[k]));
        Serial.print(' ');
      }
      Serial.println();
    }
  }
  Serial.println();
  delay(250);

  #else

  // if enabled this section produces a bar graph of the surface quality that can be used to focus the camera
  // also drawn is the average pixel value 0-63 and the shutter speed and the motion dx,dy.

  int val = mousecam_read_reg(ADNS3080_PIXEL_SUM);
  MD md;
  mousecam_read_motion(&md);
  for(int i=0; i<md.squal/4; i++)
    Serial.print('*');
  Serial.print(' ');
  Serial.print((val*100)/351);
  Serial.print(' ');
  Serial.print(md.shutter); Serial.print(" (");
  Serial.print((int)md.dx); Serial.print(',');
  Serial.print((int)md.dy); Serial.println(')');
  
  // Serial.println(md.max_pix);
  delay(100);


    distance_x = convTwosComp(md.dx);
    distance_y = convTwosComp(md.dy);

total_x1 = total_x1 + distance_x;
total_y1 = total_y1 + distance_y;

total_x = total_x1/157;
total_y = total_y1/157;

std::vector<float> D{total_x, total_y, distance_x, distance_y};

Serial.print('\n');


Serial.println("Distance_x = " + String(total_x));
Serial.println("Distance_y = " + String(total_y));


Serial.println("Error = "+String(a.err));
Serial.println("KP = "+String(a.Kp));
Serial.println("Duty "+String(a.duty_cycle));

Serial.print('\n');

gostraight(1,70,D);


  delay(250);

  #endif


};

//remember to initialate the PID control



