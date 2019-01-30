
#pragma once

#include <Arduino.h>
#include <YUKON_COMMAND.h>

class ROBOT;

class CATAPULT : public YUKON_COMMAND
{

    public:
        CATAPULT(ROBOT &refRobot);
        ROBOT &Robot;

        void Loop();

        void OISetSpeed(int16_t CatapultMotorSpeed);

        bool ForAsync(long durationMS, int16_t CatapultMotorSpeed);
        bool ForAsync(long durationMS, int16_t CatapultMotorSpeed, uint8_t HoldPercent);

    private:
        int16_t _CmdCatapultMotorSpeed = 0;
        int16_t _OICatapultMotorSpeed = 0;

};
