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

startTask( Set_Drive );

while (true)
{
	// resetMotorEncoder(liftLeftFront);
  // resetMotorEncoder(liftRightFront);

	while (true)
	{
		// liftLeftValue = getMotorEncoder(liftLeftFront);
    // liftRightValue = getMotorEncoder(liftRightFront);

		liftSpeed = 0;

		if (vexRT[Btn6D] == 1)
    {
    	liftSpeed = 127;
    }

    if (vexRT[Btn6U] == 1)
    {
     liftSpeed = -127;
   	}

    liftRightSpeed = liftSpeed
    liftLeftSpeed = liftSpeed

    // if (liftRightValue < liftLeftValue)
    // {
    //   liftRightSpeed += (liftLeftValue - liftRightValue)
    // }

    // if (liftLeftValue < liftRightValue)
    // {
    //   liftLeftSpeed += (liftReftValue - liftLightValue)
    // }

 		motor(liftRightTop) = liftRightSpeed;
 		motor(liftRightBottom) = liftRightSpeed;
 		motor(liftLeftTop) = liftLeftSpeed;
 		motor(liftLeftBottom) = liftLeftSpeed;

		DrivePower(vexRT[Ch2] + vexRT[Ch1], vexRT[Ch2] - vexRT[Ch1]);
    // motor(middleLeft) = vexRT[Ch4]
    // motor(middleRight) = vexRT[Ch4]
  }
}
