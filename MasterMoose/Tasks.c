/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     Auto.c                                                      */
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

///////////////////////////////////////STOP DRIVE TRAIN
void StopDrive()
{
	motor[leftDrive] = 0;
	motor[leftDrive2] = 0;
	motor[rightDrive] = 0;
	motor[rightDrive2] = 0;
}
///////////////////////////////////////APPLY BREAKS
void Break(int time, int speed)
{
	motor[leftDrive] = -speed;
	motor[leftDrive2] = -speed;
	motor[rightDrive] = -speed;
	motor[rightDrive2] = -speed;
	wait1Msec(time);
	StopDrive();
}
void Break2(int time, int speed)
{
	motor[leftDrive] = speed;
	motor[leftDrive2] = speed;
	motor[rightDrive] = -speed;
	motor[rightDrive2] = -speed;
	wait1Msec(time);
	StopDrive();
}
int grabber(int action, int type, int timeout){
	int target;
	//Pick up
	if (action == 0) {
		//type == 0 Stars
		if (type == 0) {
			target = -950;
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
	//Ready position
	if (action == 2) {
		target = -600;
	}
	return target;
}

///////////////////////////////////////MOVE ROBOT BASED ON SPEED EXAMPLE // direction: -1 = left   1 = right 2 = Forward -2 = Backwards// while(condition){ Move(2,127) };//THIS MOVES FORWARD UNTIL CONDITION IS MET
/*
void Move(int direction, int speed)
{
	int left = 0, right = 0;
	if (direction == 1){left = 1; right = -1;}
	else if (direction == -1){left = -1; right =  1; }
	else if (direction == 2) {left =  1; right =  1; }
	else if (direction == -2){left = -1; right = -1; }
	else if (direction == 3){left = 1; right = 0; }
	else if (direction == -3){left = 0; right = 1; }
	else if (direction == 4){left = -1; right = 0; }
	else if (direction == -4){left = 0; right = -1; }

	motor[leftDrive] = speed*left;
	motor[leftDrive2] = speed*left;
	motor[rightDrive] = speed*right;
	motor[rightDrive2] = speed*right;
}
*/

int MoveDist(int inches, int speed, int TimeOut)
{
	int status, direction = 0;
	if (MoveCounter == 0 )
	{
		SensorValue[leftDriveEncoder] = 0;
		MoveCounter = 1;
		clearTimer(T3);
	}
	////////////////////////////////////FAILASFE TIMEOUT
	if(time1[T3] > TimeOut && TimeOut > 0){
		StopDrive();
		break;
	}
	////////////////////////////////////////////////////
	if (inches < 0){direction = -1;}
	else if (inches > 0){direction = 1;}
	int ticks = abs(inches*19); ///NEEDS TO BE ADJUSTED BASED ON ENCONDER RATIO
	if(abs(SensorValue[leftDriveEncoder]) < ticks) //ENCODER TO USE FOR DISTANCE
	{
	motor[leftDrive] = speed*direction;
	motor[leftDrive2] = speed*direction;
	motor[rightDrive] = speed*direction;
	motor[rightDrive2] = speed*direction;
		status = 1;
	}
	else
	{

		motor[leftDrive] = (speed*direction*-1)/20;
		motor[leftDrive2] = (speed*direction*-1)/20;
		motor[rightDrive] = (speed*direction*-1)/20;
		motor[rightDrive2] = (speed*direction*-1)/20;


		delay(330);
		StopDrive();
		status = 0;
		MoveCounter = 0;
	}
	return status;
}

///////////////////////////////////////TURN BASED ON GYRO DEGREES EXAMPLE // TurnDegree(-90, 127);//THIS TURNS LEFT 90 DEGREES AT 127 POWER
void TurnDegree(int degrees, int speed, int Timeout)
{
	int left = 0, right = 0;
	SensorValue[Gyro] = 0;
	if (degrees < 0){left = -1; right = 1;}
	else if (degrees > 0){left = 1; right = -1; }
	float ticks = abs(degrees*6.7);
	clearTimer(T3);

	while(abs(SensorValue[Gyro]) < ticks)
	{
		/////////////////////////////////////////////TIMEOUT
		if(time1[T3] > TimeOut && TimeOut > 0){break;}
		////////////////////////////////////////////////////
		motor[leftDrive] = speed*left;
		motor[leftDrive2] = speed*left;
		motor[rightDrive] = speed*right;
		motor[rightDrive2] = speed*right;
	}
	motor[leftDrive] = (speed*left*-1)/9;
	motor[leftDrive2] = (speed*left*-1)/9;
	motor[rightDrive] = (speed*right*-1)/9;
	motor[rightDrive2] = (speed*right*-1)/9;

	wait1Msec(250);
	StopDrive();
}
void Deploy(){
	motor[rightGrabber] = 127;
  motor[leftGrabber] = 127;
  wait1Msec(500);
  motor[rightGrabber] = 0;
  motor[leftGrabber] = 0;

  motor[rightLift] = -127;
  motor[leftLift] = -127;
  motor[rightLift2] = -127;
  motor[leftLift2] = -127;
  wait1Msec(200);
  motor[rightLift] = 0;
  motor[leftLift] = 0;
  motor[rightLift2] = 0;
  motor[leftLift2] = 0;
}


bool liftSimple(int target){
	int correction = abs(target) - abs(SensorValue[leftLiftEncoder]);
	if (abs(SensorValue[leftLiftEncoder]) < abs(target)) {
		motor[leftLift] = -127;
		motor[leftLift2] = -127;
		motor[rightLift] = -127;
		motor[rightLift2] = -127;
		return false;
	}
	if (abs(SensorValue[leftLiftEncoder]) > abs(target)) {
		motor[leftLift] = 70;
		motor[leftLift2] = 70;
		motor[rightLift] = 70;
		motor[rightLift2] = 70;
		return true;
	}
	return false;
}


void liftPosition(int target){
	int correction = abs(target) - abs(SensorValue[leftLiftEncoder]);
	if (abs(SensorValue[leftLiftEncoder]) < abs(target)) {
		motor[leftLift] = -127;
		motor[leftLift2] = -127;
		motor[rightLift] = -127;
		motor[rightLift2] = -127;

	}
	if (abs(SensorValue[leftLiftEncoder]) > abs(target)) {
		motor[leftLift] = 0;
		motor[leftLift2] = 0;
		motor[rightLift] = 0;
		motor[rightLift2] = 0;

	}

}
