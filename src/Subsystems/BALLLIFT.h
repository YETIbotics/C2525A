
#pragma once

#include <Arduino.h>
#include <YUKON_COMMAND.h>

class ROBOT;

class BALLLIFT : public YUKON_COMMAND
{

    public:
        BALLLIFT(ROBOT &refRobot);
        ROBOT &Robot;

        void Loop();

        void OISetSpeed(int16_t BallLiftMotorSpeed);

        bool ForAsync(long durationMS, int16_t BallLiftMotorSpeed);
        bool ForAsync(long durationMS, int16_t BallLiftMotorSpeed, uint8_t HoldPercent);

    private:
        int16_t _CmdBallLiftMotorSpeed = 0;
        int16_t _OIBallLiftMotorSpeed = 0;

};
