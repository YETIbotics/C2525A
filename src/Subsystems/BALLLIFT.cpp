
#include "BALLLIFT.h"
#include "ROBOT.h"

BALLLIFT::BALLLIFT(ROBOT &refRobot) : Robot(refRobot)
{
}

void BALLLIFT::Loop()
{
    //Only Run Command Code When Valid
    if (!CmdTimedOut() && CmdIsRunning())
    {
        if (CmdName() == "ForAsync")
        {
            Robot.State.BallLiftMotorSpeed = _CmdBallLiftMotorSpeed;
            while (CmdUpdatePercent(millis()))
            {
                delay(20);
            }
        }
    }
    Robot.State.BallLiftMotorSpeed = _OIBallLiftMotorSpeed;

    delay(20);
}

void BALLLIFT::OISetSpeed(int16_t BallLiftMotorSpeed)
{
    _OIBallLiftMotorSpeed = BallLiftMotorSpeed;
}

bool BALLLIFT::ForAsync(long durationMS, int16_t BallLiftMotorSpeed, uint8_t HoldUntilPercent)
{
    bool retVal = ForAsync(durationMS, BallLiftMotorSpeed);
    while (CmdPercentComplete() < HoldUntilPercent && retVal)
    {
        delay(20);
    }

    return retVal;
}

bool BALLLIFT::ForAsync(long durationMS, int16_t BallLiftMotorSpeed)
{
    _CmdBallLiftMotorSpeed = BallLiftMotorSpeed;
    

    bool retVal = CmdStart("ForAsync", millis(), millis() + durationMS, durationMS + 500);

    return retVal;
}
