int gyroscope;
task gyroUpdate(){

	while(true){
		gyroscope = SensorValue[in8];
		wait1Msec(20);
	}
}
