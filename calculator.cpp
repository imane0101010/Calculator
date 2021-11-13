#include "calculator.h"
#include <QKeyEvent>
#include <QApplication>
#include <math.h>

Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
{
    createWidgets();
    placeWidget();
    makeConnexions();

}
int Calculator::fact(int n){
    for(int i=1;i<=n;i++){
        n=n*i;
    }
    return n;
}





Calculator::~Calculator()
{
    delete disp;
    delete layout;
    delete buttonsLayout;
}


void Calculator::createWidgets()
{
    //Creating the layouts
    layout = new QVBoxLayout();
    layout->setSpacing(2);

    //grid layout
    buttonsLayout = new QGridLayout;


    //creating the buttons
    for(int i=0; i < 10; i++)
    {
        digits.push_back(new QPushButton(QString::number(i)));
        digits.back()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        digits.back()->resize(sizeHint().width(), sizeHint().height());
    }
    //enter button
    enter = new QPushButton("Enter",this);
    enter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    enter->resize(sizeHint().width(), sizeHint().height());

    //operatiosn buttons
    operations.push_back(new QPushButton("+"));
    operations.push_back(new QPushButton("-"));
    operations.push_back(new QPushButton("*"));
    operations.push_back(new QPushButton("/"));
   // operations.push_back(new QPushButton("!"));

    //creating the lcd
    disp = new QLCDNumber(this);
    disp->setDigitCount(6);

}

void Calculator::placeWidget()
{

    layout->addWidget(disp);
    layout->addLayout(buttonsLayout);


    //adding the buttons
    for(int i=1; i <10; i++)
        buttonsLayout->addWidget(digits[i], (i-1)/3, (i-1)%3);


    //Adding the operations
    for(int i=0; i <= 4; i++)
        buttonsLayout->addWidget(operations[ i], i, 4);


    //Adding the 0 button
    buttonsLayout->addWidget(digits[0], 3, 0);
    buttonsLayout->addWidget(enter, 3, 1, 1,2);

    setLayout(layout);
}

void Calculator::makeConnexions()
{
    //Connecting the digits
    for(int i=0; i <10; i++){
        connect(digits[i], &QPushButton::clicked,
                this, &Calculator::newDigit);
    }
    for(int i=0;i<operations.size();i++){
        connect(operations[i],SIGNAL(clicked()),this,SLOT(changeOperation()));

    }
    connect(enter,&QPushButton::clicked,
       this, &Calculator::enter_button);
}

void Calculator::keyPressEvent(QKeyEvent *e)
{
    //Exiting the application by a click on space
    if( e->key() == Qt::Key_Escape)
        qApp->exit(0);


    //You could add more keyboard interation here (like digit to button)
}
void Calculator::newDigit()
{
    //getting the sender
    auto button = dynamic_cast<QPushButton*>(sender());
    //getting the value
    int value = button->text().toInt();
    //Check if we have an operation defined
        if(operation)
        {
            //check if we have a value or not
            if(!right)
                right = new int{value};
            else
                *right = 10 * (*right) + value;

            disp->display(*right);

        }
        else
        {
            if(!left)
                left = new int{value};
            else
                *left = 10 * (*left) + value;
                disp->display(*left);
        }

    }

void Calculator::changeOperation()
{
    //Getting the sender button
    auto button = dynamic_cast<QPushButton*>(sender());

    //Storing the operation
    operation = new QString{button->text()};

    //Initiating the right button
    right = new int{0};

    //reseting the display
    disp->display(0);
}

void Calculator::enter_button()
{
auto button = dynamic_cast<QPushButton*>(sender());
if(button == enter){

   if(*operation == "+"){
       disp->display(*left + *right);
   }

   else if(*operation == "-"){
       disp->display(*left - *right);
   }

   else if(*operation == "*"){
       disp->display(*left * *right);
   }

  else if(*operation == "/"){
       disp->display(*left / *right);
   }



}
}
