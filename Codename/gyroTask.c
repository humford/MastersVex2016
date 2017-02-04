int gyroscope;
task gyroUpdate(){

	while(true){
		gyroscope = SensorValue[in8];
		wait1Msec(20);
	}
}
int time;
task timeout(){
	while(true){
		time = time1[T1];
		if (time1(T1) > 13000){ // 13 seconds
			//stopTask(autonomous);

			resetDrive();
			motor[leftLift] = 0;
			motor[leftLift2] = 0;
			motor[rightLift] = 0;
			motor[rightLift2] = 0;
			motor[leftGrabber] = 0;
			motor[rightGrabber] = 0;
			stopAllTasks();
			stopTask(timeout);
		}
		wait1Msec(20);
	}
}
