
#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Motor,  port2,           leftFront,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           leftMiddle,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           rightFront,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           rightMiddle,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           liftLeftFront, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           liftRightFront, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           middleLeft, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           middleRight, tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     main.c                                                      */
/*    Author:     Henry Williams                                              */
/*    Created:    1 Dec 2016                                                  */
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

//////////////////////////////////GLOBAL VARIABLES
int liftRightSpeed = 0;
int liftLeftSpeed = 0;
int liftRightValue = 0;
int liftLeftValue = 0;
float leftTarget = 0;
float rightTarget = 0;


//////////////////////////////////INCLUDED FILES

#include "Vex_Competition_Includes.c"   //VEX REQUIRED FILE
#include "Tasks.c"          //RPM CALC // RPM CONTROL

///////////////////////////////////////////////////BEGIN PREAUTONOMOUS

void pre_auton()
{
	//#include "PreAuto.c"
	//bStopTasksBetweenModes = true;
}

///////////////////////////////////////////////////BEGIN AUTONOMOUS

task autonomous()
{
	//#include "Auto.c"
}

///////////////////////////////////////////////////BEGIN DRIVER CONTROL

task usercontrol()
{
	#include "DriverControl.c"
}
