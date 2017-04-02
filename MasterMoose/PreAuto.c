/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     PreAuto.c                                                   */
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

SensorValue[leftLiftEncoder] = 0;
SensorValue[rightLiftEncoder] = 0;

SensorValue[leftDriveEncoder] = 0;
SensorValue[rightDriveEncoder] = 0;

SensorType[in8] = sensorNone;
wait1Msec(1000);
SensorType[in8] = sensorGyro;
wait1Msec(2000);

SensorValue[sideSelector];
SensorValue[typeSelector];

SensorValue[leftDriveEncoder] = 0;
SensorValue[rightDriveEncoder] = 0;
