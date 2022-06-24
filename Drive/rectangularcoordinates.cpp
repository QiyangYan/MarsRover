#include <Arduino.h>
#include "Robojax_L298N_DC_motor.h"
#include "pid.h"
#include "Drive.h"
#include "ADNS3080.h"
#include <vector>

/*

to get the rectangular coordinates
when travelled in positive y direction, 
when travelled in negative y direction,
when travelled in positvie x direction,
when travelled in negative x direction

*/

float positivey=0;
float negativey=0;
float positivex=0;
float negativex=0;
int movementfinished=0;
int turndirection=0;//0 is leftturn and 1 is righturn, only consider 90 degree

std::vector<float> coordinates{positivey+negativey,positivex+negativex};


