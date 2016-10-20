#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port2,           leftFB,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           leftMiddle,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           rightFB,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           rightMiddle,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           forkLeftFront, tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port7,           forkLeftBack,  tmotorVex393_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port8,           forkRightFront, tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_4)
#pragma config(Motor,  port9,           forkRightBack, tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_3)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////
void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
  // .....................................................................................
  // Insert user code here.
  // .....................................................................................
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////


// CONVENTION - ALL BRACKET CONTAINED CODE COMES ON THE LINE BELOW
task usercontrol()
{
	resetMotorEncoder(forkLeftFront);
  resetMotorEncoder(forkRightFront);

	int forkSpeed = 0;
	int forkRight = 0;
	int forkLeft = 0;
	while (true)
	{
		int fork = ( getMotorEncoder(forkLeftFront) - getMotorEncoder(forkRightFront) ) / 2;

		forkSpeed = 0;

		if (vexRT[Btn6D] == 1)
    {
      forkSpeed = 127;
    }

    if (vexRT[Btn6U] == 1)
    {
      forkSpeed = -127;
    }

    forkRight = forkSpeed
		forkLeft = forkSpeed
	
		if (vexRT[Btn7D] == 1)
		{
			forkRight = 127
		}
		
		if (vexRT[Btn7U] == 1)
		{
			forkRight = -127
		}
		
		if (vexRT[Btn6D] == 1)
		{
			forkLeft = 127
		}
		
		if (vexRT[Btn6U] == 1)
		{
			forkLeft = -127
		}
    
 		motor(forkRightFront) = forkRight;
 		motor(forkRightBack) = forkRight;
 		motor(forkLeftFront) = forkLeft;
 		motor(forkLeftBack) = forkLeft;

		//Right joystick controlls the robots movement forward and backward and turning
		int rightSide = vexRT[Ch2] - vexRT[Ch1];
		motor(rightFB) = rightSide;
	  motor(rightMiddle) = rightSide;

	  //Left joystick controlls the robots movement forward and backward and straifing
	  int leftSide = vexRT[Ch2] + vexRT[Ch1];
		motor(leftFB) = leftSide;
	  motor(leftMiddle) = leftSide;
  }
}
