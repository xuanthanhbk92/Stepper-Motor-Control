#include "mysteppermotor.h"



MyStepperMotor::MyStepperMotor(int resolution, int AplusPin, int AminusPin, int BplusPin, int BminusPin){
    m_resolution = resolution;
    m_direction = OPEN;
    currentStage = 9;
    m_Aplus = AplusPin;
    m_Aminus = AminusPin;
    m_Bplus = BplusPin;
    m_Bminus = BminusPin;
}

void MyStepperMotor::step(int numberStep){
    int noStep = 0;
    if (numberStep > 0)
    {
        m_direction = 1;
        noStep = numberStep;
    } else {
        m_direction = 0;
        noStep = -numberStep;
    }
    while (noStep) {
        moveOneStep();
        delayBetweenStep();
        noStep --;
    }
}

void MyStepperMotor::fullOpen()
{
    step(MAX_STEP);
    currentStage =9;
}

void MyStepperMotor::fullClose()
{
    step(-MAX_STEP);
    currentStage = 9;

}

void MyStepperMotor::output(int Aplus, int Bplus, int Bminus, int Aminus){
    qDebug() << "Stage:"<<currentStage <<  " Pin A+:" << Aplus<<  " Pin B+:" << Bplus<<  " Pin B-:" << Bminus<<  " Pin A-:" << Aminus;
}

void MyStepperMotor::moveOneStep(){
    if (m_direction == OPEN)
    {
        if ((currentStage == 1) || (currentStage == 9))
            currentStage =8;
        else
            currentStage -=1;
    }
    if (m_direction == CLOSE)
    {
        if((currentStage == 8) || (currentStage == 9))
            currentStage =1;
        else
            currentStage +=1;
    }
    switch (currentStage) {
    case 1:
        output(HIGH,LOW,HIGH,LOW);
        break;
    case 2:
        output(LOW,LOW,HIGH,LOW);
        break;
    case 3:
        output(LOW,LOW,HIGH,HIGH);
        break;
    case 4:
        output(LOW,LOW,LOW,HIGH);
        break;
    case 5:
        output(LOW,HIGH,LOW,HIGH);
        break;
    case 6:
        output(LOW,HIGH,LOW,HIGH);
        break;
    case 7:
        output(HIGH,HIGH,LOW,LOW);
        break;
    case 8:
        output(HIGH,LOW,LOW,LOW);
        break;
    default:
        break;
    }
}
