#ifndef REAL_CALCULATOR_H
#define REAL_CALCULATOR_H

#include <QtWidgets/QMainWindow>
#include "ui_Real_Calculator.h"
#include "Global variables.h"



namespace Ui
{
    class Real_Calculator;
}

class Real_Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Real_Calculator(QWidget *parent = nullptr);


private:
    Ui::Real_CalculatorClass ui;

private slots:
    void numberPressed();
    void clearEntry();
    void decimalButton();
    void mathPressed();
    void equalPressed();
    void clearAllEntry();
    void flipTheSign();

private:
    void displayFirst(QString x=firstNumber) { ui.display->setText(x); }
    void displaySecond(QString y=secondNumber) { ui.display->setText(y); }
    void calculateChainResult();

    
};




#endif
