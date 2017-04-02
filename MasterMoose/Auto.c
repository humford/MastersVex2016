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
int y = 0;
int x = 0;
if (SensorValue[sideSelector] < 1500){
	aSide = 0; //Left side
} else if (SensorValue[sideSelector] > 2500){
	aSide = 1; //Right side
} else {
	aSide = 2; //Straight
}

if (SensorValue[typeSelector] < 2000){
	autoType = 0; //Stars
} else if (SensorValue[typeSelector] > 2000){
	autoType = 1; //Cube
}


if (aSide == 0) { //Left side
	switch (autoType){
		case 0: //Stars
			leftStarAuto();
			break;
		case 1: //Cube
			leftCubeAuto();
			break;
	}

} else if (aSide == 1) { //Right side
	while (autoType == 0){ //Stars

	}
	while (autoType == 1){ //Cube

	}
} else if (aSide == 2) { //Straight auto

}
/*
while ( alliance == 0 ) // BEGIN BLUE ALLIANCE CODE
{
	while ( autonomousN == 0 ) // BEGIN AUTONOMOUS 1 CODE
	{
		BlueAuto1 ( ) ;
	}
	while ( autonomousN == 1 ) // BEGIN AUTONOMOUS 2 CODE
	{
		BlueAuto2 ( ) ;
	}
	while ( autonomousN == 2 ) // BEGIN AUTONOMOUS 3 CODE
	{
		BlueAuto3 ( ) ;
	}
	while ( autonomousN == 3 ) // BEGIN AUTONOMOUS 4 CODE
	{
		BlueAuto4 ( ) ;
	}
	while ( autonomousN == 4 ) // BEGIN AUTONOMOUS 5 CODE
	{
		BlueAuto5 ( );
	}
	// END BLUE ALLIANCE CODE
}
while ( alliance == 1 ) //  BEGIN RED ALLIANCE CODE
{
	while ( autonomousN == 0 ) // BEGIN AUTONOMOUS 1 CODE
	{
		RedAuto1 ( ) ;
	}
	while ( autonomousN == 1 ) // BEGIN AUTONOMOUS 2 CODE
	{
		RedAuto2 ( ) ;
	}
	while ( autonomousN == 2 ) // BEGIN AUTONOMOUS 3 CODE
	{
		RedAuto3 ( ) ;
	}
	while ( autonomousN == 3 ) // BEGIN AUTONOMOUS 4 CODE
	{
		RedAuto4 ( ) ;
	}
	while ( autonomousN == 4 ) // BEGIN AUTONOMOUS 5 CODE
	{
		RedAuto5 ( ) ;
	}
	// END RED ALLIANCE CODE
}
while ( alliance == 2 ) // BEGIN SELF CHECK CODE
{
	SelfCheckCode ( ) ;
	// END SELF CHECK CODE
}
while ( alliance == 3 ) // BEGIN SELF CHECK CODE
{
	DebugCode ( ) ;
	// END DebugCode
}*/
