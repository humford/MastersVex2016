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

startTask( Set_Drive );

while (true)
{
	resetMotorEncoder(forkLeftFront);
  	resetMotorEncoder(forkRightFront);

	while (true)
	{
		int fork = ( getMotorEncoder(forkLeftFront) - getMotorEncoder(forkRightFront) ) / 2;

		forkSpeed = 0;

		if (vexRT[Btn6D] == 1)
    	{
      		forkSpeed = 127;
    	}

    	if (vexRT[Btn6U] == 1)
    	{
     	 forkSpeed = -127;
   		}

 		motor(forkRightFront) = forkSpeed;
 		motor(forkRightBack) = forkSpeed;
 		motor(forkLeftFront) = forkSpeed;
 		motor(forkLeftBack) = forkSpeed;

		DrivePower(vexRT[Ch2] + vexRT[Ch1], vexRT[Ch2] - vexRT[Ch1]);
  }
}
