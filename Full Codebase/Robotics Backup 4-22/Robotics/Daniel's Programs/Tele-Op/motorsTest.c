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
	servo[bucket] = 135;
  servo[pin] = 0;
}

task main()
{
	long c;
	short nxtFunction = 1;
	nNxtExitClicks = 999999999;

	while (nxtFunction != 0){
		if (nxtFunction == 1){
			nxtDisplayCenteredTextLine(0, "Left One");
			if (nNxtButtonPressed == 3){
				c = nMotorEncoder[Left];
				motor[Left] = 100;
				wait10Msec(120);
				if (nMotorEncoder[Left] <= c+1440){
					nxtDisplayCenteredTextLine(3, "Left Encoder Broken");
					wait10Msec(100);
				}
			}
			if (nNxtButtonPressed == 2)
				nxtFunction = 8;

			motor[Left] = 0;
			if (nNxtButtonPressed == 1)
				nxtFunction++;

			if (nNxtButtonPressed == 0)
				nxtFunction = 0;
		wait1Msec(pressTime);
		}

		if (nxtFunction == 2){
			nxtDisplayCenteredTextLine(0, "Left Two");
			if (nNxtButtonPressed == 3){
				c = nMotorEncoder[Left];
				motor[Left2] = 100;
				wait10Msec(120);
				if (nMotorEncoder[Left] <= c+1440){
					nxtDisplayCenteredTextLine(3, "Left Encoder Broken");
					wait10Msec(100);
				}
			}
			if (nNxtButtonPressed == 2)
				nxtFunction--;

			motor[Left2] = 0;
			if (nNxtButtonPressed == 1)
				nxtFunction++;

			if (nNxtButtonPressed == 0)
				nxtFunction = 0;
		wait1Msec(pressTime);
		}

		if (nxtFunction == 3){
			nxtDisplayCenteredTextLine(0, "Right One");
			if (nNxtButtonPressed == 3){
				c = nMotorEncoder[Right];
				motor[Right] = 100;
				wait10Msec(120);
				if (nMotorEncoder[Right] <= c+1440){
					nxtDisplayCenteredTextLine(3, "Right Encoder Broken");
					wait10Msec(100);
				}
			}
			if (nNxtButtonPressed == 2)
				nxtFunction--;

			motor[Right] = 0;
			if (nNxtButtonPressed == 1)
				nxtFunction++;
			if (nNxtButtonPressed == 0)
				nxtFunction = 0;
		wait1Msec(pressTime);
		}

		if (nxtFunction == 4)
			nxtDisplayCenteredTextLine(0, "Right Two");
			if (nNxtButtonPressed == 3){
				c = nMotorEncoder[Right];
				motor[Right2] = 100;
				wait10Msec(120);
				if (nMotorEncoder[Right] <= c+1440){
					nxtDisplayCenteredTextLine(3, "Right Encoder Broken");
					wait10Msec(100);
				}
			}
			if (nNxtButtonPressed == 2)
				nxtFunction--;

			motor[Right2] = 0;
			if (nNxtButtonPressed == 1)
				nxtFunction++;
			if (nNxtButtonPressed == 0)
				nxtFunction = 0;
		wait1Msec(pressTime);
		}

		if (nxtFunction == 5){
			nxtDisplayCenteredTextLine(0, "Lift One");
			while (nNxtButtonPressed == 3){
				motor[Lift1] = 100;
			}
			motor[Lift1] = 0;

			if (nNxtButtonPressed == 2)
				nxtFunction--;
			if (nNxtButtonPressed == 1){
				nxtFunction++;
			if (nNxtButtonPressed == 0)
				nxtFunction = 0;
		wait1Msec(pressTime);
		}

		if (nxtFunction == 6){
			nxtDisplayCenteredTextLine(0, "Lift Two");
			if (!SensorValue[touch]){
				while (nNxtButtonPressed == 3 && !SensorValue[touch]){
					motor[Lift2] = -100;
				}
				motor[Lift2] = 0;
			}
			if (nNxtButtonPressed == 2)
				nxtFunction--;
			if (nNxtButtonPressed == 1)
				nxtFunction++;
			if (nNxtButtonPressed == 0)
				nxtFunction = 0;
		wait1Msec(pressTime);
		}

		if (nxtFunction == 7){
			nxtDisplayCenteredTextLine(0, "Flag");
			if (nNxtButtonPressed == 3){
				motor[Flag] = 100;
				wait1Msec(3000);
			}
			motor[Flag] = 0;
			if (nNxtButtonPressed == 2)
				nxtFunction--;
			if (nNxtButtonPressed == 1)
				nxtFunction++;
			if (nNxtButtonPressed == 0)
				nxtFunction = 0;
		wait1Msec(pressTime);
		}
		if (nxtFunction == 8){
			nxtDisplayCenteredTextLine(0, "Sweeper");
			if (nNxtButtonPressed == 3){
				motor[Sweep] = -100;
				wait1Msec(3000);
			}
			motor[Sweep] = 0;
			if (nNxtButtonPressed == 2)
				nxtFunction--;
			if (nNxtButtonPressed == 1)
				nxtFunction = 1;
			if (nNxtButtonPressed == 0)
				nxtFunction = 0;
		wait1Msec(pressTime);
		}
	}
}
