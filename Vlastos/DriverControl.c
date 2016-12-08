/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     DriverControl.c                                             */
/*    Author:     Henry Williams                                              */
/*    Created:    27 Oct 2016                                                 */
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

startTask( Set_Drive );

while (true)
{
	resetMotorEncoder(forkLeftFront);
  resetMotorEncoder(forkRightFront);

	while (true)
	{
		forkLeftValue = getMotorEncoder(forkLeftFront);
    forkRightValue = getMotorEncoder(forkRightFront);

		forkSpeed = 0;

		if (vexRT[Btn6D] == 1)
    {
    	forkSpeed = 127;
    }

    if (vexRT[Btn6U] == 1)
    {
     forkSpeed = -127;
   	}

    forkRightSpeed = forkSpeed
    forkLeftSpeed = forkSpeed

    //if (forkRightValue < forkLeftValue)
    //{
    //  forkRightSpeed += (forkLeftValue - forkRightValue)
    //}

    //if (forkLeftValue < forkRightValue)
    //{
    //  forkLeftSpeed += (forkReftValue - forkLightValue)
    //}

		if (SensorValue[dgtl1] == 0)
    {
      motor(forkRightFront) = forkRightSpeed;
 			motor(forkRightBack) = forkRightSpeed;
 			motor(forkLeftFront) = forkLeftSpeed;
 			motor(forkLeftBack) = forkLeftSpeed;
    } else {
    	if (vexRT[Btn8U] == 1) {
    		motor(forkRightFront) = -127;
 				motor(forkRightBack) = -127;
 				motor(forkLeftFront) = -127;
 				motor(forkLeftBack) = -127;
 			}
    }

		DrivePower(vexRT[Ch2] + vexRT[Ch1], vexRT[Ch2] - vexRT[Ch1]);
  }
}
