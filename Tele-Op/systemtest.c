#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Hubs,  S2, HTServo,  HTMotor,  none,     none)
#pragma config(Sensor, S3,     infared,        sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     touch,          sensorTouch)
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

#include "JoystickDriver.c"

int pressTime = 300;

int servoBase = 102; //was 135, 72
int servoMovement = 50;

int pinvalue = 0;

void initializeRobot(){
	servo[bucket] = servoBase;
  servo[pin] = 0;
}

void resetEncoders(){
	nMotorEncoder[Left] = 0;
	nMotorEncoder[Right] = 0;
}

task changeFunctions();
int nxtFunction = 1;

task main()
{
	StartTask(changeFunctions);
	nNxtExitClicks = 999999999;

	while (nxtFunction != 0)
	{
		while (nxtFunction == 1){
			nxtDisplayCenteredTextLine(0, "Left drive");
			while (nNxtButtonPressed == 2){
				motor[Left] = -100;
				motor[Left2] = -100;
			}
			while (nNxtButtonPressed == 1){
				motor[Left] = 100;
				motor[Left2] = 100;
			}
			motor[Left] = 0;
			motor[Left2] = 0;
			if (nNxtButtonPressed == 0)
				resetEncoders();
		}

		while (nxtFunction == 2){
			nxtDisplayCenteredTextLine(0, "Right drive");
			while (nNxtButtonPressed == 2){
				motor[Right] = -100;
				motor[Right2] = -100;
			}
			motor[Right] = 0;
			motor[Right2] = 0;
			while (nNxtButtonPressed == 1){
				motor[Right] = 100;
				motor[Right2] = 100;
			}
			motor[Right] = 0;
			motor[Right2] = 0;
			if (nNxtButtonPressed == 0)
				resetEncoders();
		}

		while (nxtFunction == 3)
		{
			nxtDisplayCenteredTextLine(0, "Straight drive");
			while (nNxtButtonPressed == 2){
				motor[Right] = -100;
				motor[Right2] = -100;
				motor[Left] = -100;
				motor[Left2] = -100;
			}
			while (nNxtButtonPressed == 1){
				motor[Right] = 100;
				motor[Right2] = 100;
				motor[Left] = 100;
				motor[Left2] = 100;
			}
			motor[Right] = 0;
			motor[Right2] = 0;
			motor[Left] = 0;
			motor[Left2] = 0;
			if (nNxtButtonPressed == 0)
				resetEncoders();
		}

		while (nxtFunction == 4){
			nxtDisplayCenteredTextLine(0, "Flag");
			while (nNxtButtonPressed == 2)
				motor[Flag] = -100;
			motor[Flag] = 0;
			while (nNxtButtonPressed == 1)
				motor[Flag] = 100;
			motor[Flag] = 0;
			if (nNxtButtonPressed == 0)
				nxtFunction = 0;
		}

		while (nxtFunction == 5){
			nxtDisplayCenteredTextLine(0, "Sweeper");
			while (nNxtButtonPressed == 2)
				motor[Sweep] = -50;
			motor[Sweep] = 0;
			while (nNxtButtonPressed == 1)
				motor[Sweep] = 50;
			motor[Sweep] = 0;
			if (nNxtButtonPressed == 0)
				nxtFunction = 0;
		}

		while (nxtFunction == 6){
			nxtDisplayCenteredTextLine(0, "Lift 1&2");
			while (nNxtButtonPressed == 2 && !SensorValue[touch]){
					motor[Lift1] = -100;
					motor[Lift2] = -100;
			}
			while (nNxtButtonPressed == 1){
				motor[Lift1] = 100;
				motor[Lift2] = 100;
			}
			motor[Lift1] = 0;
			motor[Lift2] = 0;
			if (nNxtButtonPressed == 0)
				nxtFunction = 0;
		}

		while (nxtFunction == 7){
			nxtDisplayCenteredTextLine(0, "Lift 1");
			while (nNxtButtonPressed == 2 && !SensorValue[touch]){
					motor[Lift1] = -100;
				}
			while (nNxtButtonPressed == 1){
				motor[Lift1] = 100;
			}
			motor[Lift1] = 0;
			if (nNxtButtonPressed == 0)
				nxtFunction = 0;
		}

		while (nxtFunction == 8){
			nxtDisplayCenteredTextLine(0, "Lift 2");
			while (nNxtButtonPressed == 2 && !SensorValue[touch]){
				motor[Lift2] = -100;
			}
			while (nNxtButtonPressed == 1){
				motor[Lift2] = 100;
			}
			motor[Lift2] = 0;
			if (nNxtButtonPressed == 0)
				nxtFunction = 0;
		}-

		while (nxtFunction == 9){
			nxtDisplayCenteredTextLine(0, "Bucket");
			if (nNxtButtonPressed == 2)
				servo[bucket] = servoBase - servoMovement;
			if (nNxtButtonPressed == 1)
				servo[bucket] = servoBase + servoMovement;
			if (nNxtButtonPressed == 0)
				servo[bucket] = servoBase;
		}

		while (nxtFunction == 10){
			nxtDisplayCenteredTextLine(0, "Pin");
			nxtDisplayCenteredTextLine(1, "Press grey to skip to lift");
			if (nNxtButtonPressed == 2)
				pinvalue = 30;
			if (nNxtButtonPressed == 1)
				pinvalue = 0;
			if (nNxtButtonPressed == 0)
				nxtFunction = 6;
		}
	}
	StopTask(changeFunctions);
	resetEncoders();
}

task changeFunctions()
{
	while (true)
	{
		if (nNxtButtonPressed == 3){
			nxtFunction++;
			if (nxtFunction == 11)
				nxtFunction = 1;
			wait1Msec(pressTime);
		}
		nxtDisplayCenteredTextLine(1, "L enc: %d", nMotorEncoder[Left]);
		nxtDisplayCenteredTextLine(2, "R enc: %d", nMotorEncoder[Right]);
		servo[pin] = pinvalue;
	}
}
