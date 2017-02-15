#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl5,  rightLiftEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  leftLiftEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl11, grabberEncoder, sensorQuadEncoder)
#pragma config(Sensor, I2C_1,  leftDriveEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  rightDriveEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           rightDrive2,   tmotorVex393HighSpeed_HBridge, openLoop, reversed, driveRight, encoderPort, I2C_2)
#pragma config(Motor,  port2,           rightDrive,    tmotorVex393HighSpeed_MC29, openLoop, reversed, driveRight, encoderPort, I2C_2)
#pragma config(Motor,  port3,           leftDrive,     tmotorVex393HighSpeed_MC29, openLoop, driveLeft, encoderPort, I2C_1)
#pragma config(Motor,  port4,           rightLift,     tmotorVex393_MC29, openLoop, reversed, encoderPort, dgtl5)
#pragma config(Motor,  port5,           leftLift,      tmotorVex393_MC29, openLoop, encoderPort, dgtl7)
#pragma config(Motor,  port6,           rightGrabber,  tmotorVex393_MC29, openLoop, encoderPort, dgtl11)
#pragma config(Motor,  port7,           leftGrabber,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           rightLift2,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           leftLift2,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          leftDrive2,    tmotorVex393HighSpeed_HBridge, openLoop, driveLeft, encoderPort, I2C_1)

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     AutoTasks.c                                                 */
/*    Author:     Henry Williams                                              */
/*    Created:    14 Feb 2017                                                 */
/*                                                                            */
/*    Copyright (c) Masters of Robotics 2017, All Rights Reserved             */
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

//////////////////////////////////GLOBAL VARIABLES
int liftRightSpeed = 0;
int liftLeftSpeed = 0;
int liftSpeed = 0;

int grabberRightSpeed = 0;
int grabberLeftSpeed = 0;
int grabberSpeed = 0;

float leftTarget = 0;
float rightTarget = 0;

bool encoderDrivingActive = false;
bool gyroTurningActive = false;
float gyroTarget = 0, speed = 0;

#include "Tasks.c"          			//RPM CALC // RPM CONTROL
#include "AutoTasks.c"
#include "Auto.c"

task main() {
		//Reconfigure Analog Port 8 as a Gyro sensor and allow time for ROBOTC to calibrate it
		SensorType[in8] = sensorNone;
		wait1Msec(1000);
		SensorType[in8] = sensorGyro;
		wait1Msec(2000);

		//Reset sensor
		SensorValue[in8] = 0;
		wait1Msec(1000);

		//Reset lift encoders
		SensorValue[leftLiftEncoder] = 0;
		SensorValue[rightLiftEncoder] = 0;

		startTask(autonomous);
}
