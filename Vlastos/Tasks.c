/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     Tasks.c                                                     */
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

////////////////////////////RPM CALCULATION TASK
task RPMCALC()
{
	int count = 0;
	int status = 0;
	clearTimer(T1);
	while(1)
	{
		if (status == 0)
		{
			count++;
			status = 1;
		}
		if (count == 5)
		{
			CurrentSpeed = (1000*5*30)/time1[T1];
			clearTimer(T1);
			count = 0;
		}
		if (time1[T1] > 500)
		{
			CurrentSpeed = 0;
		}
	}
}
////////////////////////////RPM CONTROL TASK
task BANGBANG ()
{
	int MotorPower = 0;
	while(1)
	{
		///////CONTROL
		if (CurrentSpeed > TargetSpeed){
			MotorPower = BasePower;
		}
		else if (CurrentSpeed < TargetSpeed){
			MotorPower = 127;
		}
		motor[m1] = MotorPower;
		motor[m2] = MotorPower;
		EndTimeSlice(); //OR DELAY 20 MILLI
		////ERROR CALCULATION//
		rpmError = abs((TargetSpeed - CurrentSpeed)/10);
	}
}

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

		motor[rightFB] = rightCur;
		motor[rightMiddle] = rightCur;

		motor[leftFB] = leftCur;
		motor[leftMiddle] = leftCur;

		wait1Msec(Time_Step);
	}
}

void DrivePower(float left, float right)
{
	leftTarget = left;
	rightTarget = right;
}