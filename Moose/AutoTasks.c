/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     AutoTasks.c                                                 */
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

task timeout(){
	while(true){
		if (time1(T1) > 14000){ // 14 seconds
			stopTask(autonomous);
			motor[leftDrive] = 0;
			motor[leftDrive2] = 0;
			motor[rightDrive] = 0;
			motor[rightDrive2] = 0;
			motor[leftLift] = 0;
			motor[leftLift2] = 0;
			motor[rightLift] = 0;
			motor[rightLift2] = 0;
			motor[leftGrabber] = 0;
			motor[rightGrabber] = 0;
			stopTask(timeout);
		}
		wait1Msec(20);
	}
}

bool gyroTurningActive = false;
float gyroTarget = 0, speed = 0;
task Gyro_Drive()
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

void resetDrive (){
	motor[leftDrive] = 0;
	motor[leftDrive2] = 0;
	motor[rightDrive] = 0;
	motor[rightDrive2] = 0;
}

void resetEnc() {
	SensorValue[leftDriveEncoder] = 0;
	SensorValue[rightDriveEncoder] = 0;
	SensorValue[leftLiftEncoder] = 0;
	SensorValue[leftLiftEncoder] = 0;
}

void resetLiftEnc(){
	SensorValue[leftLiftEncoder] = 0;
	SensorValue[rightLiftEncoder] = 0;
}

void resetGrabber(){
	while(SensorValue[grabberEncoder] < -600) {
		motor[leftGrabber] = -40;
		motor[rightGrabber] = -40;
	}
	motor[leftGrabber] = 0;
	motor[rightGrabber] = 0;
}

void checkGrip(int type){
	int target;
	//type == 0 Stars
	if (type == 0) {
		target = -930;
	}
	//type == 1 Cube
	if (type == 1){
		target = -1150;
	}

	if(SensorValue[grabberEncoder] > target) {
		motor[leftGrabber] = 40;
		motor[rightGrabber] = 40;
	} else {
		motor[leftGrabber] = 0;
		motor[rightGrabber] = 0;
	}
}

void move(int dist, int s, bool cube){
	while (abs(SensorValue[leftDriveEncoder]) <= dist){
		speed = s;
		if (cube) {
			checkGrip(1);
		}
	}
	speed = 0;
	resetEnc();
	wait1Msec(300);
}

/*
void brake(int speed, int dir){
	// dir == 1 CCW
	// dir == -1 CW
	motor[leftDrive] = speed*(-dir);
	motor[leftDrive2] = speed*(-dir);
	motor[rightDrive] = speed*dir;
	motor[rightDrive2] = speed*dir;
}

void turn(int speed, int dir){
	// dir == 1 CCW
	// dir == -1 CW
	motor[leftDrive] = speed*(-dir);
	motor[leftDrive2] = speed*(-dir);
	motor[rightDrive] = speed*dir;
	motor[rightDrive2] = speed*dir;
}
*/

// void liftComp(int target){
// 	int correction = target - SensorValue[leftliftEncoder];

// 	if (SensorValue[leftLiftEncoder] < target) {
// 		motor[leftLift] = -1*(correction*correction);
// 		motor[leftLift2] = -1*(correction*correction);
// 		motor[rightLift] = -1*(correction*correction);
// 		motor[rightLift2] = -1*(correction*correction);
// 	}

// 	if (SensorValue[leftLiftEncoder] > target) {
// 		motor[leftLift] = correction*correction;
// 		motor[leftLift2] = correction*correction;
// 		motor[rightLift] = correction*correction;
// 		motor[rightLift2] = correction*correction;
// 	}
// }

bool liftSimple(int target){
	int correction = abs(target) - abs(SensorValue[leftLiftEncoder]);
	if (abs(SensorValue[leftLiftEncoder]) < abs(target)) {
		motor[leftLift] = -1*(correction*correction);
		motor[leftLift2] = -1*(correction*correction);
		motor[rightLift] = -1*(correction*correction);
		motor[rightLift2] = -1*(correction*correction);
		return false;
	}
	if (abs(SensorValue[leftLiftEncoder]) > abs(target)) {
		motor[leftLift] = correction*correction;
		motor[leftLift2] = correction*correction;
		motor[rightLift] = correction*correction;
		motor[rightLift2] = correction*correction;
		return true;
	}
	return false;
}

//Action 0 = pick up
//Action 1 = drop
int grabber(int action, int type){
	int target;
	//Pick up
	if (action == 0) {
		//type == 0 Stars
		if (type == 0) {
			target = -930;
		}
		//type == 1 Cube
		if (type == 1){
			target = -1150;
		}
	}
	//Drop
	if (action == 1){
		target = -450;
	}
	return target;
}
