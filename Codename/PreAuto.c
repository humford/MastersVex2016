/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     PreAuto.c                                                   */
/*    Author:     Henry Williams                                              */
/*    Created:    14 Feb 2017                                                 */
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

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = false;

	//Reconfigure Analog Port 8 as a Gyro sensor and allow time for ROBOTC to calibrate it
	SensorType[in8] = sensorNone;
  wait1Msec(1000);
  SensorType[in8] = sensorGyro;
  wait1Msec(2000);

  //Reset sensor
	SensorValue[in8] = 0;
	wait1Msec(1000);

  //Reset lift encoders
  SensorValue[leftLiftEncoder] = 0;
  SensorValue[rightLiftEncoder] = 0;

	startTask(Set_Drive);
	startTask(gyro_Drive);
}