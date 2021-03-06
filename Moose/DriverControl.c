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
  startTask(Set_Drive);

  while(true)
  {
    if(vexRT[Btn6U])
    {
    	liftSpeed = -127;
    }
    else if(vexRT[Btn6D])
    {
    	liftSpeed = 127;
    }
    else
    {
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

    if (vexRT[Btn8D] == 1) {
    	startTask(autonomous);
  	}

   }
}
