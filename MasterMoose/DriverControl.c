/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     DriverControl.c                                             */
/*    Author:     Henry Williams                                         			*/
/*    Author:     Teddy Hoisington                                         		*/
/*    Created:    13 March 2017                                               */
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



while (true)
{
	pot1Side = SensorValue[sideSelector];
	pot2Type = SensorValue[typeSelector];
	if(vexRT[Btn6U] == 1)
  {
  	liftSpeed = -127;
  }
  else if(vexRT[Btn6D] == 1)
  {
  	liftSpeed = 127;
  }
  else if(vexRT[Btn8D] == 1)
  {
  	liftSpeed = -40;
  }
  else if(vexRT[Btn8U] == 1)
  {
  	liftSpeed = 40;
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

  motor[rightGrabber] = grabberSpeed;
  motor[leftGrabber] = grabberSpeed;

	motor[leftDrive] = vexRT[Ch3] + vexRT[Ch1];
	motor[leftDrive2] = vexRT[Ch3] + vexRT[Ch1];
	motor[rightDrive] = vexRT[Ch3] - vexRT[Ch1];
	motor[rightDrive2] = vexRT[Ch3] - vexRT[Ch1];

  motor[rightLift] = liftSpeed;
  motor[leftLift] = liftSpeed;
  motor[rightLift2] = liftSpeed;
  motor[leftLift2] = liftSpeed;

}
