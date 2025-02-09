#include "Arduino.h"
class RoboCar{
    private:

    public:
        int MeasureDistance();
        void DriveForward(int);
        void DriveReverse(int);
        void DriveSpinRight(int);
        void DriveSpinLeft(int);
        void DriveStop();

    
};