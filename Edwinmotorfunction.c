// Motor Encoder = 230 degrees

//MTE 121 - Shell Game Robot
//=========================================
const int RED_COL = (int)colorRed;
const int BLUE_COL = (int)colorBlue;
const char RED_WIN_POS = 'r';
const char BLUE_WIN_POS = 'l';
const int MAX_MIX_MOVES = 12;
const int ULTRASONIC_LENGTH = 50; //cm
const int HALF_TURN = 180;
const int SWITCH_ROT = 230;
const int CC = -1; //Counter Clockwise
const int CW = 1; //Clockwise
const int MOT_SPEED = 30;
const int STOP_SPEED = 0;
const int MIX_TURN = 230;
const int RESET_TURN = 55;

const tSensors ULTSON_SEN_PORT = S1;
const tSensors COLOUR_SEN_PORT = S2;
const tSensors TOUCH_SEN_PORT = S3;
const tMotor RIGHT_MIX_MOTOR = motorA;
const tMotor LEFT_MIX_MOTOR = motorD;
const tMotor CENTER_MOTOR = motorB;
//=========================================
char RedMotorMixMoves[MAX_MIX_MOVES] = {'L', 'L', 'R', 'R', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'L'};
int RedDirMixMoves[MAX_MIX_MOVES] = {1, -1, -1, 1, 1, 1, 1, -1, 1, -1, 1, 1};
int RedNumSpins[MAX_MIX_MOVES] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

char BlueMotorMixMoves[MAX_MIX_MOVES] = {'L', 'R', 'L', 'R', 'L', 'R', 'L', 'R', 'L', 'R', 'L', 'R'};
int BlueDirMixMoves[MAX_MIX_MOVES] = {1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1};
int BlueNumSpins[MAX_MIX_MOVES] = {1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3};
//=========================================
void calibrateSensors(tSensors ultson_port, tSensors colour_port, tSensors touch_port);
int senseGamePiece(tSensors colour_port);
void motorMix(char mixMoves, int dirMoves, int numSpins);
bool tooClose(tSensors ultsonPort);
char getPlayerGuess(tSensors touchsensorPort);
void centerGuess(char playerGuess, tMotor rightMotorPort, tMotor leftMotorPort);
char pieceEnding(int colourScanned);
bool guessCorrectness(int colourScanned, char playerGuess);
void liftChoice(tMotor motorPortsMedium);
//=========================================
task main()
{
	calibrateSensors(ULTSON_SEN_PORT, COLOUR_SEN_PORT, TOUCH_SEN_PORT);

	int gamePiece = senseGamePiece(COLOUR_SEN_PORT);
	char usingMotorMixMoves[MAX_MIX_MOVES];
	int usingDirMixMoves[MAX_MIX_MOVES];
	int usingNumSpins[MAX_MIX_MOVES];
	// if (gamePiece == RED_COL)
	// {
	// 	usingMotorMixMoves = RedMotorMixMoves;
	// 	usingDirMixMoves = RedDirMixMoves;
	// 	usingNumSpins = RedNumSpins;
	// 	//char usingMotorMixMoves[MAX_MIX_MOVES] = {'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L'};
	// 	//int usingDirMixMoves[MAX_MIX_MOVES] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	// 	//int usingNumSpins[MAX_MIX_MOVES] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	// }
	// else
	// {
	// 	usingMotorMixMoves = BlueMotorMixMoves;
	// 	usingDirMixMoves = BlueDirMixMoves;
	// 	usingNumSpins = BlueNumSpins;
	// }
	eraseDisplay();
	// for (int count = 0; count <= MAX_MIX_MOVES; count++)
	// {
	// 	displayString(4, "motor: %c", usingMotorMixMoves[count]);
	// 	displayString(5, "dir: %d", usingDirMixMoves[count]);
	// 	displayString(6, "spins: %d", usingNumSpins[count]);
	// 	wait1Msec(2000);
	// 	eraseDisplay();
	// }

	//UPDATED MOTORMIX FUNCTIONS
	if(gamePiece == RED_COL)
	{
		for (int moves = 0; moves < MAX_MIX_MOVES; moves++)
		{
			motorMix(RedMotorMixMoves[moves], RedDirMixMoves[moves], RedNumSpins[moves]);
		}
	}
	else
	{
		for (int moves = 0; moves < MAX_MIX_MOVES; moves++)
		{
			motorMix(BlueMotorMixMoves[moves], BlueDirMixMoves[moves], BlueNumSpins[moves]);
		}
	}

    if(gamePiece == RED_COL)
    {
        displayString(7, "adsfkahsdfkjasfh REDREDREDRED");

        for(int moves = 0; moves < MAX_MIX_MOVES; moves++)
        {
            nMotorEncoder[LEFT_MIX_MOTOR] = 0;
            nMotorEncoder[RIGHT_MIX_MOTOR] = 0;

            displayString(8, "moves number is %d", moves);
            char motSide = RedMotorMixMoves[moves];

            if(RedMotorMixMoves[moves] == 'L')
            {
                displayString(2, "LEFTTTT side spinnnnnnnn");
                if(RedDirMixMoves[moves] == CW)
                {
                    motor[LEFT_MIX_MOTOR] = MOT_SPEED;
                    while(nMotorEncoder[LEFT_MIX_MOTOR] <= (230 + 180 * (RedNumSpins[moves]-1)))
                    {}
                    motor[LEFT_MIX_MOTOR] = STOP_SPEED;

                }

                else
                {
                    motor[LEFT_MIX_MOTOR] = -MOT_SPEED;
                    while(nMotorEncoder[LEFT_MIX_MOTOR] >= -(230 + 180 * (RedNumSpins[moves]-1)))
                    {}
                    motor[LEFT_MIX_MOTOR] = STOP_SPEED;
                }
            }

            else if (RedMotorMixMoves[moves] == 'R')
            {
                displayString(2, "RIGHTTHTHTHT side spinnnnnnnn");
                if(RedDirMixMoves[moves] == CW)
                {
                    motor[RIGHT_MIX_MOTOR] = -MOT_SPEED;
                    while(nMotorEncoder[RIGHT_MIX_MOTOR] >= -(230 + (180 * (RedNumSpins[moves]-1))))
                    {}
                    motor[RIGHT_MIX_MOTOR] = STOP_SPEED;
                    nMotorEncoder[RIGHT_MIX_MOTOR] = 0;
                }

                else
                {
                    motor[RIGHT_MIX_MOTOR] = MOT_SPEED;
                    while(nMotorEncoder[RIGHT_MIX_MOTOR] <= (230 + (180 * (RedNumSpins[moves]-1))))
                    {}
                    motor[RIGHT_MIX_MOTOR] = STOP_SPEED;
                }
            }
            wait1Msec(50);
        }
    }
    else
    {
        for(int moves = 0; moves < MAX_MIX_MOVES; moves++)
        {
            nMotorEncoder[LEFT_MIX_MOTOR] = 0;
            nMotorEncoder[RIGHT_MIX_MOTOR] = 0;
            char motSide = BlueMotorMixMoves[moves];
            if(motSide == 'L')
            {

                if(BlueDirMixMoves[moves] == CW)
                {
                    motor[LEFT_MIX_MOTOR] = MOT_SPEED;
                    while(nMotorEncoder[LEFT_MIX_MOTOR] <= (230 + 180 * (BlueNumSpins[moves]-1)))
                    {}
                    motor[LEFT_MIX_MOTOR] = STOP_SPEED;

                }

                else
                {
                    motor[LEFT_MIX_MOTOR] = MOT_SPEED;
                    while(nMotorEncoder[LEFT_MIX_MOTOR] >= (230 + 180 * (BlueNumSpins[moves]-1)))
                    {}
                    motor[LEFT_MIX_MOTOR] = STOP_SPEED;
                }
            }

            else
            {

                if(BlueDirMixMoves[moves] == CW)
                {
                    motor[RIGHT_MIX_MOTOR] = MOT_SPEED;
                    while(nMotorEncoder[RIGHT_MIX_MOTOR] <= (230 + 180 * (BlueNumSpins[moves]-1)))
                    {}
                    motor[RIGHT_MIX_MOTOR] = STOP_SPEED;

                }

                else
                {
                    motor[RIGHT_MIX_MOTOR] = MOT_SPEED;
                    while(nMotorEncoder[LEFT_MIX_MOTOR] >= (230 + 180 * (BlueNumSpins[moves]-1)))
                    {}
                    motor[RIGHT_MIX_MOTOR] = STOP_SPEED;
                }
            }

             wait1Msec(50);
        }
    }

	// for (int count = 0; count < MAX_MIX_MOVES; count++)
	// {
	// 	motorMix(usingMotorMixMoves[count], usingDirMixMoves[count], usingNumSpins[count]);
	// 	displayString(4, "count: %d", count);
	// 	wait1Msec(2000);
	// }
	displayString(5, "%d", gamePiece);
	wait1Msec(5000);
}
//=========================================
void calibrateSensors(tSensors ultson_port, tSensors colour_port, tSensors touch_port)
{
	SensorType[COLOUR_SEN_PORT] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[COLOUR_SEN_PORT] = modeEV3Color_Color;
	wait1Msec(50);
	SensorType[ULTSON_SEN_PORT] = sensorEV3_Ultrasonic;
	wait1Msec(50);
	SensorType[TOUCH_SEN_PORT] = sensorEV3_Touch;
	wait1Msec(50);
}

int senseGamePiece(tSensors colour_port)
{
	int scannedColour = 0;
	string scannedColourName = "";
	bool scanFlag = false;
	displayString(5, "PLEASE SCAN A RED OR BLUE BRICK");
	while(scanFlag == false)
	{
		if (SensorValue[COLOUR_SEN_PORT] == RED_COL)
		{
			scannedColourName = "RED";
			scannedColour = RED_COL;
			scanFlag = true;
		}
		else if (SensorValue[COLOUR_SEN_PORT] == BLUE_COL)
		{
			scannedColourName = "BLUE";
			scannedColour = BLUE_COL;
			scanFlag = true;
		}
	}
	eraseDisplay();
	displayString(5, "PLEASE PLACE YOUR %s BRICK UNDER THE CENTER CUP", scannedColourName);
	displayString(6, "PRESS THE TOUCH SENSOR WHEN DONE");
	while (SensorValue[TOUCH_SEN_PORT] == 0)
	{}
	eraseDisplay();
	return scannedColour;
}

void motorMix(char mixMoves, int dirMoves, int numSpins)
{

    nMotorEncoder[LEFT_MIX_MOTOR] = 0;
    nMotorEncoder[RIGHT_MIX_MOTOR] = 0;

    displayString(8, "moves number is %d", dirMoves);
    char motSide = mixMoves;

    if(mixMoves == 'L')
    {
        displayString(2, "LEFTTTT side spinnnnnnnn");
        if(dirMoves == CW)
        {
            motor[LEFT_MIX_MOTOR] = MOT_SPEED;
            while(nMotorEncoder[LEFT_MIX_MOTOR] <= (230 + 180 * (numSpins - 1)))
            {}
            motor[LEFT_MIX_MOTOR] = STOP_SPEED;

            nMotorEncoder[LEFT_MIX_MOTOR] = 0;
            motor[LEFT_MIX_MOTOR] = -MOT_SPEED;
            while(abs(nMotorEncoder[LEFT_MIX_MOTOR]) < RESET_TURN)
            {}
            motor[LEFT_MIX_MOTOR] = STOP_SPEED;

        }

        else
        {
            motor[LEFT_MIX_MOTOR] = -MOT_SPEED;
            while(nMotorEncoder[LEFT_MIX_MOTOR] >= -(230 + 180 * (numSpins - 1)))
            {}
            motor[LEFT_MIX_MOTOR] = STOP_SPEED;

            nMotorEncoder[LEFT_MIX_MOTOR] = 0;
            motor[LEFT_MIX_MOTOR] = MOT_SPEED;
            while(abs(nMotorEncoder[LEFT_MIX_MOTOR]) < RESET_TURN)
            {}
            motor[LEFT_MIX_MOTOR] = STOP_SPEED;
        }
    }

    else if (mixMoves == 'R')
    {
        displayString(2, "RIGHTTHTHTHT side spinnnnnnnn");
        if(dirMoves == CW)
        {
            motor[RIGHT_MIX_MOTOR] = -MOT_SPEED;
            while(nMotorEncoder[RIGHT_MIX_MOTOR] >= -(MIX_TURN + (HALF_TURN * (numSpins-1))))
            {}
            motor[RIGHT_MIX_MOTOR] = STOP_SPEED;

            nMotorEncoder[RIGHT_MIX_MOTOR] = 0;
            motor[RIGHT_MIX_MOTOR] = MOT_SPEED;
            while(abs(nMotorEncoder[RIGHT_MIX_MOTOR]) < RESET_TURN)
            {}
            motor[RIGHT_MIX_MOTOR] = STOP_SPEED;
        }

        else
        {
            motor[RIGHT_MIX_MOTOR] = MOT_SPEED;
            while(nMotorEncoder[RIGHT_MIX_MOTOR] <= (MIX_TURN + (HALF_TURN * (numSpins-1))))
            {}
            motor[RIGHT_MIX_MOTOR] = STOP_SPEED;

            nMotorEncoder[RIGHT_MIX_MOTOR] = 0;
            motor[RIGHT_MIX_MOTOR] = -MOT_SPEED;
            while(abs(nMotorEncoder[RIGHT_MIX_MOTOR]) < RESET_TURN)
            {}
            motor[RIGHT_MIX_MOTOR] = STOP_SPEED;
        }
    }
    wait1Msec(100);
}

void motorMix(char arrayMotor, int arrayDirection, int arraySpins)
{


	// for(int moves = 0; moves <= MAX_MIX_MOVES; moves++)
	// {
	// char *motChoice[MAX_MIX_MOVES] = arrayMotor;
	// 	if(motChoice == 'L')
    //     {

    //         if(arrayDirection[moves] == CW)
    //         {
    //             motor[LEFT_MIX_MOTOR] = MOT_SPEED;
    //             while(nMotorEncoder[LEFT_MIX_MOTOR] <= (230 + 180 * arraySpins[moves]))
    //             {}
    //             motor[LEFT_MIX_MOTOR] = STOP_SPEED;

    //         }

    //         else
    //         {
    //             motor[LEFT_MIX_MOTOR] = MOT_SPEED;
    //             while(nMotorEncoder[LEFT_MIX_MOTOR] >= (230 + 180 * arraySpins[moves]))
    //             {}
    //             motor[LEFT_MIX_MOTOR] = STOP_SPEED;
    //         }
    //     }

    //     else
    //     {

    //         if(arrayDirection[moves] == CW)
    //         {
    //             motor[RIGHT_MIX_MOTOR] = MOT_SPEED;
    //             while(nMotorEncoder[RIGHT_MIX_MOTOR] <= (230 + 180 * arraySpins[moves]))
    //             {}
    //             motor[RIGHT_MIX_MOTOR] = STOP_SPEED;

    //         }

    //         else
    //         {
    //             motor[RIGHT_MIX_MOTOR] = MOT_SPEED;
    //             while(nMotorEncoder[LEFT_MIX_MOTOR] >= (230 + 180 * arraySpins[moves]))
    //             {}
    //             motor[RIGHT_MIX_MOTOR] = STOP_SPEED;
    //         }
    //     }
	// }



	// tMotor turnMotor = motorC;
    // if(arrayMotor == 'R')
    //     turnMotor = RIGHT_MIX_MOTOR;
    // else
    //     turnMotor = LEFT_MIX_MOTOR;
    // int turnDist = (arraySpins * 360) + MIX_TURN;
    // if(arrayDirection == 1)
    // {
    //     nMotorEncoder[turnMotor] = 0;
    //     motor[turnMotor] = MOT_SPEED;
    //     while (nMotorEncoder[turnMotor] < turnDist)
    //     {}
    //   	motor[turnMotor] = STOP_SPEED;
    //     nMotorEncoder[turnMotor] = 0;
    //     motor[turnMotor] = -MOT_SPEED;
    //     while (nMotorEncoder[turnMotor] > RESET_TURN)
    //     {}
    //   	motor[turnMotor] = STOP_SPEED;
    // }
    // else
    // {
    // 		nMotorEncoder[turnMotor] = 0;
    //     motor[turnMotor] = -MOT_SPEED;
    //     while (nMotorEncoder[turnMotor] > -turnDist)
    //     {}
    //   	motor[turnMotor] = STOP_SPEED;
    //     nMotorEncoder[turnMotor] = 0;
    //     motor[turnMotor] = MOT_SPEED;
    //     while (nMotorEncoder[turnMotor] < -RESET_TURN)
    //     {}
    //   	motor[turnMotor] = STOP_SPEED;
    // }
    // displayString(5, "In motorMix");
}




bool tooClose(tSensors ultsonPort)
{
	if(SensorValue[ultsonPort]<ULTRASONIC_LENGTH)
	{
		//if the player is too close
		displayString(4,"PLAYER IS TOO CLOSE");
		playSound(soundBeepBeep);
		return true;
	}
	else
	{
		//if the player is far enough away
		displayString(2,"Player distance: %d",SensorValue[ultsonPort]);
		return false;
	}
}

char getPlayerGuess(tSensors touchsensorPort)
{
	char playerGuess = 'a';
	while(!getButtonPress(buttonAny))
	{}
	if(getButtonPress(buttonEnter))
		playerGuess = 'c';
	else if(getButtonPress(buttonRight))
		playerGuess = 'r';
	else if(getButtonPress(buttonLeft))
		playerGuess = 'l';
	while(!getButtonPress(buttonAny))
	{}
	return playerGuess;
}

void centerGuess(char playerGuess, tMotor rightMotorPort, tMotor leftMotorPort)
{
	if(playerGuess == 'R')
	{
		nMotorEncoder[RIGHT_MIX_MOTOR] = 0;

		motor[RIGHT_MIX_MOTOR] = 15;
		while(nMotorEncoder[RIGHT_MIX_MOTOR] < HALF_TURN)
		{}
		motor[RIGHT_MIX_MOTOR] = 0;
	}

	else if(playerGuess == 'L')
	{
		nMotorEncoder[LEFT_MIX_MOTOR] = 0;

		motor[LEFT_MIX_MOTOR] = 15;
		while(nMotorEncoder[LEFT_MIX_MOTOR] < HALF_TURN)
		{}
		motor[LEFT_MIX_MOTOR] = 0;
	}
}

char pieceEnding(int colourScanned)
{
	if(colourScanned == RED_COL)
		return RED_WIN_POS;
	else
		return BLUE_WIN_POS;
}

bool guessCorrectness(char pieceEnding, char playerGuess)
{
	if(pieceEnding == playerGuess)
		return true;
	else
		return false;
}

//add lift function
