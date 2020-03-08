#include "pid.h"
#include<SoftwareSerial.h>
#include<Servo.h>
#ifdef ARDUINO_DEBUG
int debugLeftSpeed;
int debugRightSpeed;
uint8_t debugIrs = 0;
#endif 
//对应的四个电机驱动
const float motorSpeed = 140; 
const int IR_PIN[] = {A0, A1, A2, A3, A4};
const int  IN1 = 13;  //右边轮子
const int  IN2 = 12;  //右边轮子
const int  IN3 = 11;  //左边轮子
const int  IN4 = 10;  //左边轮子
const int IN_A1 = 10;  //
const int IN_A2 = 11;  //
const int IN_B1 = 12;   //
const int IN_B2 = 13;   //

const int _pwmLeftPin  = 5;
const int _pwmRightPin = 6;
const int pwmleft = 5;
const int pwmright = 6;
pid_t pid;
//#define PIN_TRIG 3 //发送引脚
//#define PIN_ECHO 4 //接收引脚

int rate = 140;
float pidValue = 0;
bool turnFlag = false;
SoftwareSerial bluetoothSerial(8,9);
SoftwareSerial SpeakerSerial(2,7);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  bluetoothSerial.begin(115200);

  //放歌
  cmd_5();
  set_speed(rate);
  
  //电机驱动引脚
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  int i;
  for (i = 0; i < 5; i++) {
    pinMode(IR_PIN[i], INPUT);
  }

  pid.sampleTime = SAMPLE_TIME;
  pid.Kp = KP_VALUE;
  pid.Ki = KI_VALUE;
  pid.Kd = KD_VALUE;
  pid.error = 0;
  pid.previous_error = 0;
  
  analogWrite(_pwmLeftPin,  motorSpeed );
  analogWrite(_pwmRightPin, motorSpeed );
  
  //超声波测距引脚
  //pinMode(PIN_TRIG, OUTPUT);
  //pinMode(PIN_ECHO, INPUT);
}

uint8_t getIrData(void)
{
  int i, j;
  uint8_t level;
  uint8_t temp;
  uint8_t irs[9] = {0};
  for (j = 0; j < 9; j ++) {
    
      for (i = 0; i < 5; i++) {
        level = digitalRead(IR_PIN[i]);
        if (level) {
          bitSet(irs[j], i);
        } else {
          bitClear(irs[j], i);
        }
      }
  }
  for (i = 0; i < 9 - 1; i ++) {
    for (j = 0; j < 9 - i - 1; j ++) {
      if (irs[j] > irs[j + 1]) {
        temp = irs[j];
        irs[j] = irs[j + 1];
        irs[j + 1] = temp;
      }
    }
  }
  
  #ifdef ARDUINO_DEBUG
    debugIrs = irs[4];
  #endif 

  return irs[4];
}

int calcErrorByIrsValue(uint8_t irs)
{
  int curError = pid.error;

  switch (irs) {
    case B11110: curError = -8; break;
    
    case B10000:
    case B11000: curError = -7; break;
    
    case B11100: curError = -6; break;
    case B11101: curError = -4; break;
    case B11001: curError = -2; break;
    
    case B00000:
    case B11011: curError = 0;  break;
    
    case B10011: curError = 2;  break;
    case B10111: curError = 4;  break;
    case B00111: curError = 6;  break;
    
    case B00011:
    case B00001: curError = 7;  break;
    
    case B01111: curError = 8;  break;
    case B11111: curError = pid.error > 0 ? 9 : - 9; break;
  }

  return curError;
}

void _sortData(int *p, int n)
{
  int temp;
  int i, j;
  
  for (i = 0; i < n - 1; i ++) {
    for (j = 0; j < n - i - 1; j ++) {
      if (p[j] > p[j + 1]) {
        temp = p[j];
        p[j] = p[j + 1];
        p[j + 1] = temp;
      }
    }
  }

  return;
}

//取得准确的偏差值
void calcCurrentError(void)
{
  int i;
  uint8_t irs;
  float sum = 0;
  int errorData[10];

  for (i = 0; i < 10; i ++) {
    irs =  getIrData();
    errorData[i] =  calcErrorByIrsValue(irs);
  }

  _sortData(errorData, 10);

  for (i = 1; i < 10 - 1; i ++) {
    sum += errorData[i];
  }

  pid.error = sum / 8;

  return;
}

//设置左右边的速度
void motorControl(float pidValue, bool turnFlag)
{
  int leftMotorSpeed = 0;
  int rightMotorSpeed = 0;
  

  leftMotorSpeed  = constrain((motorSpeed + pidValue), -255, 255);
  rightMotorSpeed = constrain((motorSpeed - pidValue), -255, 255);

  if (turnFlag) {
    if (abs(leftMotorSpeed) > abs(rightMotorSpeed)) {
      leftMotorSpeed  = abs(leftMotorSpeed);
      rightMotorSpeed = leftMotorSpeed;
      turn_sound_flag = 2;
      //cmd_2();
      //Serial.println("cmd_2()被执行");
    } else {
      rightMotorSpeed =  abs(rightMotorSpeed);
      leftMotorSpeed  = rightMotorSpeed;
      //Serial.println("cmd_3()被执行");
      //cmd_3();
    }
  } else {
    leftMotorSpeed  = leftMotorSpeed  > 0 ? leftMotorSpeed  : -leftMotorSpeed;
    rightMotorSpeed = rightMotorSpeed > 0 ? rightMotorSpeed : -rightMotorSpeed;
  }

  analogWrite(_pwmLeftPin,  leftMotorSpeed );
  analogWrite(_pwmRightPin, rightMotorSpeed);

#ifdef ARDUINO_DEBUG
  debugLeftSpeed  = leftMotorSpeed ;
  debugRightSpeed = rightMotorSpeed;
#endif 

  return;
}

bool calculatePid(float *pValue)
{
  float P = 0;
  static float I = 0 ;
  float D = 0 ;
  static unsigned long lastTime = 0;
  unsigned long now = millis();
  int timeChange = now - lastTime;

  if (timeChange < pid.sampleTime) {
    return false;
  }

  P = pid.error;
  I = I + pid.error;
  D = pid.error - pid.previous_error;

  *pValue = (pid.Kp * P) + (pid.Ki * I) + (pid.Kd * D) + 1;
  *pValue = constrain(*pValue, -motorSpeed,motorSpeed);

  pid.previous_error = pid.error;
  lastTime = now;

  return true;
}

#if ARDUINO_DEBUG
void print_debug()
{
  int i;
  String irs2bin = String(debugIrs, 2);
  int len = irs2bin.length();
  if (len < 5) {
    for (i = 0; i < 5 - len; i++) {
      irs2bin = "0" + irs2bin;
    }
  }
  
  Serial.print("IRS : ");
  Serial.print(irs2bin);
  Serial.print("   ML:");
  Serial.print(debugLeftSpeed);
  Serial.print("   MR:");
  Serial.print(debugRightSpeed);
  Serial.print("  ERROR:");
  Serial.print(pid.error, OCT);
  Serial.println();
}
#endif

//计算方向
void calcDirection(void)
{
  if (pid.error >= 7 && pid.error <= 9) {
    turnLeft();
    turnFlag = true;
  } else if (pid.error >= -9 && pid.error <= -7) {
    turnRight();
    turnFlag = true;
  } else {
    goForward();
    turnFlag = false;
  }

  return;
}

void goForward(void)
{
  digitalWrite(IN_A1, LOW);
  digitalWrite(IN_A2, HIGH);
  digitalWrite(IN_B1, LOW);
  digitalWrite(IN_B2, HIGH);
}

void turnRight(void)
{
  digitalWrite(IN_A1, LOW);
  digitalWrite(IN_A2, HIGH);
  digitalWrite(IN_B1, HIGH);
  digitalWrite(IN_B2, LOW);
}

void turnLeft(void)
{
  digitalWrite(IN_A1, HIGH);
  digitalWrite(IN_A2, LOW);
  digitalWrite(IN_B1, LOW);
  digitalWrite(IN_B2, HIGH);
}

void leftMotorForward() //左边正转
{
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void leftMotorBack() //左边反转
{
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void rightMotorForward() //右边正转
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void rightMotorBack() //右边发转
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void car_forward()
{
  rightMotorForward();
  leftMotorForward();
  //delay(1000);
}


void car_back()
{
  leftMotorBack();
  rightMotorBack();
  //delay(1000);
}

void car_left()
{
  leftMotorBack();
  rightMotorForward();
  //delay(1000);
}

void car_right()
{
  leftMotorForward();
  rightMotorBack();
  //delay(1000);
}

void car_stop()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  //delay(1000);
}

void set_speed(int speed_value)
{
  analogWrite(pwmleft, speed_value);
  analogWrite(pwmright, speed_value);
}

//转圈,转向
void turn_around()
{
  analogWrite(pwmleft, 120);
  analogWrite(pwmright, 120);
  rightMotorForward();
  leftMotorBack();
  //delay(100);
}

//加速
void accelerate(void)
{
  set_speed(120);
  car_forward();
  for (int i = 120; i <= 255; i++)
  {
    set_speed(i);
    delay(37);
  }
}

int sound_flag = 0;
char Blue_Tooth(void)
{
  char recv;
  bluetoothSerial.listen(); //监听蓝牙串口数据

  while(bluetoothSerial.available() > 0)
  {
    recv = bluetoothSerial.read();
    Serial.println(recv, HEX);
    sound_flag = 1;
    return recv;
  }
}

//向前
void cmd_1(){
  Serial.begin(115200);
  SpeakerSerial.begin(9600);
  char cmd[] = {0x7E,0x05,0x43,0x00,0x01,0x47,0xEF};
  SpeakerSerial.write(cmd,sizeof(cmd)/sizeof(cmd[0]));
}

//向左
void cmd_2(){
  Serial.begin(115200);
  SpeakerSerial.begin(9600);
  char cmd[] = {0x7E,0x05,0x43,0x00,0x02,0x44,0xEF};
  SpeakerSerial.write(cmd,sizeof(cmd)/sizeof(cmd[0]));
}

//向右
void cmd_3(){
  Serial.begin(115200);
  SpeakerSerial.begin(9600);
  char cmd[] = {0x7E,0x05,0x43,0x00,0x03,0x45,0xEF};
  SpeakerSerial.write(cmd,sizeof(cmd)/sizeof(cmd[0]));
}

//我们不一样
void cmd_5(){
  Serial.begin(115200);
  SpeakerSerial.begin(9600);
  char cmd[] = {0x7E,0x05,0x41,0x00,0x05,0x41,0xEF};
  char cmd_2[] = {0x7E,0x04,0x31,0x19,0x2C,0xEF};
  SpeakerSerial.write(cmd_2,sizeof(cmd_2)/sizeof(cmd_2[0]));
  SpeakerSerial.write(cmd,sizeof(cmd)/sizeof(cmd[0]));
}

//循迹
void cmd_10(void)
{  
  Serial.begin(115200);
  SpeakerSerial.begin(9600);
  char cmd[] = {0x7E,0x05,0x43,0x00,0x0A,0x4C,0xEF};
  SpeakerSerial.write(cmd,sizeof(cmd)/sizeof(cmd[0]));
}

//向后
void cmd_14(){
  Serial.begin(115200);
  SpeakerSerial.begin(9600);
  char cmd[] = {0x7E,0x05,0x43,0x00,0xE,0x48,0xEF};
  SpeakerSerial.write(cmd,sizeof(cmd)/sizeof(cmd[0]));
}

//刹车
void cmd_15(){
  Serial.begin(115200);
  SpeakerSerial.begin(9600);
  char cmd[] = {0x7E,0x05,0x43,0x00,0x0F,0x49,0xEF};
  SpeakerSerial.write(cmd,sizeof(cmd)/sizeof(cmd[0]));
}

void Track(void)
{
  bool ok;
  float  pidValue;

  calcCurrentError(); //取得准确的偏差，给‘pid.error’一个平均值
  ok = calculatePid(&pidValue);//小于上次比较时间就继续比较，否则返回一个true，并给计算P、I、D的值
  if (ok) {
    calcDirection();  //计算方向
    motorControl(pidValue, turnFlag);//设置左右边的速度
  }

  //delay(500);
  
#if ARDUINO_DEBUG
  print_debug();
  //delay(1000);
#endif 

  return;  
}

void loop() 
{
  switch(Blue_Tooth())
  {
    case 0xA:
    {
      if(sound_flag)
      {
        rate += 20;
        if(rate >=240)
          rate = 255;
        set_speed(rate);
        Serial.println();
        cmd_1();
        //delay(2000);
        sound_flag = 0;
      }
      car_forward();
      delay(10);
    }
      break;
    case 0xB:
    {
      if(sound_flag)
      {
        rate -= 20;
        if(rate <= 80)
          rate = 80;
        set_speed(rate);
        Serial.println();
        cmd_14();
        //delay(2000);
        sound_flag = 0;
      }
      car_back();
      delay(10);
    }
      break;
    case 0xC:
    {
      if(sound_flag)
      {
        Serial.println();
        cmd_2();
        //delay(2000);
        sound_flag = 0;
      }
      car_right();
      delay(10);
    }
      break;
    case 0xD:
    {
      if(sound_flag)
      {
        Serial.println();
        cmd_3();
        //delay(2000);
        sound_flag = 0;
      }
      car_left();
      delay(10);
    }
      break;
    case 0x10:
    {
      if(sound_flag)
      {
        Serial.println();
        cmd_15();
        //delay(2000);
        sound_flag = 0;
      }
      car_stop();
    }
      break;
    case 0xE:
    {
      if(sound_flag)
      {
        Serial.println();
        cmd_10();
        //delay(2000);
        sound_flag = 0;
      }
      Track();
    }
      break;
  }
}
