/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     DriverControl.c                                             */
/*    Author:     Henry Williams                                              */
/*    Created:    4 Jan 2017                                                  */
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
	liftTarget = LIFT_MAX;
	wait1Msec(500);
	speed = 127;
	wait1Msec(750);
	motor[intakeLeft] = 127;
	wait1Msec(250);
	speed = 0 
	gyroTurningActive = false;
}