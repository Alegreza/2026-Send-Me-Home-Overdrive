#pragma once
#include "main.h"

class Control{
    public:
        static void opupdate();
        static void opinit();
        static void debug();
    private:
        static double drive_control_map(double input);
        static double boundBy(double l, double r, double value);
        static void controls();
        static void tankLemlibDrive();
        static void tankDrive();
        static void directiontankdrive(int direction);
        static void arcadeDrive();
        static void lemlibarcadeDrive(int direction);
        static void directionarcadeDrive(int direction);
        static void directionlemlibsinglstickarcadeDrive(int direction);
        static void curvatureDrive();
};