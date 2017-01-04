/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     DriverControl.c                                             */
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

float leftTarget = 0, rightTarget = 0;

int liftTarget = LIFT_MAX;
int liftSpeed = 0;
int intakeSpeed = 0;
startTask( Set_Drive );

while (true)
{
	if (vexRT[Btn6D] == 1){
    	liftSpeed = -127;
    } else if (vexRT[Btn6U] == 1){
    	liftSpeed = 127;
   	} else {
   		liftSpeed = 0;
   	}
    
    motor[liftLeft] = liftSpeed;
	motor[liftRight] = liftSpeed;

    if (vexRT[Btn5D] == 1){
    	intakeSpeed = -127;
    } else if (vexRT[Btn5U] == 1){
    	intakeSpeed = 127;
   	} else {
   		intakeSpeed = 0;
   	}

   	motor[intakeLeft] = intakeSpeed;
   	motor[intakeRight] = intakeSpeed;

   	motor[leftFront] = vexRT[Ch2] + vexRT[Ch1];
	motor[leftBack] = vexRT[Ch2] + vexRT[Ch1];

   	motor[rightFront] = vexRT[Ch2] - vexRT[Ch1];
	motor[rightBack] = vexRT[Ch2] - vexRT[Ch1];

	motor[strafeLeft] = vexRT[Ch4];
	motor[strafeRight] = vexRT[Ch4];
}
