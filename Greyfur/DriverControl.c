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

#define LIFT_MAX **FUCKING SET THIS VALUE YOU LAZY WHORES**
#define LIFT_MIN **FUCKING SET THIS VALUE YOU LAZY WHORES**

float leftTarget = 0, rightTarget = 0;

int intakeSpeed = 0;

startTask( Set_Drive );

while (true)
{
    if(vexRT[Btn6U]) liftTarget = LIFT_MAX;
    else if(vexRT[Btn6D]) liftTarget = LIFT_MIN;
	    
    if (vexRT[Btn5D] == 1)
    {
    	intakeSpeed = -127;
    }
	
    else if (vexRT[Btn5U] == 1)
    {
    	intakeSpeed = 127;
    } 
    else 
    {
     	intakeSpeed = 0;
    }

    motor[intakeLeft] = intakeSpeed;
    motor[intakeRight] = intakeSpeed;
	
    DrivePower(vexRT[Ch2] + vexRT[Ch1], vexRT[Ch2] - vexRT[Ch1], vexRT[Ch4]);
}
