#include <Arduino.h>  
#include "PID_incre.h"

void pid_initial(PID_incre *PID,float kp,float ki,float kd)
{
PID->kp=kp;
PID->ki=ki;
PID->kd=kd;
PID->reference_value=0;
PID->actual_value=0;
PID->error=0;
PID->error_pre1=0;
PID->error_pre2=0;
PID->integral=0;
PID->duty_cycle=0;
PID->A=0;
PID->B=0;
PID->C=0;
};




float pid_control(PID_incre *PID, float reference_value,float actual_value)
{

PID->A=PID->kp+PID->ki+PID->kd;
PID->B=-2*PID->kd-PID->kp;
PID->C=PID->kd;
PID->reference_value=reference_value;
PID->actual_value=actual_value;
PID->error=PID->reference_value-PID->actual_value;
PID->duty_cycle=PID->A*PID->error+PID->B*PID->error_pre1+PID->C*PID->error_pre2;
PID->error_pre2=PID->error_pre1;
PID->error_pre1=PID->error;
return PID->duty_cycle;

}
;
//https://blog.csdn.net/shuoyueqishilove/article/details/73824173?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522165369513516781432959181%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=165369513516781432959181&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v1~rank_v31_ecpm-1-73824173-null-null.142^v11^pc_search_result_control_group,157^v12^new_style1&utm_term=%E5%9F%BA%E4%BA%8Ec%2B%2B%E7%9A%84PID%E6%8E%A7%E5%88%B6%E5%99%A8&spm=1018.2226.3001.4https://blog.csdn.net/shuoyueqishilove/article/details/73824173?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522165369513516781432959181%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=165369513516781432959181&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v1~rank_v31_ecpm-1-73824173-null-null.142^v11^pc_search_result_control_group,157^v12^new_style1&utm_term=%E5%9F%BA%E4%BA%8Ec%2B%2B%E7%9A%84PID%E6%8E%A7%E5%88%B6%E5%99%A8&spm=1018.2226.3001.4187https://blog.csdn.net/shuoyueqishilove/article/details/73824173?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522165369513516781432959181%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=165369513516781432959181&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v1~rank_v31_ecpm-1-73824173-null-null.142^v11^pc_search_result_control_group,157^v12^new_style1&utm_term=%E5%9F%BA%E4%BA%8Ec%2B%2B%E7%9A%84PID%E6%8E%A7%E5%88%B6%E5%99%A8&spm=1018.2226.3001.4187187
