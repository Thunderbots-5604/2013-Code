#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     infrared,       sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     sonar,          sensorSONAR)
#pragma config(Motor,  mtr_S1_C1_1,     leftFront,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     rightFront,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     bucketRaise,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     unknown,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     sweeperArm,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     flagRaise,       tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    bucket,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,            		tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,            		tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)

/* Suggestions from Mr. Caneen:
-Instead of going along the entire bucket row, consider moving backwards to make room for the other robot.
-Instead of using the encoders to measure the distance to the ramp, use a light/color sensor to find the white tape
-Make a second version of the program, with a delay at the beginning to potentially give time for the other robot
-Instead of going straight for the infrared, use a color/sonar/encoder to find the first bucket and put a block in
-Use a dog whistle to signal to the autonomous robot when to start (I think it's illegal but Pranav insists I include it here)
*/

#include "JoystickDriver.c"

void setMovementPower(int power, int modifier){ //TWO WHEELS MAY NOT HAVE MOTORS
	//motor[leftOmni] = -power + modifier;
	//motor[rightOmni] = power + modifier;
	motor[leftFront] = -power - modifier;
	motor[rightFront] = power - modifier;
	return;
}



void resetEncoders(){
	nMotorEncoder[leftFront] = 0;
	nMotorEncoder[rightFront] = 0;
	return;
}

void turn90(int direction){
	int turnRadius = (18 * 3.1415926525); //assuming 18 is the width of the robot
	if (direction == 1){
		int enc = nMotorEncoder[leftFront];
		setMovementPower(0,100);
		while(abs(nMotorEncoder[leftFront] - enc) < turnRadius){ }
		motor[leftFront] = 0;
	}
	if (direction == -1){
		int enc = nMotorEncoder[rightFront];
		motor[rightFront] = 100;
		//motor[rightOmni] = 100;
		while(abs(nMotorEncoder[rightFront] - enc) < turnRadius){}
		motor[rightFront] = 0;
		//motor[rightOmni] = 0;
	}
	resetEncoders();
	return;
}

int distanceTraveled(){
	return 12.566370614 * ((abs(nMotorEncoder[leftFront] + nMotorEncoder[rightFront])/2)/1440);
}

int rightDistanceTraveled(){
	return 12.566370614 * (abs(nMotorEncoder[rightFront])/1440);
}

int leftDistanceTraveled(){
	return 12.566370614 * (abs(nMotorEncoder[leftFront])/1440);
}

task main()
{

	//start of autonmous

	int orientFactor = -1; //assume the robot is facing backward
	if (SensorValue[sonar] >= 100){ //if wall is more than 1 meter behind, then the robot is facing backwards
		orientFactor = 1;
	}
	resetEncoders();
	servo[bucket] = 130;

	int distance1 = 24; //the distance from the starting point to the first bucket
	int distance2 = 0; //the distance from the first bucket to the turning point
	int distance3 = 0; //the distance from the turning point to the bottom of the ramp
	int distance4 = 0; //the distance from the bottom of the ramp to the parking point

	int bucketDistance11 = 0; //the distance from the first bucket to the first bucket (This will always be 0; it's just a placeholder variable for now.)
	int bucketDistance12 = 10; //the distance from the first bucket to the second bucket
	int bucketDistance13 = 29; //the distance from the first bucket to the third bucket
	int bucketDistance14 = 39; //the distance form the first bucket to the fourth bucket

	int turnRadius = 0; //the distance each center wheel must move to complete a 90-degree turn

	waitForStart();

	setMovementPower(100 * orientFactor, 0); //start moving forward
	while(distanceTraveled() < distance1){}
	resetEncoders();
	while(SensorValue[infrared] != 5){}
	setMovementPower(0,0);

	int targetPosition = 0;
	int minDistance = 1000;

	if (abs(distanceTraveled() - bucketDistance11) < minDistance){ //find the closest bucket
		minDistance = abs(distanceTraveled() - bucketDistance11);
		targetPosition = bucketDistance11;
	}
	if (abs(distanceTraveled() - bucketDistance12) < minDistance){
		minDistance = abs(distanceTraveled() - bucketDistance12);
		targetPosition = bucketDistance12;
	}
	if (abs(distanceTraveled() - bucketDistance13) < minDistance){
		minDistance = abs(distanceTraveled() - bucketDistance13);
		targetPosition = bucketDistance13;
	}
	if (abs(distanceTraveled() - bucketDistance14) < minDistance){
		minDistance = abs(distanceTraveled() - bucketDistance14);
		targetPosition = bucketDistance14;
	}

	if (targetPosition == bucketDistance11 || targetPosition == bucketDistance12) //move to the closest bucket
		targetPosition = targetPosition + 2;
	if (targetPosition == bucketDistance13 || targetPosition == bucketDistance14)
		targetPosition = targetPosition - 2;

	if (targetPosition < distanceTraveled()){
		setMovementPower(-100 * orientFactor,0);
		while (targetPosition < distanceTraveled()){}
		setMovementPower(0,0);
	}
	if (targetPosition > distanceTraveled()){
		setMovementPower(100 * orientFactor,0);
		while (targetPosition > distanceTraveled()){}
		setMovementPower(0,0);
	}

	motor[bucketRaise] = 100; //deposit the block
	wait1Msec(1500);
	motor[bucketRaise] = 0;
	wait10Msec(5);
	servo[bucket] = 210;
	wait1Msec(1000);
	servo[bucket] = 130;
	wait10Msec(50);
	motor[bucketRaise] = -100;
	wait1Msec(750);
	motor[bucketRaise] = 0;

	setMovementPower(-100 * orientFactor,0); //move to end of bucket row
	while (distanceTraveled() > 0){}
	resetEncoders();
	while (distanceTraveled() > distance2){};
	setMovementPower(0,0);
	turn90(-orientFactor);

	setMovementPower(-100 * orientFactor, 0); //move to bottom of ramp
	while (distanceTraveled() < distance3){};
	setMovementPower(0,0);
	turn90(-orientFactor);

	setMovementPower(-100 * orientFactor,0); //park on the ramp
	while (distanceTraveled() < distance4){};
	setMovementPower(0,0);

}
