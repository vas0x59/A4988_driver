#include<A4988_stepper.h>


A4988_Stepper::A4988_Stepper stepper(A4988_Stepper::NEMA_17_STEPS_PER_TURN, 3, 2, 4, 5, 7);

void setup() {
    stepper.setMode(A4988_Stepper::POSE);
    stepper.setMicroStep(A4988_Stepper::QUARTER_STEP);
    // stepper.setTargetSpeedDegrees(4);
    stepper.setStdSpeedDegrees(720);
    Serial.begin(115200);
    // Serial.print(stepper.getTargetSpeedSteps());
    // stepper.setTargetPoseDegrees(360);
    // while(!stepper.targetPoseReached()) { stepper.tick();};
    // delay(500);
    // stepper.setTargetPoseDegrees(-360);
    // while(!stepper.targetPoseReached()) { stepper.tick();};
    // delay(1000);
    // delay(500);
    // stepper.setTargetPoseDegrees(-180);
    // while(!stepper.targetPoseReached()) { stepper.tick();};
    // stepper.setTargetPoseDegrees(180);
    // stepper.setMode(A4988_Stepper::SPEED);
    // stepper.setTargetSpeedDegrees(720);
}

void loop() {
    stepper.tick();
    if (Serial.available())
    {
        char c = Serial.read();
        if (c == '+')
            stepper.setTargetPoseDegrees(150, A4988_Stepper::RELATIVE);
        else if (c == 's')
            stepper.setTargetPoseDegrees(50, A4988_Stepper::RELATIVE);
        else if (c == '-')
            stepper.setTargetPoseDegrees(-150, A4988_Stepper::RELATIVE);
    }
    // delay(1000);
    // Serial.print("target speed: ");
    // Serial.print(stepper.getTargetSpeedSteps());
    // Serial.print("c speed: ");
    // Serial.print(stepper.getSpeedSteps());
    // Serial.println();
}
