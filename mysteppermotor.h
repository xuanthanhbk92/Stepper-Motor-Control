#ifndef MYSTEPPERMOTOR_H
#define MYSTEPPERMOTOR_H
#include <QDebug>
#include <QThread>
class MyStepperMotor
{
#define MAX_STEP 164
#define DELAY_DEFAULT 100
public:
    MyStepperMotor(int resolution,int AplusPin, int AminusPin, int BplusPin , int BminusPin );   // resolution and control pin
    void step( int numberStep);
    void fullOpen();
    void fullClose();

private:
    void delayBetweenStep(){
        QThread::msleep(DELAY_DEFAULT);
    }

    enum {
        OPEN =1,
        CLOSE =0
    };
    enum {
        LOW=0,
        HIGH =1
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


#endif // MYSTEPPERMOTOR_H
