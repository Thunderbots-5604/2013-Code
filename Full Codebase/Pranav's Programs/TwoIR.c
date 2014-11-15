#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Hubs,  S2, HTServo,  HTMotor,  none,     none)
#pragma config(Sensor, S3,     infrared,        sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     infrared,        sensorHiTechnicIRSeeker1200)
//#pragma config(Sensor, S4,     touch,          sensorTouch)
#pragma config(Motor,  mtr_S1_C1_1,     Left,          tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     Right,         tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     Left2,         tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     Right2,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     Lift1,         tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     Lift2,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_1,     Sweep,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_2,     Flag,          tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    bucket,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    pin,                  tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)

void move(int speed)
{
	speed = .75*speed;
	dir = 1;
	if (speed < 0)
		dir = -1;
	if (speed == 0)
		dir = 0;
  speed = abs(speed);
	if (abs(nMotorEncoder[Left]) > abs(nMotorEncoder[Right]))
  {
  	leftadjust = adjust;
  	rightadjust = 0;
  }
  else
  {
  	leftadjust = 0;
  	rightadjust = adjust;
  }
  motor[Left] = dir*(speed-leftadjust);
  motor[Left2] = dir*(speed-leftadjust);
  motor[Right] = dir*(speed-rightadjust);
  motor[Right2] = dir*(speed-rightadjust);
}

void turn(int speed)
{
	speed = speed*.75;
	dir = 1;
	if (speed < 0)
		dir = -1;
	if (speed == 0)
		dir = 0;
  speed = abs(speed);
	if (abs(nMotorEncoder[Left]) > abs(nMotorEncoder[Right]))
  {
  	leftadjust = adjust;
  	rightadjust = 0;
  }
  else
  {
  	leftadjust = 0;
  	rightadjust = adjust;
  }
  motor[Left] = dir*(speed-leftadjust);
  motor[Left2] = dir*(speed-leftadjust);
  motor[Right] = -dir*(speed-rightadjust);
  motor[Right2] = -dir*(speed-rightadjust);
}

void swingLeft(int speed)
{
  motor[Left] = 0;
  motor[Left2] = 0;
  motor[Right] = speed;
  motor[Right2] = speed;
}
void swingRight(int speed)
{
  motor[Left] = speed;
  motor[Left2] = speed;
  motor[Right] = 0;
  motor[Right2] = 0;
}

void initializeRobot()
{
	servo[bucket] = 130;
	servo[pin] = 0;
}

void resetEncoders()
{
	nMotorEncoder[Left] = 0;
	nMotorEncoder[Right] = 0;
}

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

float in = 114.649682;



task main()
{



}
