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

#include "Tasks.c"          			//RPM CALC // RPM CONTROL

void move(int speed, int dir){
	// dir == 1 forward
	// dir == -1 backwards
	motor[leftDrive] = speed*dir;
	motor[leftDrive2] = speed*dir;
	motor[rightDrive] = speed*dir;
	motor[rightDrive2] = speed*dir;
}

void brake(int speed, int dir){
	// dir == 1 CCW
	// dir == -1 CW
	motor[leftDrive] = speed*(-dir);
	motor[leftDrive2] = speed*(-dir);
	motor[rightDrive] = speed*dir;
	motor[rightDrive2] = speed*dir;
}

void turn(int speed, int dir){
	// dir == 1 CCW
	// dir == -1 CW
	motor[leftDrive] = speed*(-dir);
	motor[leftDrive2] = speed*(-dir);
	motor[rightDrive] = speed*dir;
	motor[rightDrive2] = speed*dir;
}

void resetDrive (){
	motor[leftDrive] = 0;
	motor[leftDrive2] = 0;
	motor[rightDrive] = 0;
	motor[rightDrive2] = 0;
}

void resetEnc() {
	SensorValue[leftDriveEncoder] = 0;
	SensorValue[rightDriveEncoder] = 0;
	SensorValue[leftLiftEncoder] = 0;
	SensorValue[leftLiftEncoder] = 0;
}

void resetLiftEnc(){
	SensorValue[leftLiftEncoder] = 0;
	SensorValue[rightLiftEncoder] = 0;
}

void resetGrabber(){
	while(SensorValue[grabberEncoder] < -600) {
		motor[leftGrabber] = -40;
		motor[rightGrabber] = -40;
	}
	motor[leftGrabber] = 0;
	motor[rightGrabber] = 0;
}

void checkGrip(int type){
	int target;
	//type == 0 Stars
	if (type == 0) {
		target = -930;
	}
	//type == 1 Cube
	if (type == 1){
		target = -870;
	}

	if(SensorValue[grabberEncoder] > target) {
		motor[leftGrabber] = 40;
		motor[rightGrabber] = 40;
	} else {
		motor[leftGrabber] = 0;
		motor[rightGrabber] = 0;
	}
}

// void liftComp(int target){
// 	int correction = target - SensorValue[leftliftEncoder];

// 	if (SensorValue[leftLiftEncoder] < target) {
// 		motor[leftLift] = -1*(correction*correction);
// 		motor[leftLift2] = -1*(correction*correction);
// 		motor[rightLift] = -1*(correction*correction);
// 		motor[rightLift2] = -1*(correction*correction);
// 	}

// 	if (SensorValue[leftLiftEncoder] > target) {
// 		motor[leftLift] = correction*correction;
// 		motor[leftLift2] = correction*correction;
// 		motor[rightLift] = correction*correction;
// 		motor[rightLift2] = correction*correction;
// 	}
// }

bool liftSimple(int target){
	int correction = target - SensorValue[leftLiftEncoder];
	if (SensorValue[leftLiftEncoder] < target) {
		motor[leftLift] = -1*(correction*correction);
		motor[leftLift2] = -1*(correction*correction);
		motor[rightLift] = -1*(correction*correction);
		motor[rightLift2] = -1*(correction*correction);
		return false;
	}
	if (SensorValue[leftLiftEncoder] > target) {
		motor[leftLift] = correction*correction;
		motor[leftLift2] = correction*correction;
		motor[rightLift] = correction*correction;
		motor[rightLift2] = correction*correction;
		return true;
	}
	return false;
}

//Action 0 = pick up
//Action 1 = drop
int grabber(int action, int type){
	int target;
	//Pick up
	if (action == 0) {
		//type == 0 Stars
		if (type == 0) {
			target = -930;
		}
		//type == 1 Cube
		if (type == 1){
			target = -800;
		}
	}
	//Drop
	if (action == 1){
		target = -450;
	}
	return target;
}

task main() {
	clearTimer(T1);
	startTask(timeout);

	//Forward 27 inches
	while (SensorValue[leftDriveEncoder] <= 780){
		move(60, 1);
	}
	resetDrive();

	//CCW Turn 90 Degrees
	while (abs(SensorValue[in8]) < 600){
		turn(60, 1);
	}
	brake(30, -1);
	resetDrive();
	resetEnc();
	wait1Msec(300);

	//Forward 17 inches
	while (SensorValue[leftDriveEncoder] <= 580){
		move(60, 1);
	}
	resetDrive();

	//Grab cube
	while (SensorValue[grabberEncoder] > grabber(0, 1)) {
			motor[leftGrabber] = 127;
			motor[rightGrabber] = 127;
	}
	motor[leftGrabber] = 0;
	motor[rightGrabber] = 0;
	
	resetDrive();
	resetEnc();
	wait1Msec(300);

	//Backwards 17 inches
	while (abs(SensorValue[leftDriveEncoder]) <= 580) {
		move(60, -1);
		checkGrip(1);
	}
	resetDrive();
	resetEnc();
	wait1Msec(300);

	int turnTarget = (abs(SensorValue[in8])+250);
	//CCW Turn 90 Degrees
	while (abs(SensorValue[in8]) < turnTarget){
		turn(70, 1);
		checkGrip(1);
		if (SensorValue[leftLiftEncoder] < 20){
			motor[leftLift] = -90;
			motor[leftLift2] = -90;
			motor[rightLift] = -90;
			motor[rightLift2] = -90;
		} else {
			motor[leftLift] = 0;
			motor[leftLift2] = 0;
			motor[rightLift] = 0;
			motor[rightLift2] = 0;
		}
	}
	brake(30, -1);
	resetDrive();
	resetEnc();
	wait1Msec(400);

	while (liftSimple(145) == false) {
		move(40, -1);
		checkGrip(1);
	}

	resetDrive();
	wait1Msec(1000);

	//Drop cube
	while (SensorValue[grabberEncoder] < -700) {
		if (SensorValue[leftLiftEncoder] < 145){
			motor[leftLift] = -90;
			motor[leftLift2] = -90;
			motor[rightLift] = -90;
			motor[rightLift2] = -90;
		} else {
			motor[leftLift] = 90;
			motor[leftLift2] = 90;
			motor[rightLift] = 90;
			motor[rightLift2] = 90;
		}
		motor[leftGrabber] = -127;
		motor[rightGrabber] = -127;
	}
	
	motor[leftGrabber] = 50;
	motor[rightGrabber] = 50;
	motor[leftLift] = 90;
	motor[leftLift2] = 90;
	motor[rightLift] = 90;
	motor[rightLift2] = 90;
	wait1Msec(200);
	motor[leftGrabber] = 0;
	motor[rightGrabber] = 0;
	motor[leftLift] = 40;
	motor[leftLift2] = 40;
	motor[rightLift] = 40;
	motor[rightLift2] = 40;

	resetGrabber();
	wait1Msec(2500);
	motor[leftLift] = 0;
	motor[leftLift2] = 0;
	motor[rightLift] = 0;
	motor[rightLift2] = 0;
	resetLiftEnc();

	stopTask(autonomous);
}