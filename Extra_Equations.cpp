#include "Real_Calculator.h"
#include "Extra_Equations.h"
#include "Global variables.h"

void resetOperator()
{
    isSum = false;
    isMult = false;
    isSubs = false;
    isDiv = false;
}

//if you press "." before number it will place a 0 for you
void putZeroInFront(QString& x)
{
	if (x.isEmpty() || x.contains(QChar{'-'}))
		x.append(QString{ '0' });

}

//flips the sign of the number in screen
void changeTheSign(QString& x)
{

	if (x.contains(QString{ '-' }))
		x.removeFirst();
	else
		x.prepend(QChar{ '-' });

}

void mathing()
{
    double uno{ firstNumber.toDouble() };
    double two{ secondNumber.toDouble() };

    if (isSum)
        firstNumber = QString::number(uno + two);
    else if (isSubs)
        firstNumber = QString::number(uno - two);
    else if (isMult)
        firstNumber = QString::number(uno * two);
    else if (isDiv)
    {
        if (two == 0)
            firstNumber = QString{ "UNDEF" };
        else
            firstNumber = QString::number(uno / two);
    }
}

void setOperator(QString& op)
{
    resetOperator();
    // changes the correct bool variable accoring to what button the user pressed
    if (op == QString{ '+' })
        isSum = true;
    else if (op == QString{ '-' })
        isSubs = true;
    else if (op == QString{ 'x' })
        isMult = true;
    else if (op == QString{ '/' })
        isDiv = true;

    opMemory = op;
}