#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Hubs,  S2, HTServo,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     infrared,       sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     touch,          sensorTouch)
#pragma config(Motor,  mtr_S1_C1_1,     Left,          tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     Right,         tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     Lift1,         tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     Lift2,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     Left2,         tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     Right2,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_1,     Sweep,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_2,     Flag,          tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    bucket,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    pin,                  tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)

static void resetEncoders();
static void initializeRobot();
static void moveForward(float power);
static void brake();
static const float in = 360/PI;
void initializeRobot(){
	resetEncoders();
	brake();
	motor[Lift1] = 0;
	motor[Lift2] = 0;
	motor[Sweep] = 0;
	motor[Flag] = 0;
	servo[bucket] = 72;
	servo[pin] = 0;
}

void moveForward(float power){
	motor[Left] = power;
	motor[Left2] = power;
	motor[Right] = power;
	motor[Right2] = power;
}

void brake(){
	moveForward(0);
}

void resetEncoders(){
	nMotorEncoder[Left] = 0;
	nMotorEncoder[Right] = 0;
}

task

task main()
{

resetEncoders();
ClearTimer(T1);
while (true){
		if (time1[T1]%5000 == 0)
			resetEncoders();
		if ((nMotorEncoder[Left]+nMotorEncoder[Right])/2 <= -0.5*in && (nMotorEncoder[Left]+nMotorEncoder[Right])/2 > -2*in){
			moveForward(30);
		}
		if ((nMotorEncoder[Left]+nMotorEncoder[Right])/2 >= 0.5*in && (nMotorEncoder[Left]+nMotorEncoder[Right])/2 < 2*in){
			moveForward(-30);
		}
		if ((nMotorEncoder[Left]+nMotorEncoder[Right])/2 >= 2*in){
			moveForward(-100);
		}
		if ((nMotorEncoder[Left]+nMotorEncoder[Right])/2 <= -2*in){
			moveForward(100);
		}
		if ((nMotorEncoder[Left]+nMotorEncoder[Right])/2 > -0.5*in){
			if ((nMotorEncoder[Left]+nMotorEncoder[Right])/2 < 0.5*in){
				brake();
			}
		}
	}
}
