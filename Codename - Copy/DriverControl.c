/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     DriverControl.c                                             */
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

task usercontrol()
{
  driverControl = true;
  encoderDrivingActive = true;

	while (true)
	{

    if(vexRT[Btn6U])
    {
    	//liftTarget = LIFT_MAX;
    	liftSpeed = -127;
    }
    else if(vexRT[Btn6D])
    {
    	//liftTarget = LIFT_MIN;
    	liftSpeed = 127;
    }
    else if(!vexRT[Btn6U] && !vexRT[Btn6D])
    {
    	//liftTarget = LIFT_MIN;
    	liftSpeed = 0;
    }

    if (vexRT[Btn5U] == 1)
    {
    	grabberSpeed = 127;
    }
    else if (vexRT[Btn5D] == 1)
    {
    	grabberSpeed = -127;
    }
    else
    {
     	grabberSpeed = 0;
    }

    grabberRightSpeed = grabberSpeed;
    grabberLeftSpeed = grabberSpeed;
    motor[rightGrabber] = grabberRightSpeed;
    motor[leftGrabber] = grabberLeftSpeed;

    liftRightSpeed = liftSpeed;
    liftLeftSpeed = liftSpeed;
    motor[rightLift] = liftRightSpeed;
    motor[leftLift] = liftLeftSpeed;
    motor[rightLift2] = liftRightSpeed;
    motor[leftLift2] = liftLeftSpeed;

    DrivePower(vexRT[Ch3] + vexRT[Ch1], vexRT[Ch3] - vexRT[Ch1]);

    if(vexRT[Btn7L])
    {
    	MoveForDistance(DIST_TO_CUBE_Y);
    }

    if(vexRT[Btn7R])
    {
    	gyroTurningActive = true;
	encoderDrivingActive = true;

	MoveForDistance(DIST_TO_CUBE_Y);

	gyroTarget = -950;
	wait1Msec(2000);

	MoveForDistance(DIST_TO_CUBE_X);

	//GRAB CUBE
	motor[rightGrabber] = -100;
	motor[leftGrabber] = -100;
	wait1Msec(1500);
	motor[rightGrabber] = 0;
	motor[leftGrabber] = 0;

	//LIFT CUBE SLIGHTLY
	motor[rightLift] = -50;
	motor[leftLift] = -50;

	gyroTarget = 1900;
	wait1Msec(2000);

	MoveForDistance(DIST_TO_CUBE_X);

	gyroTarget = -950;
	wait1Msec(2000);

	MoveForDistance(DIST_TO_FENCE_FROM_CUBE_Y);

	//LIFT CUBE
	motor[rightLift] = -127;
	motor[leftLift] = -127;
	wait1Msec(1500);
	motor[rightLift] = 0;
	motor[leftLift] = 0;

	//LET GO OF CUBE
	motor[rightGrabber] = 100;
	motor[leftGrabber] = 100;
	wait1Msec(1500);
	motor[rightGrabber] = 0;
	motor[leftGrabber] = 0;

	encoderDrivingActive = false;
	gyroTurningActive = false;
    }
	}
}
