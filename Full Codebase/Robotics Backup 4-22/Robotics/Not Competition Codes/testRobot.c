#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Hubs,  S2, HTServo,  HTMotor,  none,     none)
#pragma config(Sensor, S3,     infared,        sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     Left,          tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     Right,         tmotorTetrix, openLoop, encoder)
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

#include "JoystickDriver.c"

void initializeRobot(){
	servo[bucket] = 135;
  servo[pin] = 0;
}

void testLift(){
	motor[Lift1] = 100;
	motor[Lift2] = 100;
	wait1Msec(1200);
	motor[Lift1] = 0;
	motor[Lift2] = 0;
	servo[bucket] = 20;
	wait1Msec(500);
	servo[bucket] = 240;
	wait1Msec(500);
	servo[bucket] = 130;
	wait1Msec(500);
	servo[pin] = 20;
	wait1Msec(500);
	servo[pin] = 0;
	motor[Lift1] = -100;
	motor[Lift2] = -100;
	wait1Msec(1000);
	motor[Lift1] = 0;
	motor[Lift2] = 0;
}

void testSweep(){
	motor[Sweep] = 100;
	wait1Msec(500);
	motor[Sweep] = 0;
	wait1Msec(100);
  motor[Sweep] = -100;
	wait1Msec(500);
	motor[Sweep] = -5;
	wait1Msec(500);
}

void testDrive(){
	motor[Left] = 100;
	motor[Right] = -100;
	wait1Msec(1000);
	motor[Left] = 0;
	motor[Right] = 0;
}

void testFlag(){
	motor[Flag] = 100;
	wait1Msec(1000);
	motor[Flag] = 0;
	wait1Msec(100);
	motor[Flag] = -100;
	wait1Msec(1000);
}

task main(){
	initializeRobot();
	testDrive();
	testLift();
	testSweep();
	testFlag();
}
