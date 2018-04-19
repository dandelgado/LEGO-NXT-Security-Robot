#pragma config(Sensor, S1,		 frontSensor,		 sensorSONAR)
#pragma config(Sensor, S2,		 leftSensor,		 sensorSONAR)
#pragma config(Motor,	 motorA,					shooter,			 tmotorNXT, PIDControl, encoder)
#pragma config(Motor,	 motorB,					leftMotor,		 tmotorNXT, PIDControl, encoder)
#pragma config(Motor,	 motorC,					rightMotor,		 tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard							 !!*//

/*
ASSUMPTIONS AND EDGE CASES
- Assume no dead ends.
- Assume there is enough room for the robot to move/turn successfully.
- Assume robot can successfully detect all obstacles in the room.
- Assume optimal starting position.
*/

void moveForwards()
{
	motor[leftMotor] = 40;
	motor[rightMotor] = 40;
}

void moveBackwards()
{
	motor[leftMotor] = -40;
	motor[rightMotor] = -40;
}

void stopMove()
{
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
}

void turnLeft()
{
	motor[leftMotor] = -20;
	motor[rightMotor] = 20;
	wait1Msec(1000);
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
}

void turnRight()
{
	motor[leftMotor] = 20;
	motor[rightMotor] = -20;
	wait1Msec(1000);
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
}

int attackMode(int objDist)
{
	int r = 0;
	clearTimer(T1);
	while(time1[T1]<3000) {
		if(SensorValue[frontSensor] > objDist+5 || SensorValue[frontSensor] < objDist-5) {
			motor[shooter] = 45;
			wait1Msec(500);
			motor[shooter] = 0;
			r = 1;
		}
		else {
			stopMove();
		}
	}
	return r;
}

task main()
{
	while(true)		/* While the Sonar Sensor readings are greater */
	{
		if(SensorValue[frontSensor] > 25)
		{
			moveForwards();
		}
		else
		{
			/*Robot waits 5 seconds for object to move.
			If object moves, the robot will attack, and then proceed to move forward.
			If not, the robot attempts to make a turn.*/
			stopMove();
			wait1Msec(500);
			int objDist = SensorValue[frontSensor];
			if (attackMode(objDist) == 1) {
				continue;
			}
			else {
				if (SensorValue[frontSensor] < 20) {
					moveBackwards();
					wait1Msec(500);
					continue;
				}
				if (SensorValue[leftSensor] > 25){
					turnLeft();
					continue;
				}
				else
				{
					turnRight();
					continue;
				}
			}
		}
	}
}
