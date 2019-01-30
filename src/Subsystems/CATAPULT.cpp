
#include "CATAPULT.h"
#include "ROBOT.h"

CATAPULT::CATAPULT(ROBOT &refRobot) : Robot(refRobot)
{
}

void CATAPULT::Loop()
{
    //Only Run Command Code When Valid
    if (!CmdTimedOut() && CmdIsRunning())
    {
        if (CmdName() == "ForAsync")
        {
            Robot.State.CatapultMotorSpeed = _CmdCatapultMotorSpeed;
            while (CmdUpdatePercent(millis()))
            {
                delay(20);
            }
        }
    }
    Robot.State.CatapultMotorSpeed = _OICatapultMotorSpeed;

    delay(20);
}

void CATAPULT::OISetSpeed(int16_t CatapultMotorSpeed)
{
    _OICatapultMotorSpeed = CatapultMotorSpeed;
}

bool CATAPULT::ForAsync(long durationMS, int16_t CatapultMotorSpeed, uint8_t HoldUntilPercent)
{
    bool retVal = ForAsync(durationMS, CatapultMotorSpeed);
    while (CmdPercentComplete() < HoldUntilPercent && retVal)
    {
        delay(20);
    }

    return retVal;
}

bool CATAPULT::ForAsync(long durationMS, int16_t CatapultMotorSpeed)
{
    _CmdCatapultMotorSpeed = CatapultMotorSpeed;
    

    bool retVal = CmdStart("ForAsync", millis(), millis() + durationMS, durationMS + 500);

    return retVal;
}
