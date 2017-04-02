void rightStarAuto(){
	Deploy();
	while (SensorValue[grabberEncoder] > grabber(2, 0, 500)){
		motor[rightGrabber] = 127;
  	motor[leftGrabber] = 127;
	}
	motor[rightGrabber] = 0;
  motor[leftGrabber] = 0;

	TurnDegree(-45, 127, 1500);

	while (MoveDist(30, 127, 3000) == 1){}

	while (SensorValue[grabberEncoder] > grabber(0, 1, 500)){
		motor[rightGrabber] = 127;
  	motor[leftGrabber] = 127;
	}
	motor[rightGrabber] = 0;
  motor[leftGrabber] = 0;



  while(liftSimple(-100) == false){}

  motor[leftLift] = 0;
	motor[leftLift2] = 0;
	motor[rightLift] = 0;
	motor[rightLift2] = 0;

  TurnDegree(-90, 127, 3000);

  while (MoveDist(-62, 127, 3000) == 1){}

  while(liftSimple(-145) == false){}

  motor[leftLift] = 0;
	motor[leftLift2] = 0;
	motor[rightLift] = 0;
	motor[rightLift2] = 0;

	motor[leftGrabber] = 50;
	motor[rightGrabber] = 50;
	motor[leftLift] = 90;
	motor[leftLift2] = 90;
	motor[rightLift] = 90;
	motor[rightLift2] = 90;
	wait1Msec(200);
	motor[leftGrabber] = 0;
	motor[rightGrabber] = 0;
	motor[leftLift] = 40;
	motor[leftLift2] = 40;
	motor[rightLift] = 40;
	motor[rightLift2] = 40;


}
