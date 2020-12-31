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
enum Mode { 
    POSE,
    SPEED
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
    int _microstep = 1; // 1 2 4 8 16
    long _current_pose  = 0;  // in steps
    long _target_pose   = 0;  // in steps
    int  _current_speed = 0;  // in steps/sec
    int  _target_speed  = 0;  // in steps/sec
    int  _std_speed     = 1;
    int  _acceleration  = 0;  // in steps/sec^2
    int _steps_per_turn = 1;
    int _d_steps = 1;
    bool _going_to_target = 0;
    unsigned long _tick__prev_time = 0;
    bool _is_moving = false;
    Mode _mode = SPEED;
    PROGMEM const bool MICRO_STEP_MAP[5][3] = {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {1, 1, 0}, {1, 1, 1}};
    // bool _target_specified = 0;


public:
    // A4988_stepper()
    const unsigned int STEP_TIME = 20;
    A4988_Stepper(int steps_per_turn, int step_pin, int dir_pin) {
        _steps_per_turn = steps_per_turn;
        _step_pin = step_pin;
        _dir_pin = dir_pin;

        pinMode(_step_pin, OUTPUT);
        pinMode(_dir_pin, OUTPUT);
    };
    A4988_Stepper(int steps_per_turn, int step_pin, int dir_pin, int ms1_pin, int ms2_pin, int ms3_pin){
        _steps_per_turn = steps_per_turn;
        _step_pin = step_pin;
        _dir_pin = dir_pin;
        _ms_pins[0] = ms1_pin;
        _ms_pins[1] = ms2_pin;
        _ms_pins[2] = ms3_pin;

        pinMode(_step_pin, OUTPUT);
        pinMode(_dir_pin, OUTPUT);
        for (int i = 0; i < 3; i++) {
            pinMode(_ms_pins[i], OUTPUT);
        }
    };
    // ~A4988_Stepper();

    void   setStdSpeedSteps(double speed_s) { _std_speed = speed_s*_microstep;};
    void   setStdSpeedDegrees(double speed_d) { setStdSpeedSteps(speed_d*((float)_steps_per_turn / (360.0)));};
    // void   setSpeedRadians(float speed_r) { setSpeedSteps(_target_speed = speed_r*((float)_steps_per_turn / (2*PI)));};
    double    getStdSpeedSteps() {return _std_speed/_microstep;};
    double    getStdSpeedDegrees() {return getStdSpeedSteps()*(360.0/_steps_per_turn);};
    // float  getSpeedRadians() {return _current_speed*((2*PI)/_steps_per_turn);}
    
    void   setTargetSpeedSteps(double speed_s) { _target_speed = speed_s*_microstep;_is_moving = true;};
    void   setTargetSpeedDegrees(double speed_d) { setTargetSpeedSteps(speed_d*((float)_steps_per_turn / (360.0)));};

    double    getTargetSpeedSteps() {return (double)_target_speed/_microstep;};
    double    getTargetSpeedDegrees() {return getTargetSpeedSteps()*(360.0/_steps_per_turn);};
    // float  getTargetSpeedRadians() {return _target_speed*((2*PI)/_steps_per_turn);};
    double   getSpeedSteps() {return (double)_current_speed/_microstep;};
    double   getSpeedDegrees() {return getSpeedSteps()*(360.0/_steps_per_turn);};



    double leadScrew(double distance, double screw_step) { return ((double)_steps_per_turn*(double)_microstep/screw_step) * distance; }
    double belt(double distance, double belt_step, int number_teeth) { return ((double)_steps_per_turn*(double)_microstep/(belt_step*(double)number_teeth)) * distance; }



    void   setTargetPoseSteps(double pose_s, TargetMode mode = ABSOLUTE) { _target_pose = pose_s*_microstep;  _is_moving = true; _going_to_target = true;};
    void   setTargetPoseDegrees(double pose_d, TargetMode mode = ABSOLUTE) { setTargetPoseSteps(pose_d*((double)_steps_per_turn / (360.0)));};
    // void   setTargetRadians(double pose_r, TargetMode mode = ABSOLUTE) { setTargetSteps(pose_r*((float)_steps_per_turn / (2*PI)));};
    double   getTargetPoseSteps() {return (double)_target_pose/_microstep;};
    double   getTargetPoseDegrees() {return getTargetPoseDegrees()*(360.0/_steps_per_turn);};
    // double getTargetRadians() {return _target_pose*((2*PI)/_steps_per_turn);};

    double   getPoseSteps() {return (double)_current_pose/_microstep;};
    double   getPoseDegrees() {return getPoseSteps()*(360.0/_steps_per_turn);};
    // double getPoseRadians() {return _current_pose*((2*PI)/_steps_per_turn);};



    // void setAccelerationSteps(int a) { _acceleration = a;};
    // void setAccelerationDegrees(int a) { setAccelerationSteps(a*((float) / (360.0)));};
    // void setAccelerationRadians(float a) { setAccelerationSteps(a*((float) / (2*PI));};
    // int getAccelerationSteps() {return _acceleration;};
    // int getAccelerationDegrees() {return _acceleration*(360.0/_steps_per_turn);};
    // float getAccelerationRadians() {return _acceleration*((2*PI)/_steps_per_turn);};
    
    void setMode(Mode mode) {_mode = mode;};

    bool targetPoseReached() {return !_going_to_target;};

    void stop() {
        _target_speed = 0;
        _is_moving = 0;
    };
    // void stop() {};
    
    bool tick() {
        if (_mode == POSE && _going_to_target) {
            long delta = _target_pose - _current_pose;
            _target_speed = (_std_speed)*(delta > 0 ? 1 : -1);
            if (delta == 0) {
                _going_to_target = false;
                stop();
            }
        }
        _current_speed = _target_speed;
        if (_current_speed != 0) {
            unsigned long mc_b_steps = 1000000 / abs(_current_speed);
            unsigned long mc_now = micros();
            if (_is_moving && (mc_now - _tick__prev_time) >= mc_b_steps) {
                _tick__prev_time = mc_now;
                
                    
                    // if(_mode == POSE &&  delta == 0) {
                    //     stop();
                    // }
                    // else {
                        _current_pose += (_current_speed > 0 ? 1 : -1);
                        
                        // STEP
                        // if (_mode == SPEED)
                        // Serial.println("STEP: ");
                        Serial.println(_current_speed);
                        digitalWrite(_dir_pin, _current_speed > 0);
                        digitalWrite(_step_pin, 1);
                        delayMicroseconds(STEP_TIME);
                        digitalWrite(_step_pin, 0);
                        delayMicroseconds(STEP_TIME);
                    // }
            }
        }
        else
        {
            _is_moving = false;
        }
        
        
        return _is_moving;
    };
    void reset() {_current_pose = 0; };
    void setMicroStep(MicroStepMode mode) {
        _microstep = mode;
        if (_ms_pins[0] != -1) 
            for (int i = 0; i < 3; i++) {
                if (mode == FULL_STEP) {
                    digitalWrite(_ms_pins[i], MICRO_STEP_MAP[0][i]);
                }
                else if (mode == HALF_STEP) {
                    digitalWrite(_ms_pins[i], MICRO_STEP_MAP[1][i]);
                }
                else if (mode == QUARTER_STEP) {
                    digitalWrite(_ms_pins[i], MICRO_STEP_MAP[2][i]);
                }
                else if (mode == EIGHTH_STEP) {
                    digitalWrite(_ms_pins[i], MICRO_STEP_MAP[3][i]);
                }
                else if (mode == SIXTEENTH_STEP) {
                    digitalWrite(_ms_pins[i], MICRO_STEP_MAP[4][i]);
                }
                // digitalWrite(_ms_pins[i], MICRO_STEP_MAP[mode][i]);
            }
    };
};

}