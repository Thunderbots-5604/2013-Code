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

#define pressTime 325

void initializeRobot(){
	servo[bucket] = 102;
  servo[pin] = 0;
}

task main()
{
	short nxtFunction = 1;
	nNxtExitClicks = 999999999;

	while (nxtFunction != 0){
		if (nxtFunction == 1){
			nxtDisplayCenteredTextLine(0, "Left hand drive");
			if (nNxtButtonPressed == 3){
				nxtFunction++;
				wait1Msec(pressTime);
			}
			while (nNxtButtonPressed == 2){
				motor[Left] = -100;
				motor[Left2] = -100;
			}
			motor[Left2] = 0;
			motor[Left] = 0;
			while (nNxtButtonPressed == 1){
				motor[Left] = 100;
				motor[Left2] = 100;
			}
			motor[Left] = 0;
			motor[Left2] = 0;
			if (nNxtButtonPressed == 0)
				nxtFunction = 0;
		}

		if (nxtFunction == 2){
			nxtDisplayCenteredTextLine(0, "Right hand drive");
			if (nNxtButtonPressed == 3){
				nxtFunction++;
				wait1Msec(pressTime);
			}
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
				nxtFunction = 0;
		}

		if (nxtFunction == 3){
			nxtDisplayCenteredTextLine(0, "Flag");
			if (nNxtButtonPressed == 3){
				nxtFunction++;
				wait1Msec(pressTime);
			}
			while (nNxtButtonPressed == 2)
				motor[Flag] = -100;
			motor[Flag] = 0;
			while (nNxtButtonPressed == 1)
				motor[Flag] = 100;
			motor[Flag] = 0;
			if (nNxtButtonPressed == 0)
				nxtFunction = 0;
		}

		if (nxtFunction == 4){
			nxtDisplayCenteredTextLine(0, "Sweeper");
			if (nNxtButtonPressed == 3){
				nxtFunction++;
				wait1Msec(pressTime);
			}
			while (nNxtButtonPressed == 2)
				motor[Sweep] = -50;
			motor[Sweep] = 0;
			while (nNxtButtonPressed == 1)
				motor[Sweep] = 50;
			motor[Sweep] = 0;
			if (nNxtButtonPressed == 0)
				nxtFunction = 0;
		}

		if (nxtFunction == 5){
			nxtDisplayCenteredTextLine(0, "Lift");
			if (nNxtButtonPressed == 3){
				nxtFunction++;
				wait1Msec(pressTime);
			}
			if (!SensorValue[touch]){
				while (nNxtButtonPressed == 2 && !SensorValue[touch]){
					motor[Lift1] = -100;
					motor[Lift2] = -100;
				}
				motor[Lift1] = 0;
				motor[Lift2] = 0;
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

		if (nxtFunction == 6){
			nxtDisplayCenteredTextLine(0, "Bucket");
			if (nNxtButtonPressed == 3){
				nxtFunction++;
				wait1Msec(pressTime);
			}
			if (nNxtButtonPressed == 2)
				servo[bucket] = 102-50;
			if (nNxtButtonPressed == 1)
				servo[bucket] = 102+50;
			if (nNxtButtonPressed == 0)
				servo[bucket] = 102;
		}

		if (nxtFunction == 7){
			nxtDisplayCenteredTextLine(0, "Pin");
			if (nNxtButtonPressed == 3){
				nxtFunction = 1;
				wait1Msec(pressTime);
			}
			if (nNxtButtonPressed == 2)
				servo[pin] = 30;
			if (nNxtButtonPressed == 1)
				servo[pin] = 0;
			if (nNxtButtonPressed == 0)
				nxtFunction = 0;
		}
	}
}
