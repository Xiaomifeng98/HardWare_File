#ifndef _PID_HEAD_H_
#define _PID_HEAD_H_

#define ARDUINO_DEBUG 0

typedef struct {
  float Kp; //P值
  float Ki; //I值
  float Kd; //D值
  float error;  //偏移值
  int sampleTime; //采样时间
  float previous_error; //上次的误差值
} pid_t;

#define SAMPLE_TIME 10
#define KP_VALUE  30
#define KI_VALUE  0.03
#define KD_VALUE  13


#endif
