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
		time = time1(T1);
		if (time1(T1) > 1100){
			//stopTask(autonomous);
		}
		wait1Msec(20);
	}
}
