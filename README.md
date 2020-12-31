# A4988 Library  
## Описание
### Библиотека для работы с шаговыми моторами с помощью драйвера A4988  
### Реализовано для Олимпиады НТИ (2020)  
### Команда `VYD`   
## Документация  

Инициализация 

	A4988_Stepper::A4988_Stepper stepper(steps, step, dir);  
    A4988_Stepper::A4988_Stepper stepper(steps, step, dir, ms1, ms2, ms3); // поддержка дробления шага

Режимы работы  

    A4988_Stepper::POSE - линейное перемещение  
    A4988_Stepper::SPEED - вращение
    setMode(mode); // Установка режима работы

Дробление шага

    A4988_Stepper::FULL_STEP = 1/1
    A4988_Stepper::HALF_STEP = 1/2
    A4988_Stepper::QUARTER_STEP = 1/4
    A4988_Stepper::EIGHTH_STEP = 1/8
    A4988_Stepper::SIXTEENTH_STEP = 1/16
    setMicroStep(mode); // Установка дробления шага
    getMicroStep(); // Получение текущего дробления шага

Установка скорости в **POSE**

    setStdSpeedSteps(speed); // шаг/с
    setStdSpeedDegrees(speed); // град/с

Системы координат в **POSE**

    A4988_Stepper::ABSOLUTE - абсолютная
    A4988_Stepper::RELATIVE - относительная

Установка скорости в **SPEED**

    setTargetSpeedSteps(speed); // шаг/с
    setTargetSpeedDegrees(speed); // град/с

Получение текущей скорости

    getSpeedSteps(); // шаг/с
    getSpeedDegrees(); // град/с

Установка цели в **POSE**

    // кол-во шагов, система координат  
    setTargetPoseSteps(pose, mode); 
    setTargetPoseDegrees(pose, mode);

Получение текущего положения в **POSE**

    getPoseSteps();
    getPoseDegrees();

Использование с винтовой передачей в **POSE**

    // расстояние в мм, шаг резьбы в мм
    leadScrewMM2STEPS(distance, screw_step);
    setTargetPoseSteps(leadScrewMM2STEPS(distance, screw_step));

Использование с ременной передачей в **POSE**

    // расстояние в мм, шаг ремня в мм, кол-во зубьев на шкиве на валу
    beltMM2STEPS(distance, belt_step, number_teeth);
    setTargetPoseSteps(beltMM2STEPS(distance, belt_step, number_teeth));

Установка ускорения

    setAccelerationSteps(a); // шаг/с/с
    setAccelerationDegrees(a); // град/с/с

Остановка

    stop();

"Обнуление позиции"

    reset();

Тик

    // самый главный метод (обновление)
    tick();