#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(Sensor, in2,    potRight,       sensorPotentiometer)
#pragma config(Sensor, in3,    gyro,           sensorGyro)
#pragma config(Sensor, in4,    potLeft,        sensorPotentiometer)
#pragma config(Motor,  port1,           conveyMotor,   tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           leftFront,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           leftBack,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           rightFront,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           rightBack,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           liftLeft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           liftRight,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           intakeLeft,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           intakeRight,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          strafeMotor,   tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard

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

#define LEFT_BUTTON 1
#define CENTER_BUTTON 2
#define RIGHT_BUTTON 4


#define LIFT_MAX 1500 /**FUCKING SET THIS VALUE YOU LAZY WHORES**/
#define LIFT_MIN 550 /**FUCKING SET THIS VALUE YOU LAZY WHORES**/

//////////////////////////////////GLOBAL VARIABLES
int liftSpeed = 0;
int liftRightSpeed = 0;
int liftLeftSpeed = 0;
int liftRightValue = 0;
int liftLeftValue = 0;
float leftTarget = 0;
float rightTarget = 0;
float liftTarget = 0;


bool gyroTurningActive = false;
float gyroTarget = 0, speed = 0;


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
		//while(vrDisabled && nLCDButtons != CENTER_BUTTON);
		wait1Msec(100);
	}

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

	startTask(Lift_Control);
	startTask(Set_Drive);
	startTask(gyro_Drive);
}

///////////////////////////////////////////////////BEGIN AUTONOMOUS
#include "Auto.c"

///////////////////////////////////////////////////BEGIN DRIVER CONTROL
#include "DriverControl.c"
