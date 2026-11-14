#pragma once
#include "main.h"

class Autonomous{
    public:
        static void init();
        static void tuneAngularPID();
        static void tuneLateralPID();
        static void constantlyPrintPose();
        static void RedDriveMech();
        static void BlueDriveMech();
        static void move(int time);
        static void stop();
        static void IntakeMech();
        static void outtaketomid();
};