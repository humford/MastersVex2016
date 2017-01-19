/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     DriverControl.c                                             */
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
	gyroTurningActive = true;
	encoderDrivingActive = true;

	MoveForDistance(DIST_TO_CUBE_Y);
	wait1Msec(500);

	gyroTarget = -900;
	wait1Msec(2000);

	MoveForDistance(DIST_TO_CUBE_X);
	wait1Msec(500);

	//GRAB CUBE

	//LIFT CUBE SLIGHTLY

	gyroTarget = 1800;
	wait1Msec(2000);

	MoveForDistance(DIST_TO_CUBE_X);
	wait1Msec(500);

	gyroTarget = -900;
	wait1Msec(2000);

	MoveForDistance(DIST_TO_FENCE_FROM_CUBE_Y);
	wait1Msec(500);

	//LIFT CUBE

	//LET GO OF CUBE

	encoderDrivingActive = false;
	gyroTurningActive = false;
}
