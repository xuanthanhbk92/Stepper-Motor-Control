
/*
 Stepper Motor Control - one step at a time

 This program drives a unipolar or bipolar stepper motor.
 The motor is attached to digital pins 8 - 11 of the Arduino.

 The motor will step one step at a time, very slowly.  You can use this to
 test that you've got the four wires of your stepper wired to the correct
 pins. If wired correctly, all steps should be in the same direction.

 Use this also to count the number of steps per revolution of your motor,
 if you don't know it.  Then plug that number into the oneRevolution
 example to see if you got it right.

 Created 30 Nov. 2009
 by Tom Igoe

 */

#include <Stepper.h>


class MyStepperMotor
{
public:
    MyStepperMotor(int resolution,int AplusPin, int AminusPin, int BplusPin , int BminusPin );  // resolution and control pin
    void step( int numberStep);
    void fullClose();
    void fullOpen();
private:
    void delayBetweenStep(){
        delay(100);
    }

    enum {
        OPEN =1,
        CLOSE =0
    };
    void output(int Aplus, int Bplus , int Bminus,int Aminus  );
    void moveOneStep();
    int m_resolution;
    int m_Aplus , m_Aminus , m_Bplus , m_Bminus;
    int m_direction;  // 1 Open  0 close
    /*
     *  1   2   3   4   5   6   7   8
     A  H   L   L   L   L   L   H   H
     B  L   L   L   L   H   H   H   L
     B- H   H   H   L   L   L   L   L
     A- L   L   H   H   H   L   L   L
     *
     * Open-> Close : 1-> 8
     * Close-> Open : 8-> 1
     *
     * Full open at stage 1
     */
    int currentStage = 9; // idle

};

MyStepperMotor::MyStepperMotor(int resolution, int AplusPin, int AminusPin, int BplusPin, int BminusPin){
        m_resolution = resolution;
        m_direction = OPEN;
        currentStage = 9;
        m_Aplus = AplusPin;
        m_Aminus = AminusPin;
        m_Bplus = BplusPin;
        m_Bminus = BminusPin;

        // set up pin 
        pinMode(m_Aplus, OUTPUT);
        pinMode(m_Aminus, OUTPUT);
        pinMode(m_Bplus, OUTPUT);
        pinMode(m_Bminus, OUTPUT);
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
void MyStepperMotor::fullClose(){
  step(-164);
  currentStage = 9;
}

void MyStepperMotor::fullOpen(){
  step(164);
  currentStage = 9;
}

void MyStepperMotor::output(int Aplus, int Bplus, int Bminus, int Aminus){
//        qDebug() << "Stage:"<<currentStage <<  " Pin A+:" << Aplus<<  " Pin B+:" << Bplus<<  " Pin B-:" << Bminus<<  " Pin A-:" << Aminus;
      digitalWrite(m_Aplus, Aplus);
      digitalWrite(m_Aminus, Aminus);
      digitalWrite(m_Bplus, Bplus);
      digitalWrite(m_Bminus, Bminus);
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

const int stepsPerRevolution = 8;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
MyStepperMotor myStepper(stepsPerRevolution, 8, 9, 10, 11);

int stepCount = 0;         // number of steps the motor has taken
int direction= 1;

void setControl(int A,int B,int Bm , int Am){
    digitalWrite(8, A);
    digitalWrite(9, Am);
    digitalWrite(10, B);
    digitalWrite(11, Bm);
}
void setup() {
  // initialize the serial port:
  Serial.begin(9600);
  // innitialize port
  myStepper.fullOpen();
  
}

void loop() {
  // step one step:
//  stepCount+= direction;
//  if ( stepCount == 9){
//    direction = -1;
//    stepCount -= 2; 
//  }
//  
//  if ( stepCount == 0){
//    direction = 1;
//    stepCount += 2; 
//  }
//  Serial.print("steps:" );
//  Serial.println(stepCount);
//  myStepper.step(direction);
//  delay(1000);
//  myStepper.step(120);
//  myStepper.step(-120);

//  setControl(HIGH,LOW,LOW,LOW);
//  delay(1000);
//  
//  setControl(HIGH,HIGH,LOW,LOW);
//  delay(1000);
//  
//  setControl(LOW,HIGH,LOW,LOW);
//  delay(1000);
//  
//  setControl(LOW,HIGH,LOW,HIGH);
//  delay(1000);
//  
//  setControl(LOW,LOW,LOW,HIGH);
//  delay(1000);
//  
//  setControl(LOW,LOW,HIGH,HIGH);
//  delay(1000);
//  
//  setControl(LOW,LOW,HIGH,LOW);
//  delay(1000);
//  
//  setControl(HIGH,LOW,HIGH,LOW);
//  delay(1000);
}
