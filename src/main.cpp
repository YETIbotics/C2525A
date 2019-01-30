#include <Arduino.h>
#include <Wire.h>

#include <YETI_YUKON.h>
#include <ROBOT.h>

YETI_YUKON Yukon("YOURROBOTNAME", "571653a9-45e9-40ee-bae1-b421d8fe9893");
ROBOT Robot(Yukon);

void WatchdogTask(void *pvParameters);
void DriveTask(void *pvParameters);
void BallLiftTask(void *pvParameters);
void CatapultTask(void *pvParameters);
void AutonTask(void *pvParameters);

void setup()
{
    Serial.begin(115200);

    Wire.begin(4, 15, 400000);

    Yukon.Setup();
    Robot.Setup();

    Serial.print("MainLoop: Executing on core ");
    Serial.println(xPortGetCoreID());

    xTaskCreatePinnedToCore(WatchdogTask, "WatchdogTask", 10000, NULL, 1, NULL, 1);
    xTaskCreatePinnedToCore(DriveTask, "DriveTask", 10000, NULL, 1, NULL, 1);
    xTaskCreatePinnedToCore(BallLiftTask, "BallLiftTask", 10000, NULL, 1, NULL, 1);
    xTaskCreatePinnedToCore(CatapultTask, "CatapultTask", 10000, NULL, 1, NULL, 1);
    xTaskCreatePinnedToCore(AutonTask, "AutonTask", 10000, NULL, 1, NULL, 1);
}

void loop()
{
    Yukon.Loop(); 
    Robot.Loop();

    delay(1);
    yield();
}

void WatchdogTask(void *pvParameters)
{
    Serial.print("WatchdogTask: Executing on core ");
    Serial.println(xPortGetCoreID());

        Yukon.EnableWatchdog();
        while (true)
        {
            Yukon.WatchdogLoop();
            delay(100);
        }
    }

void DriveTask(void *pvParameters)
{
    Serial.print("DriveTask: Executing on core ");
    Serial.println(xPortGetCoreID());

        while (true)
        {
            Robot.Drive.Loop();
        }
    }
    
void BallLiftTask(void *pvParameters)
{
    Serial.print("BallLiftTask: Executing on core ");
    Serial.println(xPortGetCoreID());

        while (true)
        {
            Robot.BallLift.Loop();
        }
    }
    
void CatapultTask(void *pvParameters)
{
    Serial.print("CatapultTask: Executing on core ");
    Serial.println(xPortGetCoreID());

        while (true)
        {
            Robot.Catapult.Loop();
        }
    }
    

void AutonTask(void *pvParameters)
{
    Serial.print("AutonTask: Executing on core ");
    Serial.println(xPortGetCoreID());
    Robot.Auton.Setup();

    while(true)
    {
        Robot.Auton.Loop();
    }
}