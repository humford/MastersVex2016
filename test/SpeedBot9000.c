#pragma config(Sensor, in1,    LiftPos,        sensorNone)
#pragma config(Sensor, in2,    LTracker,       sensorLineFollower)
#pragma config(Sensor, in3,    MTracker,       sensorLineFollower)
#pragma config(Sensor, in4,    RTracker,       sensorLineFollower)
#pragma config(Sensor, in5,    CubeDetector,   sensorLineFollower)
#pragma config(Sensor, in8,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  ConveyorPos,    sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  LowSonar,       sensorSONAR_cm)
#pragma config(Sensor, dgtl5,  HighSonar,      sensorSONAR_cm)
#pragma config(Sensor, dgtl10, GreenLED,       sensorLEDtoVCC)
#pragma config(Sensor, dgtl11, YellowLED,      sensorLEDtoVCC)
#pragma config(Sensor, dgtl12, RedLED,         sensorLEDtoVCC)
#pragma config(Motor,  port1,           BRDrive,       tmotorVex393, openLoop)
#pragma config(Motor,  port2,           MRDrive,       tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port3,           FRDrive,       tmotorVex393, openLoop)
#pragma config(Motor,  port4,           RLift,         tmotorVex393, openLoop)
#pragma config(Motor,  port5,           Conveyer,      tmotorVex393HighSpeed, openLoop, reversed)
#pragma config(Motor,  port7,           LLift,         tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port8,           FLDrive,       tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port9,           MLDrive,       tmotorVex393, openLoop)
#pragma config(Motor,  port10,          BLDrive,       tmotorVex393, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

#define cutoff 1700
#define LIFT_MAX 3000
#define LIFT_MIN 1100

#define CUBE_MODE 1
#define BAR_MODE 0
#define OBSTICAL_MODE -1
#define BLUE -1
#define RED 1
#define LEFT_BUTTON 1
#define CENTER_BUTTON 2
#define RIGHT_BUTTON 4


float leftTarget = 0, rightTarget = 0;
task Set_Drive()
{
	int leftCur = 0, rightCur = 0, leftError = 0, rightError = 0;
	int Time_Step = 20;
	int Power_Step = 10;
	while(true)
	{
		leftError = leftTarget - leftCur;
		rightError = rightTarget - rightCur;

		if(abs(leftError) <= Power_Step) leftCur = leftTarget;
		else leftCur += (leftError > 0) ? Power_Step : -Power_Step;

		if(abs(rightError) <= Power_Step) rightCur = rightTarget;
		else rightCur += (rightError > 0) ? Power_Step : -Power_Step;

		motor[FRDrive] = rightCur;
		motor[MRDrive] = rightCur;
		motor[BRDrive] = rightCur;

		motor[FLDrive] = leftCur;
		motor[MLDrive] = leftCur;
		motor[BLDrive] = leftCur;

		wait1Msec(Time_Step);
	}
}

void DrivePower(float left, float right)
{
	leftTarget = left;
	rightTarget = right;
}


bool gyroTurningActive = false;
float gyroTarget = 0, speed = 0;
task gyro_Drive()
{
	float kp = 0.25, ki = 0.0, kd = 35;
	float error = 0, last_error = 0, integral = 0, derivative = 0, power = 0;
	float time_step = 50;

	float max_power = 70;
	float integral_max_power = 30;
	float integral_window = 100;

	while(true)
	{
		if(gyroTurningActive)
		{
			last_error = error;
			error = gyroTarget - SensorValue[gyro];
			derivative = (error - last_error)/time_step;

			if(abs(error) < integral_window)integral += error * time_step;
			else integral = 0;

			if(integral * ki > integral_max_power) integral = integral_max_power / ki;
			if(integral * ki < - integral_max_power) integral = - integral_max_power / ki;

			power = kp*error + ki * integral + kd * derivative;

			if(power > max_power) power = max_power;
			if(power < - max_power) power = - max_power;

			DrivePower(speed - power, speed + power);
		}
		else
		{
			error = 0;
			last_error = 0;
			integral = 0;
			derivative = 0;
			power = 0;
		}
		wait1Msec(time_step);
	}
}


int conveyorTarget = 0;
task Move_Conveyor()
{
	float kp = 0.9, kd = 30;
	float error = 0, last_error = 0, derivative = 0, power = 0;
	float time_step = 50;

	float max_power = 127;

	while(true)
	{
		last_error = error;
		error = conveyorTarget - SensorValue[ConveyorPos];
		derivative = (error - last_error)/time_step;
		power = kp*error + kd * derivative;

		if(power > max_power) power = max_power;
		if(power < - max_power) power = - max_power;

		motor[Conveyer] = power;
		wait1Msec(time_step);
	}
}

int liftTarget = LIFT_MAX;
task Lift_Control()
{
	float kp = 0.1, kd = 10;
	float error = 0, last_error = 0, derivative = 0, power = 0;
	float time_step = 100;

	float max_power = 127;

	while(true)
	{
		last_error = error;
		error = liftTarget - SensorValue[LiftPos];
		derivative = (error - last_error)/time_step;
		power = kp*error + kd * derivative;

		if(power > max_power) power = max_power;
		if(power < - max_power) power = - max_power;

		motor[LLift] = power;
		motor[RLift] = power;
		wait1Msec(time_step);
	}
}


void trackLine(int speed, int turn_speed)
{
		if(SensorValue[LTracker] < cutoff)
		{
			DrivePower(turn_speed, speed);
		}
		else if(SensorValue[MTracker] < cutoff)
		{
			DrivePower(speed, speed);
		}
		else if(SensorValue[RTracker] < cutoff)
		{
			DrivePower(speed, turn_speed);
		}
		else
		{
			DrivePower(0, 0);
		}
}


void waitUntilSonar(int dist, int mode)
{
	if(mode == CUBE_MODE)
		while(SensorValue[LowSonar] > dist || SensorValue[LowSonar] == -1);
	else if(mode == BAR_MODE)
		while(SensorValue[HighSonar] > dist || SensorValue[HighSonar] == -1);
	else if(mode == OBSTICAL_MODE)
		while((SensorValue[LowSonar] > dist || SensorValue[LowSonar] == -1) && (SensorValue[HighSonar] > dist || SensorValue[HighSonar] == -1));
}

void moveToDistance(int dist, float precision)
{
	float kp = 1.5, ki = 0.02, kd = 500;
	float error = 0, last_error = 0, integral = 0, derivative = 0;
	float time_step = 100;

	float max_speed = 70;
	float integral_max_power = 20;
	float integral_window = 20;

	error = dist - SensorValue[HighSonar];
	while(abs(error) > precision || abs(derivative) > 0)
	{
		last_error = error;
		error = dist - SensorValue[HighSonar];
		derivative = (error - last_error)/time_step;

		if(abs(error) < integral_window)integral += error * time_step;
		else integral = 0;

		if(integral * ki > integral_max_power) integral = integral_max_power / ki;
		if(integral * ki < - integral_max_power) integral = - integral_max_power / ki;

		speed = -(kp*error + ki * integral + kd * derivative);

		if(speed > max_speed) speed = max_speed;
		if(speed < - max_speed) speed = - max_speed;

		wait1Msec(time_step);
	}
	speed = 0;
}



/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////
int autonomous_side = 0;

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = false;

	bLCDBacklight = true;                                    // Turn on LCD Backlight
	string mainBattery;

	for(int i = 0; i < 10; i ++)                                                        // An infinite loop to keep the program running until you terminate it
	{
		clearLCDLine(0);                                            // Clear line 1 (0) of the LCD
		clearLCDLine(1);                                            // Clear line 2 (1) of the LCD

		//Display the Primary Robot battery voltage
		displayLCDString(0, 0, "Primary: ");
		sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
		displayNextLCDString(mainBattery);

		//Short delay for the LCD refresh rate
		wait1Msec(100);
	}


	while(vrDisabled && nLCDButtons != CENTER_BUTTON)
	{
		clearLCDLine(0);
		clearLCDLine(1);
		switch(autonomous_side)
		{
			case 0:
				displayLCDString(0, 2, "Select Side:");
				break;
			case BLUE:
				displayLCDString(0, 1, "BLUE Selected");
				break;
			case RED:
				displayLCDString(0, 2, "RED Selected");
				break;
		}

		if(nLCDButtons == LEFT_BUTTON)autonomous_side = BLUE;
		else if(nLCDButtons == RIGHT_BUTTON)autonomous_side = RED;
		displayLCDString(1, 0, "BLUE         RED");
		wait1Msec(100);
	}

	SensorValue[ConveyorPos] = 0;
	clearLCDLine(0);
	clearLCDLine(1);
	displayLCDString(0, 0, "Calibrating Gyro");
	SensorType[gyro] = sensorNone;
	wait1Msec(250);
	displayLCDString(1, 2, "*");
	wait1Msec(250);
	displayLCDString(1, 2, "**");
	wait1Msec(250);
	displayLCDString(1, 2, "***");
	wait1Msec(250);
	displayLCDString(1, 2, "****");
	SensorType[gyro] = sensorGyro;
	wait1Msec(250);
	displayLCDString(1, 2, "*****");
	wait1Msec(250);
	displayLCDString(1, 2, "******");
	wait1Msec(250);
	displayLCDString(1, 2, "*******");
	wait1Msec(250);
	displayLCDString(1, 2, "********");
	wait1Msec(250);
	displayLCDString(1, 2, "*********");
	wait1Msec(250);
	displayLCDString(1, 2, "**********");
	wait1Msec(250);
	displayLCDString(1, 2, "***********");
	wait1Msec(250);
	displayLCDString(1, 2, "************");

	clearLCDLine(0);
	clearLCDLine(1);
	displayLCDString(0, 0, "Gyro Calibrated!");
	wait1Msec(1000);

	StartTask(Lift_Control);
	StartTask(Move_Conveyor);
	StartTask(Set_Drive);
	StartTask(gyro_Drive);
}


/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task Make_Stack()
{
	liftTarget = LIFT_MIN + 200;
	wait1Msec(1500);
	conveyorTarget = 400;
	wait1Msec(1000);
	liftTarget = LIFT_MAX;
	wait1Msec(1000);
	conveyorTarget = 0;
}

task Dump()
{
	liftTarget = LIFT_MIN + 200;
	wait1Msec(1500);
	conveyorTarget = 0;
	wait1Msec(2000);
	liftTarget = LIFT_MAX;
	wait1Msec(1000);
}


void blue_auto()
{
	speed = 100;
	waitUntilSonar(50, CUBE_MODE);
	speed = 70;
	waitUntilSonar(5, CUBE_MODE);
	conveyorTarget = 500;
	wait1Msec(500);
	speed = -100;
	wait1Msec(1500);

	speed = 0;
	wait1Msec(1000);
	gyroTarget = -950;
	wait1Msec(2000);
	speed = -70;
	moveToDistance(180, 5);
	speed = 0;
	wait1Msec(1000);

	gyroTarget = 0;
	wait1Msec(2000);
	speed = 60;
	waitUntilSonar(5, CUBE_MODE);
	conveyorTarget = 1000;
	wait1Msec(500);
	speed = -70;
	wait1Msec(1000);
	speed = 0;
	wait1Msec(1000);

	gyroTarget = 1300;
	wait1Msec(3000);
	speed = 100;
	waitUntilSonar(100, BAR_MODE);
	speed = 50;
	waitUntilSonar(10, BAR_MODE);
	speed = 0;
	wait1Msec(500);
	if(SensorValue[CubeDetector] < 1500)
		StartTask(Make_Stack);
	else
		StartTask(Dump);
	wait1Msec(3000);
	speed = -50;
	wait1Msec(1000);
	speed = 0;
	wait1Msec(2000);
}

void red_auto()
{
	speed = 100;
	waitUntilSonar(50, CUBE_MODE);
	speed = 70;
	waitUntilSonar(5, CUBE_MODE);
	conveyorTarget = 500;
	wait1Msec(500);
	speed = -100;
	wait1Msec(1500);

	speed = 0;
	wait1Msec(1000);
	gyroTarget = 950;
	wait1Msec(2000);
	speed = -70;
	moveToDistance(180, 5);
	speed = 0;
	wait1Msec(1000);

	gyroTarget = 0;
	wait1Msec(2000);
	speed = 60;
	waitUntilSonar(5, CUBE_MODE);
	conveyorTarget = 1000;
	wait1Msec(500);
	speed = -70;
	wait1Msec(1000);
	speed = 0;
	wait1Msec(1000);

	gyroTarget = -1300;
	wait1Msec(3000);
	speed = 100;
	waitUntilSonar(100, BAR_MODE);
	speed = 50;
	waitUntilSonar(10, BAR_MODE);
	speed = 0;
	wait1Msec(500);
	if(SensorValue[CubeDetector] < 1500)
		StartTask(Make_Stack);
	else
		StartTask(Dump);
	wait1Msec(3000);
	speed = -50;
	wait1Msec(1000);
	speed = 0;
	wait1Msec(2000);
}


task autonomous()
{
	gyroTurningActive = true;
	if(autonomous_side == BLUE) blue_auto();
	else if(autonomous_side == RED) red_auto();
	gyroTurningActive = false;
}

//SOUND PLAYER HEADERS

void QueueSoundFileAndWait(const string Filename, long WaitMs);
void PlaySoundFileAndWait(const string Filename);
task play_Nyan();

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task LCD_display()
{
	string s;
	while(true)
	{
		clearLCDLine(0);
		clearLCDLine(1);
		sprintf(s, "H:%3dcm  L:%3dcm", SensorValue[HighSonar], SensorValue[LowSonar]); //Build the value to be displayed
		displayLCDString(0, 0,s);

		sprintf(s, "gyro: %4d", SensorValue[gyro]); //Build the value to be displayed
		displayLCDString(1, 0, s);
		wait1Msec(100);
	}
}

task usercontrol()
{
	StartTask(LCD_display);
	StartTask(play_Nyan);
	bool pressed = false;
	gyroTurningActive = false; //MAKE FALSE

	while (true)
	{
	  DrivePower(vexRT(Ch3)+vexRT(Ch4), vexRT(Ch3)-vexRT(Ch4)); //UNCOMMENT!!!!

	  liftTarget -= vexRT(Btn5U) - vexRT(Btn5D);
	  liftTarget = liftTarget > LIFT_MAX ? LIFT_MAX : liftTarget;
	  liftTarget = liftTarget < LIFT_MIN ? LIFT_MIN : liftTarget;

	  if(!pressed && vexRT(Btn8U) && conveyorTarget < 1000)
	  {
	  	conveyorTarget += 500;
	  	pressed = true;
		}
		if(!pressed && vexRT(Btn8D) && conveyorTarget > 0)
	  {
	  	conveyorTarget -= 500;
	  	pressed = true;
		}
		if(!vexRT(Btn8U) && !vexRT(Btn8D))pressed = false;

	  if(vexRT(Btn7U))
	  {
	  	StartTask(Make_Stack);
	  }

/*	  if(vexRT(Btn7L))  //REMOVE
	  {
	  	blue_auto();
	  }

	  if(vexRT(Btn7R))  //REMOVE
	  {
	  	red_auto();
	  }

	  while(vexRT(Btn7D)) //REMOVE
		{
			trackLine(50,10);
		}*/

		SensorValue[GreenLED] = (SensorValue[LowSonar] <= 50 && SensorValue[LowSonar] > 20 || SensorValue[LowSonar] == -1);
		SensorValue[YellowLED] = (SensorValue[LowSonar] <= 20 && SensorValue[LowSonar] > 10 || SensorValue[LowSonar] == -1);
		SensorValue[RedLED] = (SensorValue[LowSonar] <= 10 || SensorValue[LowSonar] == -1);
	}
}


/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Sound Controll Functions
//
/////////////////////////////////////////////////////////////////////////////////////////

void QueueSoundFileAndWait(const string Filename, long WaitMs)
{
  PlaySoundFile(Filename);
  long StartTime = nPgmTime;
  while (nPgmTime - StartTime < WaitMs) {}
}

void PlaySoundFileAndWait(const string Filename)
{
  PlaySoundFile(Filename);
  while (bSoundActive) {}
}

task play_Nyan()
{
	while(true)
	{
  	nVolume = 100;
  	PlaySoundFileAndWait("BeginMusicalSeq.wav");
  	PlaySoundFile("NyanIntro.wav");
  	QueueSoundFileAndWait("Nyan1.wav", 3452);
  	QueueSoundFileAndWait("Nyan1.wav", 6905);
  	QueueSoundFileAndWait("Nyan2.wav", 6905);
  	QueueSoundFileAndWait("Nyan2.wav", 6905);
  	QueueSoundFileAndWait("Nyan1.wav", 6905);
  	QueueSoundFileAndWait("Nyan1.wav", 6905);
  	QueueSoundFileAndWait("Nyan2.wav", 6905);
  	QueueSoundFileAndWait("Nyan2.wav", 6905);
 	 	QueueSoundFileAndWait("Nyan1.wav", 6905);
  	nVolume = 90;
  	QueueSoundFileAndWait("Nyan1.wav", 6905);
  	QueueSoundFileAndWait("Nyan2.wav", 6905);
  	nVolume = 80;
  	QueueSoundFileAndWait("NyanEnding.wav", 6905);
  	nVolume = 100;
  	wait1Msec(8000);
  }
}