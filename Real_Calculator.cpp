#include <vector>
#include "Real_Calculator.h"
#include "Extra_Equations.h"
#include "Global variables.h"

//global string to hold values introduced into the calculator
QString firstNumber{};
QString secondNumber{};
bool isSum{ false };
bool isSubs{ false };
bool isMult{ false };
bool isDiv{ false };
bool isEqualPressed{ false };
QString opMemory{};


Real_Calculator::Real_Calculator(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.display->QTextEdit::setAlignment(Qt::AlignRight);
    ui.display->setText(QString{ '0' });

    //sets up all number buttons using a vector to save each individual button and inmidiatly use it to create
    //the conection between signal and a slot for all of them
    std::vector<QPushButton *> numButtons(10);
    for (int i = 0; i < 10; i++)
    {
        QString name{ "button" + QString::number(i) };
        numButtons[i] = Real_Calculator::findChild<QPushButton*>(name);
        connect(numButtons[i], &QPushButton::clicked, this, &Real_Calculator::numberPressed);
    }
    
    //sets up the math operator buttons
    std::vector<QPushButton *> mathButtons(4);
    for (int i = 0; i < 4; i++)
    {
        QString nameMath{ "math" + QString::number(i) };
        mathButtons[i] = Real_Calculator::findChild<QPushButton*>(nameMath);
        connect(mathButtons[i], &QPushButton::clicked, this, &Real_Calculator::mathPressed);
    }


    connect(ui.clearE, &QPushButton::clicked, this, &Real_Calculator::clearEntry);
    connect(ui.clearAll, &QPushButton::clicked, this, & Real_Calculator::clearAllEntry);
    connect(ui.button10, &QPushButton::clicked, this, &Real_Calculator::decimalButton);
    connect(ui.theEqual, &QPushButton::clicked, this, &Real_Calculator::equalPressed);
    connect(ui.flipSign, &QPushButton::clicked, this, &Real_Calculator::flipTheSign);

}

void Real_Calculator::mathPressed()
{
    //resets memory of "was the equal button just pressed?"
    if (isEqualPressed)
        isEqualPressed = !isEqualPressed;

    //ignores operator button when no values had been put into the calculator
    if (opMemory.isEmpty() && firstNumber.isEmpty())
        return;

    //makes sure 0 is shown in display after a operator button is pressed
    ui.display->setText(QString{ "0" });

    //saves what sign was pressed as a string
    QPushButton* pointer{ static_cast<QPushButton*>(sender()) };
    QString op{pointer->text()};

    //allows to change the sign by just pressing any of the math buttons again
    if (!opMemory.isEmpty() && secondNumber.isEmpty())
    {
        setOperator(op);
        return;
    }

    //checks if user presses math button before equal and does the arimethic with previous asnwer
    if (!opMemory.isEmpty())
        calculateChainResult();
    
    //sets the correct bool variable
    setOperator(op);
    
}

void Real_Calculator::numberPressed()
{
    //Gets addres from the button that sent the signal. Have to static cast becuase the sender() uses a QObject:
    //QObject* pointer{ sender() }; but the text() function uses QPushButton object
    QPushButton* pointer{ static_cast<QPushButton *>(sender()) };

    //text() function gets the text thats written in the widget button
    if (!isSum && !isSubs && !isMult && !isDiv)
    {
        //if statement resets the variable in case user introduces new number right after they pressed equal.
        if (isEqualPressed)
        {
            isEqualPressed = !isEqualPressed;
            firstNumber.clear();
        }

        firstNumber.append(pointer->text());
        displayFirst();
    }
    if (isSum || isSubs || isMult || isDiv)
    {
        secondNumber.append(pointer->text());
        displaySecond();
    }
}

void Real_Calculator::clearEntry()
{
    //this two if statements decides to which QString the changes should apply
    //if not math button has been pressed writes into firstNumber, if a math button has been pressed it writes into secondNumber
    if (!isSum && !isSubs && !isMult && !isDiv)
    {
        firstNumber.clear();
        displayFirst(QString{ '0' });
    }
    if (isSum || isSubs || isMult || isDiv)
    {
        secondNumber.clear();
        displaySecond(QString{ '0' });
    }

}

void Real_Calculator::clearAllEntry()
{
    resetOperator();
    firstNumber.clear();
    secondNumber.clear();
    opMemory.clear();
    ui.display->setText(QString{ '0' });
}

void Real_Calculator::decimalButton()
{
    if (!isSum && !isSubs && !isMult && !isDiv && !firstNumber.contains('.'))
    {
        putZeroInFront(firstNumber);
        firstNumber.append(QString{ '.' });
        displayFirst();
    }
    if ((isSum || isSubs || isMult || isDiv) && !secondNumber.contains('.'))
    {
        putZeroInFront(secondNumber);
        secondNumber.append(QString{ '.' });
        displaySecond();
    }
}

void Real_Calculator::flipTheSign()
{
    if (!isSum && !isSubs && !isMult && !isDiv)
    {
        if (firstNumber.isEmpty())
            return;
        // checks what sign the current number has, then it flips it.
        changeTheSign(firstNumber);
        displayFirst();
    }
    if (isSum || isSubs || isMult || isDiv)
    {
        //if no number is in the string this button doesnt do anything.
        if (secondNumber.isEmpty())
            return;
        changeTheSign(secondNumber);
        displaySecond();
    }
}

void Real_Calculator::equalPressed()
{
    //mathing does all the math and sets the fistNumber variable as the result
    mathing();

    displayFirst();
    resetOperator();
    secondNumber.clear();
    isEqualPressed = !isEqualPressed;
    opMemory.clear();
}

void Real_Calculator::calculateChainResult()
{
    mathing();

    displayFirst();
    secondNumber.clear();
    resetOperator();
}

