/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     Tasks.c                                                     */
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

void DrivePower(float left, float right)
{
	leftTarget = left;
	rightTarget = right;
}

void MoveForDistance(int dist)
{
  int startRight = -SensorValue[rightDriveEncoder];
	int startLeft = SensorValue[leftDriveEncoder];

	//int progress = ( abs(startLeft - SensorValue[leftDriveEncoder]) + abs(startRight - SensorValue[rightDriveEncoder]) ) / 2;
	int progress = abs(SensorValue[leftDriveEncoder] - startLeft);

	//int goal = startLeft + (360 * (dist / 4));
	int goal = startLeft + dist;

	if(encoderDrivingActive)
	{
		DrivePower(30, 30);
		while(progress < goal) {
			//progress = ( abs(startLeft - SensorValue[leftDriveEncoder]) + abs(startRight - SensorValue[rightDriveEncoder]) ) / 2;
			progress = abs(SensorValue[leftDriveEncoder] - startLeft);
		}
		DrivePower(0, 0);
	}
}

bool holdLiftActive = false;

task hold_Lift()
{
	while(true)
	{
		if(holdLiftActive)
		{

		}
	}
}

task hold_Grabber() {
	while(true)
	{
		if(holdLiftActive)
		{

		}
	}

}

task gyro_Drive()
{
	float kp = 0.25, ki = 0.0, kd = 35;
	float error = 0, last_error = 0, integral = 0, derivative = 0, power = 0;
	float time_step = 50;

	float max_power = 70;
	float integral_max_power = 30;
	float integral_window = 100;

	while(true)
	{
		if(gyroTurningActive)
		{
			last_error = error;
			error = gyroTarget - SensorValue[in8];
			derivative = (error - last_error)/time_step;

			if(abs(error) < integral_window)integral += error * time_step;
			else integral = 0;

			if(integral * ki > integral_max_power) integral = integral_max_power / ki;
			if(integral * ki < - integral_max_power) integral = - integral_max_power / ki;

			power = kp*error + ki * integral + kd * derivative;

			if(power > max_power) power = max_power;
			if(power < - max_power) power = - max_power;

			DrivePower(speed - power, speed + power);
		}
		else
		{
			error = 0;
			last_error = 0;
			integral = 0;
			derivative = 0;
			power = 0;
		}
		wait1Msec(time_step);
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

		motor[leftDrive] = leftCur;
		motor[leftDrive2] = leftCur;
   		motor[rightDrive] = rightCur;
   		motor[rightDrive2] = rightCur;

		wait1Msec(Time_Step);
	}
}

float kp = 1, kd = 1;
float error = 0, last_error = 0, derivative = 0, power = 0;
float oldTarget = 0;
float time_step = 100;
bool driverControl = false;

task Lift_Control()
{
	float max_power = 127;

	while(true)
	{
		last_error = error;
		int sensor_val = (SensorValue[rightLift] + SensorValue[leftLift]) / 2;
		error = liftTarget - sensor_val;
		derivative = (error - last_error)/time_step;
		power = kp * error + kd * derivative;

		if(power > max_power) power = max_power;
		if(power < - max_power) power = - max_power;

		if(driverControl)
		{
			if(vexRT[Btn8R])
			{
				power = 0;
			}
			if(vexRT[Btn8L]  && abs(error) < 250 && abs(liftTarget - LIFT_MIN) < 250)
			{
				power = -100;
			}

		}

		motor[rightLift] = power;
		motor[leftLift] = power;
		motor[rightLift2] = power;
		motor[leftLift2] = power;

		oldTarget = liftTarget;

		wait1Msec(time_step);
	}
}
