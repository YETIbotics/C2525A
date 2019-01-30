#include "ROBOT.h"

ROBOT::ROBOT(YETI_YUKON &rYukon) : Yukon(rYukon),
                                   DriveRight(_DriveRightPWM, &Yukon.PWM, _DriveRightDir, _DriveRightReversed),
                                   DriveLeft(_DriveLeftPWM, &Yukon.PWM, _DriveLeftDir, _DriveLeftReversed),
                                   BallLiftMotor(_BallLiftMotorPWM, &Yukon.PWM, _BallLiftMotorDir, _BallLiftMotorReversed),
                                   CatapultMotor(_CatapultMotorPWM, &Yukon.PWM, _CatapultMotorDir, _CatapultMotorReversed),
                                   Drive(*this),
                                   BallLift(*this),
                                   Catapult(*this),
                                   Auton(*this),

                                   Xbox(&Usb)

{
}

void ROBOT::Setup()
{
    Usb.Init();
    DriveRight.Init();
    DriveLeft.Init();
    BallLiftMotor.Init();
    CatapultMotor.Init();

    pinMode(_Button0, INPUT_PULLUP);
    pinMode(_LEDBuiltIn, OUTPUT);
    digitalWrite(_LEDBuiltIn, LOW);
}
bool IsHolding = false;

void ROBOT::Loop()
{
    //Read The Controller
    Usb.Task();

    if (Xbox.XboxReceiverConnected)
    {
        for (uint8_t i = 0; i < 4; i++)
        {
            if (Xbox.Xbox360Connected[i])
            {
                Drive.OISetSpeed(Yukon.XBOXJoystickTo255(Xbox.getAnalogHat(RightHatY, i), 7500), Yukon.XBOXJoystickTo255(Xbox.getAnalogHat(LeftHatY, i), 7500));
                BallLift.OISetSpeed((Xbox.getButtonPress(R1, i) * 255) - (Xbox.getButtonPress(L1, i) * 255));
                Catapult.OISetSpeed(Xbox.getButtonPress(R2, i) - Xbox.getButtonPress(L2, i));

                if (Xbox.getButtonPress(R2, i) > 0)
                    IsHolding = false;
                else if(IsHolding && Xbox.getButtonPress(L2, i) <= 100)
                    Catapult.OISetSpeed(-100);

                if (Xbox.getButtonClick(LEFT))
                    Auton.QueuePrev();
                if (Xbox.getButtonClick(RIGHT))
                    Auton.QueueNext();
                if (Xbox.getButtonClick(DOWN))
                    Auton.ToggleArmed();

                if (Xbox.getButtonClick(X))
                    Auton.LaunchQueued();

                if (Xbox.getButtonClick(A))
                    IsHolding = !IsHolding;

                if (Xbox.getButtonClick(XBOX))
                    Auton.ToggleLockArmed();
            }
        }
    }

    if (digitalRead(_Button0) == LOW)
    {
        digitalWrite(_LEDBuiltIn, HIGH);
        Yukon.SetupWIFI();
        delay(1000);
    }
    //Read The Sensors
    uint16_t LightSensorVal = Yukon.ADC.readADC(_AutonLightSensor);
    State.AutonLightSensorActive = (LightSensorVal <= _AutonLightSensorThreshold);

    //Write To Motor Controllers
    if (_NextMotorControllerWriteMillis < millis())
    {
        _NextMotorControllerWriteMillis = millis() + 20;
        DriveRight.SetMotorSpeed(State.DriveRightSpeed);
        DriveLeft.SetMotorSpeed(State.DriveLeftSpeed);
        BallLiftMotor.SetMotorSpeed(State.BallLiftMotorSpeed);
        CatapultMotor.SetMotorSpeed(State.CatapultMotorSpeed);
    }

    //Write the Display
    if (_NextDisplayMillis < millis())
    {
        _NextDisplayMillis = millis() + 250;

        if (Auton.IsArmLocked())
        {
            Yukon.OLED.clearDisplay();
            Yukon.OLED.setCursor(0, 0);
            Yukon.OLED.setTextSize(2);

            Yukon.OLED.println("LOCKED! ");

            Yukon.OLED.setTextSize(1);
            Yukon.OLED.print(Auton.QueuedProgramName());

            Yukon.OLED.display();
        }
        else if (Auton.IsArmed())
        {
            Yukon.OLED.clearDisplay();
            Yukon.OLED.setCursor(0, 0);
            Yukon.OLED.setTextSize(2);

            Yukon.OLED.print("ARMED ");
            Yukon.OLED.println(LightSensorVal);
            Yukon.OLED.setTextSize(1);
            Yukon.OLED.print(Auton.QueuedProgramName());

            Yukon.OLED.display();
        }
        else if (Auton.QueuedProgramName() != "")
        {
            Yukon.OLED.clearDisplay();
            Yukon.OLED.setCursor(0, 0);
            Yukon.OLED.setTextSize(2);

            Yukon.OLED.print(Auton.QueuedProgramName());

            Yukon.OLED.display();
        }
        else
        {
            Yukon.OLED.clearDisplay();
            Yukon.OLED.setCursor(0, 0);
            Yukon.OLED.setTextSize(2);
            Yukon.OLED.println("YUKON!");
            Yukon.OLED.display();
        }
    }
}
