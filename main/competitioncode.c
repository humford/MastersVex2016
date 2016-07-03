#pragma config(Motor,  port2,           rightBackWheel, tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port3,           leftFrontWheel, tmotorVex393, openLoop)
#pragma config(Motor,  port4,           leftBackWheel, tmotorVex393, openLoop)
#pragma config(Motor,  port5,           rightFrontWheel, tmotorVex393, openLoop, reversed)
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
	while (true)
	{
		//Wheels

		//Right joystick controlls the robots movement forward and backward and turning
	  //Left joystick controlls the robots movement forward and backward and straifing
	  motor(rightFrontWheel) = vexRT[Ch3] - vexRT[Ch4] + vexRT[Ch2] - vexRT[Ch1];
	  motor(leftFrontWheel) = vexRT[Ch3] + vexRT[Ch4] + vexRT[Ch2] + vexRT[Ch1];
	  motor(rightBackWheel) = vexRT[Ch3] + vexRT[Ch4] + vexRT[Ch2] - vexRT[Ch1];
	  motor(leftBackWheel) = vexRT[Ch3] - vexRT[Ch4] + vexRT[Ch2] + vexRT[Ch1];
  }
}
