#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MyStepperMotor m_step(100,8,9,10,11);
    m_step.fullOpen();
}

MainWindow::~MainWindow()
{
    delete ui;
}
