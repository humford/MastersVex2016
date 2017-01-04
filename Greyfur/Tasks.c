/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     Tasks.c                                                     */
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


task Set_Drive()
{
	int leftCur = 0, rightCur = 0, leftError = 0, rightError = 0;
	//PLAY WITH VALEUS TILL THEY WORK
	int Time_Step = 20;
	int Power_Step = 10;
	while(true)
	{
		leftError = leftTarget - leftCur;
		rightError = rightTarget - rightCur;

		if(abs(leftError) <= Power_Step) leftCur = leftTarget;
		else leftCur += (leftError > 0) ? Power_Step : -Power_Step;

		if(abs(rightError) <= Power_Step) rightCur = rightTarget;
		else rightCur += (rightError > 0) ? Power_Step : -Power_Step;

		motor[leftFront] = leftCur;
		motor[leftBack] = leftCur;

   		motor[rightFront] = rightCur;
		motor[rightBack] = rightCur;
		
		wait1Msec(Time_Step);
	}
}

void DrivePower(float left, float right, float strafe)
{
	leftTarget = left;
	rightTarget = right;
	motor[strafeRight] = strafe;
}

task Lift_Control()
{
	float kp = 0.1, kd = 10;
	float error = 0, last_error = 0, derivative = 0, power = 0;
	float time_step = 100;

	float max_power = 127;

	while(true)
	{
		last_error = error;
		error = liftTarget - SensorValue[LiftPos];
		derivative = (error - last_error)/time_step;
		power = kp*error + kd * derivative;

		if(power > max_power) power = max_power;
		if(power < - max_power) power = - max_power;

		motor[liftLeftTop] = power;
		motor[liftLeftBottom] = power;
		motor[liftRightBottom] = power;
		motor[liftRightBottom] = power;
		wait1Msec(time_step);
	}
}
