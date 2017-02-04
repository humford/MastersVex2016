#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl5,  rightLiftEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  leftLiftEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl11, grabberEncoder, sensorQuadEncoder)
#pragma config(Sensor, I2C_1,  leftDriveEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  rightDriveEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           rightDrive2,   tmotorVex393TurboSpeed_HBridge, PIDControl, reversed, driveRight, encoderPort, I2C_2)
#pragma config(Motor,  port2,           rightDrive,    tmotorVex393TurboSpeed_MC29, PIDControl, reversed, driveRight, encoderPort, I2C_2)
#pragma config(Motor,  port3,           leftDrive,     tmotorVex393TurboSpeed_MC29, PIDControl, driveLeft, encoderPort, I2C_1)
#pragma config(Motor,  port4,           rightLift,     tmotorVex393_MC29, openLoop, reversed, encoderPort, dgtl5)
#pragma config(Motor,  port5,           leftLift,      tmotorVex393_MC29, openLoop, encoderPort, dgtl7)
#pragma config(Motor,  port6,           rightGrabber,  tmotorVex393_MC29, openLoop, encoderPort, dgtl11)
#pragma config(Motor,  port7,           leftGrabber,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           rightLift2,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           leftLift2,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          leftDrive2,    tmotorVex393TurboSpeed_HBridge, PIDControl, driveLeft, encoderPort, I2C_1)
#include "gyroTask.c"
void orient(int speed, int target){
// dir == 1 CCW
// dir == -1 CW
	int dir;
	int divider = abs(target - SensorValue[in8]);
	if (divider!=0){
		dir = (target - SensorValue[in8])/divider;
	} else {
		dir = 0;
	}
	motor[leftDrive] = speed*(-dir);
	motor[leftDrive2] = speed*(-dir);
	motor[rightDrive] = speed*dir;
	motor[rightDrive2] = speed*dir;
	/*motor[leftDrive] = (target - SensorValue[in8])/(-2) -20;
	motor[leftDrive2] = (target - SensorValue[in8])/(-2)-20;
	motor[rightDrive] = (target - SensorValue[in8])/(2)+20;
	motor[rightDrive2] = (target - SensorValue[in8])/(2)+20;
	motor[leftDrive] = (target - SensorValue[in8])/(-4);
	motor[leftDrive2] = (target - SensorValue[in8])/(-4);
	motor[rightDrive] = (target - SensorValue[in8])/(4);
	motor[rightDrive2] = (target - SensorValue[in8])/(4);

	motor[leftDrive] = ((target - SensorValue[in8])/(-4)) - (dir*20);
	motor[leftDrive2] = ((target - SensorValue[in8])/(-4)) - (dir*20);
	motor[rightDrive] = ((target - SensorValue[in8])/(4)) + (dir*20);
	motor[rightDrive2] = ((target - SensorValue[in8])/(4)) + (dir*20);*/

}
void resetDrive (){
	motor[leftDrive] = 0;
	motor[leftDrive2] = 0;
	motor[rightDrive] = 0;
	motor[rightDrive2] = 0;

}
task main()
{
	bool oriented = false;
	startTask(gyroUpdate);
	SensorType[in8] = sensorNone;
  wait1Msec(1000);
  //Reconfigure Analog Port 8 as a Gyro sensor and allow time for ROBOTC to calibrate it
  SensorType[in8] = sensorGyro;
  wait1Msec(2000);
	SensorValue[in8] = 0;
	wait1Msec(1000);
	int targetCounter = 10;
	int speed = 35;
while(true){

	while (oriented == false) {
		orient(speed, 290);
		//180 degrees = 1290
		if (SensorValue[in8] == 290){
			//orient(127, 290);
			speed = 25;
			//wait1Msec(250);
			//oriented = true;
		} else {

		}
	}
	//oriented = false;
	targetCounter = 0;
	resetDrive();


}


}
