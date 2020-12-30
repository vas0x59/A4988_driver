#pragma once

#include <Arduino.h>

namespace A4988_Stepper {

const int NEMA_17_STEPS_PER_TURN = 200;

enum MicroStepMode {
    FULL_STEP = 1,
    HALF_STEP = 2,
    QUARTER_STEP = 4,
    EIGHTH_STEP = 8,
    SIXTEENTH_STEP = 16
};
enum TargetMode {
    ABSOLUTE,
    RELATIVE
};

// struct Stepper {
//     int steps_per_turn;
//     int max_acceleration;
//     int max_speed;
//     int min_speed;
// };

class A4988_Stepper
{
private:
    int _step_pin, _dir_pin;
    int _ms_pins[3] = {-1, -1, -1};
    int _misrostep = 1;

public:
    // A4988_stepper()
    A4988_Stepper(int steps_per_turn, int step_pin, int dir_pin);
    A4988_Stepper(int steps_per_turn, int step_pin, int dir_pin, int ms1_pin, int ms2_pin, int ms3_pin);
    ~A4988_Stepper();

    void setSpeedSteps(int speed_s);
    void setSpeedDegrees(int speed_d);
    void setSpeedRadians(float speed_r);
    
    void setTargetSteps(long pose_s, TargetMode mode = ABSOLUTE);
    void setTargetDegrees(long pose_d, TargetMode mode = ABSOLUTE);
    void setTargetRadians(double pose_r, TargetMode mode = ABSOLUTE);

    
    bool tick();
    void reset();
    void setMicroStep(int mode);
    void setMicroStep(MicroStepMode mode);
};

}