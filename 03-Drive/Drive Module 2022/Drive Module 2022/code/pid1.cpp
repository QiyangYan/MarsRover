#include <iostream>
#include "pid.h"
 
using namespace std;
 
void  Pid_control::PID_init(PID *a, float kp, float ki, float kd)
{
a->actual_value = 0.0;
a->reference_value = 0.0;
a->err = 0.0;
a->err_last = 0.0;
a->err_next = 0.0;
a->Kp = kp;
a->Ki = ki;
a->Kd = kd;
a->duty_cycle=0.0;
}
 
float Pid_control::PID_realize(PID*a,float reference_value, float actual_value ){
a->actual_value=actual_value;
a->reference_value=reference_value;
a->err = a->reference_value - a->actual_value;
a->duty_cycle = a->Kp*(a->err - a->err_next) + a->Ki*a->err + a->Kd*(a->err - 2 * a->err_next + a->err_last);

a->err_last = a->err_next;
a->err_next = a->err;
return a->duty_cycle;
}

