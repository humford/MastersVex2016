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

void move(int speed, int dir){
	// dir == 1 forward
	// dir == -1 backwards
	motor[leftDrive] = speed*dir;
	motor[leftDrive2] = speed*dir;
	motor[rightDrive] = speed*dir;
	motor[rightDrive2] = speed*dir;
}

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
		target = -870;
	}

	if(SensorValue[grabberEncoder] > target) {
		motor[leftGrabber] = 40;
		motor[rightGrabber] = 40;
	} else {
		motor[leftGrabber] = 0;
		motor[rightGrabber] = 0;
	}
}

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
	int correction = target - SensorValue[leftliftEncoder];
	if (SensorValue[leftLiftEncoder] < target) {
		motor[leftLift] = -1*(correction*correction);
		motor[leftLift2] = -1*(correction*correction);
		motor[rightLift] = -1*(correction*correction);
		motor[rightLift2] = -1*(correction*correction);
		return false;
	}
	if (SensorValue[leftLiftEncoder] > target) {
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
			target = -800;
		}
	}
	//Drop
	if (action == 1){
		target = -450
	}
	return target
}