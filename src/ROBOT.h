#ifndef ROBOT_h
#define ROBOT_h

#include <YETI_YUKON.h>
#include <STATE.h>

#include <XBOXRECV.h>

#include <YUKON_CytronMD10.h>

#include "Subsystems\Drive.h"
#include "Subsystems\BallLift.h"
#include "Subsystems\Catapult.h"

#include "Autonomous\AUTONOMOUS.h"

class ROBOT
{
  public:
    ROBOT(YETI_YUKON &rYukon);

    void Setup();
    void Loop();

    YETI_YUKON &Yukon;

    STATE State;

    //Motors
    YUKON_CytronMD10 DriveRight;
    YUKON_CytronMD10 DriveLeft;
    YUKON_CytronMD10 BallLiftMotor;
    YUKON_CytronMD10 CatapultMotor;

    //Subsystems
    DRIVE Drive;
    BALLLIFT BallLift;
    CATAPULT Catapult;
    AUTONOMOUS Auton;

    //USB Items
    USB Usb;
    
    XBOXRECV Xbox;
    
    
   

    //PIN Declarations
    static const int _DriveRightPWM = 0;
    static const int _DriveRightDir = 14;
    static const bool _DriveRightReversed = false;
        
    static const int _DriveLeftPWM = 1;
    static const int _DriveLeftDir = 17;
    static const bool _DriveLeftReversed = true;
        
    static const int _BallLiftMotorPWM = 2;
    static const int _BallLiftMotorDir = 21;
    static const bool _BallLiftMotorReversed = false;
        
    static const int _CatapultMotorPWM = 3;
    static const int _CatapultMotorDir = 22;
    static const bool _CatapultMotorReversed = false;
        

    static const uint8_t _Button0 = 0;
    static const uint8_t _LEDBuiltIn = 25;
    static const uint8_t _AutonLightSensor = 0;
    
    static const uint16_t _AutonLightSensorThreshold = 150; //Value 0 - 1024

  private:
      long _NextDisplayMillis = 0;
      long _NextMotorControllerWriteMillis = 0;
};

#endif