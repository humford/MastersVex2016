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
	startTask(Set_Drive);
	startTask(Gyro_Drive);

	gyroTurningActive = true;

	clearTimer(T1);
	startTask(timeout);

	//Forward 27 inches
	move(780, 60, false)
	
	//CCW Turn 90 Degrees
	gyroTarget = -600;
	wait1Msec(2000);

	//Forward 17 inches
	move(580, 60, false)

	//Grab cube
	while (SensorValue[grabberEncoder] > grabber(0, 1)) {
			motor[leftGrabber] = 127;
			motor[rightGrabber] = 127;
	}
	motor[leftGrabber] = 0;
	motor[rightGrabber] = 0;
	resetEnc();
	wait1Msec(300);

	//Backwards 17 inches
	move(580, -60, true)

	//CCW Turn Degrees
	gyroTarget = -850;
	while (abs(SensorValue[in8]) < 850){
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
	resetEnc();
	wait1Msec(400);

	while (liftSimple(145) == false) {
		speed = -40;
		checkGrip(1);
	}
	speed = 0;
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

	gyroTurningActive = false;

	stopTask(Gyro_Drive);
	stopTask(Set_Drive);
	stopTask(autonomous);
}
