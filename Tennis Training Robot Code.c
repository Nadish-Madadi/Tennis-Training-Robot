#include "mindsensors-motormux.h"


//RNG
int RandomAngle()
{
	int listOfAngles[61];
	for (int i = 0; i < 61; i++)
	{
		listOfAngles[i] = i - 30;
	}

	int randomNumber = random(60);

	int randomAngle = listOfAngles[randomNumber];

	displayString(2,"%d", randomAngle);

	return randomAngle;
}


//rotate
void rotate(int motorPow, int angle)
{
	resetGyro(S3);
	wait1Msec(1000);
	if(angle > 0)
	{
		motor[motorA] = -motorPow;
		motor[motorD] = motorPow;
		while(getGyroDegrees(S3) < angle)
		{}
		motor[motorA] = motor[motorD] = 0;
	}
	else if(angle < 0)
	{
		motor[motorA] = motorPow;
		motor[motorD] = -motorPow;
		while(getGyroDegrees(S3) > angle)
		{}
		motor[motorA] = motor[motorD] = 0;
	}

	motor[motorA] = motor[motorD] = 0;
}


//move conveyor
void moveConveyor(int motorPow)
{
	const int BALL_DIST = (15.4 * 180)/(PI*4.15);
	MSMMotorEncoderReset(mmotor_S2_1);
	MSMMotor(mmotor_S2_1, -motorPow);
	while (MSMMotorEncoder(mmotor_S2_1) > -BALL_DIST)
	{}
	MSMotorStop(mmotor_S2_1);
	MSMMotorEncoderReset(mmotor_S2_1);
}


//intake sequence
void intakeSequence()
{
	const int CAPACITY = 3;
	int ballcount = 0;
	const int INTAKEPOWER = 30;

	displayString(1,"Intaking Balls");
	while(ballcount < CAPACITY)
	{
		MSMMotorEncoderReset(mmotor_S2_1);
		while(SensorValue[S4] != (int)colorYellow)
		{}

		moveConveyor(INTAKEPOWER);
		ballcount++;
		displayString(2, "%d", ballcount);
		wait1Msec(2000);
	}
}

//shooting sequence
void shooting()
{
	MSMMotorEncoderReset(mmotor_S2_1);
	motor[motorB] = -100;
	motor[motorC] = 100;
	for(int count = 0; count < 3; count++)
	{
		MSMMotorEncoderReset(mmotor_S2_1);
		int chosenAngle = RandomAngle();
		displayString(5, "%d", chosenAngle);
		wait1Msec(1000);

		rotate(15, chosenAngle);
		wait1Msec(5000);

		MSMMotorEncoderReset(mmotor_S2_1);
		moveConveyor(30);
		wait1Msec(3000);
		MSMMotorEncoderReset(mmotor_S2_1);

		rotate(15, -chosenAngle);
		eraseDisplay();
	}
	motor[motorB] = motor[motorC] = 0;
}

//Drive Distance
void driveDist(float distance, int motorPow)
{
	const float ENCODERTODIST = 180/(2.75*PI);
	float encoderNum = distance * ENCODERTODIST;
	nMotorEncoder[motorA] = 0;

	motor[motorA] = motor[motorD] = motorPow;

	while(nMotorEncoder[motorA]<encoderNum)
	{}
	motor[motorA] = motor[motorD] = 0;
}

//user selects height of ball shooting
float ballHeight()
{
	eraseDisplay();
	displayString(2, "Up - high ball");
	displayString(4, "Middle - normal ball");
	displayString(6, "Down - low ball");
	int x = 0;

	while(!getButtonPress(buttonUp) && !getButtonPress(buttonEnter) && !getButtonPress(buttonDown))
	{}
	while(getButtonPress(buttonUp) || getButtonPress(buttonEnter) || getButtonPress(buttonDown))
	{
		if(getButtonPress(buttonUp))
			x = 1;
		else if(getButtonPress(buttonEnter))
			x = 2;
		else if(getButtonPress(buttonDown))
			x = 3;
	}

	if (x == 1)
	{
		displayString(8, "up was pressed");
		eraseDisplay();
		return 1.5;
	}

	else if (x == 2)
	{
		displayString(8, "enter was pressed");
		eraseDisplay();
		return 1;
	}

	else if (x == 3)
	{
		displayString(8, "down was pressed");
		eraseDisplay();
		return 0.5;
	}

	return 1;
	eraseDisplay();
}

//robot from corner to center function
void cornerToCenter(float length, float width)
{
	resetGyro(S3);
	driveDist(width/2, 25);
	wait1Msec(1000);
	rotate(10, 90);
	wait1Msec(1000);
	driveDist(length/2, 25);
	wait1Msec(1000);
	rotate(10, 90);
	wait1Msec(1000);
}

//get number of rounds
int numRounds()
{
	int rounds = 0;
	while(!getButtonPress(buttonEnter))
	{
		displayString(2, "RIGHT:  +1 Round");
		displayString(3, "LEFT:   -1 Round");
		displayString(5, "ENTER to submit");
		if(getButtonPress(buttonRight))
		{
			while(getButtonPress(buttonRight))
			{}
			rounds++;
		}
		if(rounds > 1)
		{
			if(getButtonPress(buttonLeft))
			{
				while(getButtonPress(buttonLeft))
				{}
				rounds--;
			}
		}
		displayString(11, "Number of Rounds is: %i",rounds);
	}

	eraseDisplay();
	displayString(7, "Rounds: %i", rounds);
	wait1Msec(3000);

	return rounds;
}


task main()
{
	SensorType[S2] = sensorI2CCustom;
	MSMMUXinit();

	SensorType[S3] = sensorEV3_Gyro;
	wait1Msec(50);
	SensorMode[S3] = modeEV3Gyro_Calibration;
	wait1Msec(50);
	SensorMode[S3] = modeEV3Gyro_RateAndAngle;
	wait1Msec(50);
	SensorType[S4] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S4] = modeEV3Color_Color;
	wait1Msec(50);

	int rounds = numRounds();
	float height = ballHeight();

	const int COURTDIMENSION = 135;

	for (int i = 0; i < rounds; i++)
	{
		intakeSequence();
		MSMMotorEncoderReset(mmotor_S2_1);
		cornerToCenter(COURTDIMENSION ,COURTDIMENSION*height);
		MSMMotorEncoderReset(mmotor_S2_1);
		shooting();
		MSMMotorEncoderReset(mmotor_S2_1);
		cornerToCenter(COURTDIMENSION, COURTDIMENSION*height);
		MSMMotorEncoderReset(mmotor_S2_1);
	}
}
