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

task usercontrol()
{

	float leftTarget = 0, rightTarget = 0;
	int intakeSpeed = 0;
	int conveySpeed = 0;

	while (true)
	{
    if(vexRT[Btn6U])
    {
    	// liftTarget = LIFT_MAX;
        liftSpeed = 127
    }
    else if(vexRT[Btn6D])
    {
    	// liftTarget = LIFT_MIN;
        liftSpeed = 127
    }

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

    if (vexRT[Btn7D] == 1)
    {
    	conveySpeed = -127;
    }
    else if (vexRT[Btn7U] == 1)
    {
    	conveySpeed = 127;
    }
    else
    {
     	conveySpeed = 0;
    }

    motor[intakeLeft] = intakeSpeed;
    motor[intakeRight] = intakeSpeed;
    motor[conveyMotor] = conveySpeed;

    liftRightSpeed = liftSpeed
    liftLeftSpeed = liftSpeed
    motor[liftRight] = liftRightSpeed
    motor[liftLeft] = liftLeftSpeed

    DrivePower(vexRT[Ch2] + vexRT[Ch1], vexRT[Ch2] - vexRT[Ch1], vexRT[Ch4]);
	}
}
