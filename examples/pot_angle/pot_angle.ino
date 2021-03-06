#include<A4988_stepper.h>

// step - 3
// dir - 2
// ms1-3 = {4, 5, 7}
A4988_Stepper::A4988_Stepper stepper(A4988_Stepper::NEMA_17_STEPS_PER_TURN, 3, 2, 4, 5, 7);

void setup() {
    // режим позиционирования
    stepper.setMode(A4988_Stepper::POSE);
    // дробление шага в 1/1
    stepper.setMicroStep(A4988_Stepper::FULL_STEP);
}

void loop() {
    // обновляемся
    stepper.tick();
    // установка позиции по потенциометру
    stepper.setTargetPoseSteps(analogRead(0));
}
