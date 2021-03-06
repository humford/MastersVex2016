#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl5,  rightLiftEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  leftLiftEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl11, grabberEncoder, sensorQuadEncoder)
#pragma config(Sensor, I2C_1,  leftDriveEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  rightDriveEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           rightDrive2,   tmotorVex393HighSpeed_HBridge, openLoop, reversed, driveRight, encoderPort, I2C_2)
#pragma config(Motor,  port2,           rightDrive,    tmotorVex393HighSpeed_MC29, openLoop, reversed, driveRight, encoderPort, I2C_2)
#pragma config(Motor,  port3,           leftDrive,     tmotorVex393HighSpeed_MC29, openLoop, driveLeft, encoderPort, I2C_1)
#pragma config(Motor,  port4,           rightLift,     tmotorVex393_MC29, openLoop, reversed, encoderPort, dgtl5)
#pragma config(Motor,  port5,           leftLift,      tmotorVex393_MC29, openLoop, encoderPort, dgtl7)
#pragma config(Motor,  port6,           rightGrabber,  tmotorVex393_MC29, openLoop, encoderPort, dgtl11)
#pragma config(Motor,  port7,           leftGrabber,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           rightLift2,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           leftLift2,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          leftDrive2,    tmotorVex393HighSpeed_HBridge, openLoop, driveLeft, encoderPort, I2C_1)

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:     main.c                                                      */
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

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(120)

///////////////////////////ENABLE DEBUG MODE (IF TRUE SKIPS AUTO SELECTION AND RUNS DEBUG AUTO ONLY)
#define DEBUG 0

#define LEFT_BUTTON 1
#define CENTER_BUTTON 2
#define RIGHT_BUTTON 4

#define DRIVE_WHEEL_CIR 12.56637 //circumfrence of drive wheel in inches
#define VAL_PER_ROTATION 360

#define DIST_TO_CUBE_Y 737
#define DIST_TO_CUBE_X 466
#define DIST_TO_FENCE_FROM_CUBE_Y -840
#define CLAW_CUBE_GRAB -865
#define CLAW_CUBE_DROP -660

#define LIFT_MAX 1500
#define LIFT_MIN 550

//////////////////////////////////GLOBAL VARIABLES
int liftRightSpeed = 0;
int liftLeftSpeed = 0;
int liftSpeed = 0;


int grabberRightSpeed = 0;
int grabberLeftSpeed = 0;
int grabberSpeed = 0;

float leftTarget = 0;
float rightTarget = 0;
float liftTarget = 0;

bool encoderDrivingActive = false;
bool gyroTurningActive = false;
float gyroTarget = 0, speed = 0;

//////////////////////////////////INCLUDED FILES

#include "Vex_Competition_Includes.c"   //VEX REQUIRED FILE
#include "Tasks.c"          			//RPM CALC // RPM CONTROL

///////////////////////////////////////////////////BEGIN PREAUTONOMOUS
#include "PreAuto.c"

///////////////////////////////////////////////////BEGIN AUTONOMOUS
#include "AutoTasks.c"
#include "Auto.c"

///////////////////////////////////////////////////BEGIN DRIVER CONTROL
#include "DriverControl.c"
