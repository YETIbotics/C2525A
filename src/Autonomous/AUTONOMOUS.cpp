#include "AUTONOMOUS.h"
#include "ROBOT.h"

AUTONOMOUS::AUTONOMOUS(ROBOT &refRobot) : Robot(refRobot)
{
    _MaxProgramNumber = 4;
}

void AUTONOMOUS::Loop()
{
    if (_AutonARMED)
    {
        if (Robot.State.AutonLightSensorActive)
        {
            LaunchQueued();
        }
    }

    if (_RunningAuton == "Auton1") ExecAuton1();
    else if(_RunningAuton == "Auton2") ExecAuton2();
    else if(_RunningAuton == "Auton3") ExecAuton3();
    else if(_RunningAuton == "Auton4") ExecAuton4();

     _RunningAuton = "";
    delay(20);
}

void AUTONOMOUS::ExecAuton1()
{
    Robot.BallLift.ForAsync(2000, -255, 5);
    Robot.Catapult.ForAsync(2000, -200, 100);
    Robot.Catapult.ForAsync(500, 255, 100);
    Robot.Drive.ForAsync(2000, 245, 240, 100);
    Robot.Drive.ForAsync(1750, -210, -200, 100);
    Robot.Drive.ForAsync(1500, 70, -100, 100);
    Robot.BallLift.ForAsync(3000, 255, 5);
    Robot.Drive.ForAsync(1000, 250, 235, 100);
}
void AUTONOMOUS::ExecAuton2()
{
    //  Robot.Drive.ForAsync(500, 90, 80, 100);
    Robot.BallLift.ForAsync(2000, -255, 5);
    Robot.Catapult.ForAsync(2000, -150, 100);
    Robot.Catapult.ForAsync(500, 255, 100);
    Robot.Drive.ForAsync(2000, 245, 240, 100);
    Robot.Drive.ForAsync(1750, -210, -200, 100);
    Robot.Drive.ForAsync(1500, 70, -100, 100);
    Robot.BallLift.ForAsync(3000, 255, 5);
    Robot.Drive.ForAsync(1000, 250, 235, 100);
}
void AUTONOMOUS::ExecAuton3()
{
    Robot.BallLift.ForAsync(2000, -255, 5);
    Robot.Catapult.ForAsync(2000, -175, 100);
    Robot.Catapult.ForAsync(500, 255, 100);
    Robot.Drive.ForAsync(2000, 245, 240, 100);
    Robot.Drive.ForAsync(1750, -210, -200, 100);
    Robot.Drive.ForAsync(1500, 80, -95, 100);
    Robot.BallLift.ForAsync(3000, 255, 5);
    Robot.Drive.ForAsync(2200, 250, 235, 100);
    // Robot.Drive.ForAsync(3000, 190, 200, 100);
    // Robot.BallLift.ForAsync(2500, 255, 100);
}
void AUTONOMOUS::ExecAuton4()
{
    Robot.Drive.ForAsync(100, 10, 10, 100);
}