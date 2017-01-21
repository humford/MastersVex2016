#pragma config(Sensor, dgtl1,  rightDriveEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftDriveEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  rightLiftEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  leftLiftEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl11, grabberEncoder, sensorQuadEncoder)
#pragma config(Motor,  port1,           rightDrive2,   tmotorVex393TurboSpeed_HBridge, openLoop, reversed, driveRight, encoderPort, dgtl1)
#pragma config(Motor,  port2,           rightDrive,    tmotorVex393TurboSpeed_MC29, openLoop, reversed, driveRight, encoderPort, dgtl1)
#pragma config(Motor,  port3,           leftDrive,     tmotorVex393TurboSpeed_MC29, openLoop, driveLeft, encoderPort, dgtl3)
#pragma config(Motor,  port4,           rightLift,     tmotorVex393_MC29, openLoop, reversed, encoderPort, dgtl5)
#pragma config(Motor,  port5,           leftLift,      tmotorVex393_MC29, openLoop, encoderPort, dgtl7)
#pragma config(Motor,  port6,           rightGrabber,  tmotorVex393_MC29, openLoop, encoderPort, dgtl11)
#pragma config(Motor,  port7,           leftGrabber,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           rightLift2,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           leftLift2,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          leftDrive2,    tmotorVex393TurboSpeed_HBridge, openLoop, driveLeft, encoderPort, dgtl3)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     main.c                                                      */
/*    Author:     Henry Williams                                              */
/*    Created:    14 Jan 2017                                                 */
/*                                                                            */
/*    Copyright (c) Masters of Robotics 2016, All Rights Reserved             */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Licensed under the Apache License, Version 2.0 (the "License");         */
/*    you may not use this file except in compliance with the License.        */
/*    You may obtain a copy of the License at                                 */
/*                                                                            */
/*    http://www.apache.org/licenses/LICENSE-2.0                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(120)

///////////////////////////ENABLE DEBUG MODE (IF TRUE SKIPS AUTO SELECTION AND RUNS DEBUG AUTO ONLY)
#define DEBUG 0

#define LEFT_BUTTON 1
#define CENTER_BUTTON 2
#define RIGHT_BUTTON 4

#define DRIVE_WHEEL_CIR 12.56637 //circumfrence of drive wheel in inches
#define VAL_PER_ROTATION 360

#define DIST_TO_CUBE_Y 737
#define DIST_TO_CUBE_X 466
#define DIST_TO_FENCE_FROM_CUBE_Y -840
#define CLAW_CUBE_GRAB -865
#define CLAW_CUBE_DROP -660

#define LIFT_MAX 1500 /**FUCKING SET THIS VALUE YOU LAZY WHORES**/
#define LIFT_MIN 550 /**FUCKING SET THIS VALUE YOU LAZY WHORES**/

//////////////////////////////////GLOBAL VARIABLES
int liftRightSpeed = 0;
int liftLeftSpeed = 0;
int liftSpeed = 0;
int liftRightValue = 0;
int liftLeftValue = 0;

int grabberRightSpeed = 0;
int grabberLeftSpeed = 0;
int grabberSpeed = 0;

float leftTarget = 0;
float rightTarget = 0;
float liftTarget = 0;

bool gyroTurningActive = false;
float gyroTarget = 0, speed = 0;

bool encoderDrivingActive = false;

//////////////////////////////////INCLUDED FILES

#include "Vex_Competition_Includes.c"   //VEX REQUIRED FILE
#include "Tasks.c"          //RPM CALC // RPM CONTROL

///////////////////////////////////////////////////BEGIN PREAUTONOMOUS

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = false;

  //DISPLAY BATTERY LEVEL

	//bLCDBacklight = true;                                    // Turn on LCD Backlight

  	//SELECT MODE
  	/*
	while(vrDisabled && nLCDButtons != CENTER_BUTTON)
	{
		clearLCDLine(0); //heil hitler
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
	}*/

  //CALIBRATE GYRO

		SensorType[in8] = sensorNone;
  wait1Msec(1000);
  //Reconfigure Analog Port 8 as a Gyro sensor and allow time for ROBOTC to calibrate it
  SensorType[in8] = sensorGyro;
  wait1Msec(2000);
	SensorValue[in8] = 0;
	wait1Msec(1000);

	//startTask(Lift_Control);
	startTask(Set_Drive);
	startTask(gyro_Drive);
}

///////////////////////////////////////////////////BEGIN AUTONOMOUS
#include "Auto.c"

///////////////////////////////////////////////////BEGIN DRIVER CONTROL
#include "DriverControl.c"
}
