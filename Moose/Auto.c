/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     Auto.c                                                      */
/*    Author:     Henry Williams                                              */
/*    Created:    14 Jan 2017                                                 */
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

task autonomous()
{
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
