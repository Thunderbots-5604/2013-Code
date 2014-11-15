static const float irDistances[4] = {14.5, 10, 15.5, 10};
static float irBackDistances[4] = {irDistances[0]-7,-4,0,-3.5};
static const short irValues[4] = {5, 5, 4, 4};

bool testing = false;
bool defend_ramp = false;
bool liftedUp = false;
bool foundCrate = false;
bool liftIsDown = false;
bool matchHasStarted = false;

static const int NXTBUTTONPRESS = 325;
static const int UPRAMPTIME = 2000;
static const int UPRAMPDIST = 27;
int adjust = 20;
int dir;
int leftadjust;
int rightadjust;

static const short liftUpTime = 1800;
static const short liftDownTime = 1300;
static const short rampLineUpDistance = 30;
static short crateVal = 0;
static short power;

static void resetEncoders();
static void initializeRobot();
static void move(int speed);
static void moveForward(float power);
static void dumpCube();
static void turn(float power);
static void turn90(bool right);
static void turn45(bool right);
static void swingLeft(bool forward);

static float distanceTravelled();
static float encoderDifference();
static const float in = 360/PI;
static float distToBucket;

task waitUntilStart();
task nxtDebugger();
task liftUp();
task liftDown();

task waitUntilStart()
{
	waitForStart();
	matchHasStarted = true;
	EndTimeSlice();
}

task nxtDebugger(){
	while (true){
		nxtDisplayCenteredTextLine(0, "%d", distanceTravelled());
		nxtDisplayCenteredTextLine(1, "%d", nMotorEncoder[Left]);
		nxtDisplayCenteredTextLine(2, "%d", nMotorEncoder[Right]);
		nxtDisplayCenteredTextLine(3, "%d", SensorValue[infrared]);
		nxtDisplayCenteredTextLine(4, "%d", crateVal);
		wait1Msec(10);
	}
	EndTimeSlice();
}

task liftUp(){
	ClearTimer(T4);
	motor[Lift1] = 100;
	motor[Lift2] = 100;
	while (time1[T4] <= liftUpTime){
		motor[Lift1] = 100;
		motor[Lift2] = 100;
		servo[pin] = 0;
	}
	motor[Lift1] = 0;
	motor[Lift2] = 0;
	motor[Flag] = 0;
	liftedUp = true;

	EndTimeSlice();
}

task liftDown(){
	motor[Lift1] = -100;
	motor[Lift2] = -100;
	wait1Msec(liftDownTime);

	motor[Lift1] = 0;
	motor[Lift2] = 0;
	liftIsDown = true;

	EndTimeSlice();
}

void brake(int waitTime = 0){
	ClearTimer(T3);
	move(0);
	wait1Msec(waitTime*1000);
}

void resetEncoders(){
	nMotorEncoder[Left] = 0;
	nMotorEncoder[Right] = 0;
}

void initializeRobot(){
	resetEncoders();
	brake();
	motor[Lift1] = 0;
	motor[Lift2] = 0;
	motor[Sweep] = 0;
	motor[Flag] = 0;
	servo[bucket] = 102;
}

void move(int speed)
{
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

void moveForward(float power){
	motor[Left] = power;
	motor[Left2] = power;
	motor[Right] = power;
	motor[Right2] = power;
}

void adjust12(){
	moveForward(25);
	while (distanceTravelled() <= 2){}
	brake();
}

void adjust34(){
	moveForward(-25);
	while (distanceTravelled() <= 2){}
	brake();
}

void dumpCube(){
	int servoMovement = 50;
	wait1Msec(50);
	servo[bucket] = 102;
	wait1Msec(50);
	servo[bucket] = 102 + (servoMovement);
	wait1Msec(2000);
	servo[bucket] = 102;
	wait1Msec(50);
}

void turn(float power){ //right is positive, left is negative
	motor[Left] = power;
	motor[Left2] = power;
	motor[Right] = -power;
	motor[Right2] = -power;
}

void turn90(bool right){ //true is right, false is left

	turn45(right);
	turn45(right);
}

void turn45(bool right){
	if (right){
		power = 100;
	}
	else{
		power = -100;
	}
	resetEncoders();
	motor[Left] = power;
	motor[Left2] = power;
	motor[Right] = -power;
	motor[Right2] = -power;
	while ((abs(nMotorEncoder[Left]) + abs(nMotorEncoder[Right]))/2 < 645)
		wait1Msec(1);
	brake();
}

void swingLeft(bool forward){
	short direction = 1;
	if (!forward)
		direction = -1;
	motor[Left] = 100*direction;
	motor[Left2] = 100*direction;
}

float distanceTravelled(){
	return((abs(nMotorEncoder[Left]+nMotorEncoder[Right])/2)/in);
}

float encoderDifference(){
	float left = nMotorEncoder[Left];
	float right = nMotorEncoder[Right];
	return(abs(left-right));
}
