#include "calculator.h"
#include <QKeyEvent>
#include <QApplication>
#include <iostream>


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
    reset = new QPushButton("Reset",this);
    //operatiosn buttons
    operations.push_back(new QPushButton("+"));
    operations.push_back(new QPushButton("-"));
    operations.push_back(new QPushButton("*"));
    operations.push_back(new QPushButton("/"));
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
    for(int i=0; i <4 ; i++)
        buttonsLayout->addWidget(operations[ i], i, 4);


    //Adding the 0 button
    buttonsLayout->addWidget(digits[0], 3, 0);
    buttonsLayout->addWidget(enter, 3, 2, 1,1);
    buttonsLayout->addWidget(reset, 3, 1, 1,1);
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
    connect(reset,SIGNAL(clicked()),this,SLOT(reset_()));
}

int Calculator::calculate(QVector <QString> &op,QVector<int> &num)
{
    if(op.size()==0){
        return num[0];
    }
    if((!op.contains("*") && !op.contains("/")) || (!op.contains("+") && !op.contains("-"))){
      for(int i=0;i<op.size();i++){
         if(op[i] == "-" ){
            if(i==0){
             cal =cal+num[i]-num[i+1];
            }else{
              cal =cal -num[i+1];
            }
         }else if(op[i] == "+" ){
           if(i==0){
             cal =cal+num[i]+num[i+1];
           }else{
             cal =cal +num[i+1];
           }
         }else if(op[i] == "*" ){
             if(i==0){
             cal =cal+num[i]*num[i+1];
             }else{
                 cal =cal *num[i+1];
             }
         }else if(op[i] == "/" ){
             if(num[i+1]==0){
                 std::cout<<"syntax error";
             }else{
             if(i==0){
             cal =cal+num[i]/num[i+1];
             }else {
                 cal =cal / num[i+1];
             }
         }
         }
}
  }else{
     while(op.contains("*")|| op.contains("/")){
       for(int i =0 ; i<op.size();i++){

        if(op[i]=="*"){

            num[i]=num[i]*num[i+1];
            num.removeAt(i+1);
            op.removeAt(i);
            i=i-1;

        }else if(op[i]=="/"){
             if(num[i+1] ==0){
              std::cout<<"syntax error";
             }else{
            num[i]=num[i]/num[i+1];
            num.removeAt(i+1);
            op.removeAt(i);
            i=i-1;
             }
        }
     }
  }
 calculate(op,num);
}
  return cal;
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

            if(!operand){
                operand = new int{value};
           }else{
                *operand = 10 * (*operand) + value;
}
            disp->display(*operand);
    }

void Calculator::changeOperation()
{
     nums.push_back(*operand);
    //Getting the sender button
    auto button = dynamic_cast<QPushButton*>(sender());

    //Storing the operation
    operation = new QString{button->text()};

    ops.push_back(*operation);

    //Initiating the right button
    operand = new int{0};

    //reseting the display
    disp->display(0);
}

void Calculator::enter_button()
{
 nums.push_back(*operand);
auto button = dynamic_cast<QPushButton*>(sender());
if(button == enter){

  disp->display(calculate(ops,nums));


}
}

void Calculator::reset_(){
     auto button = dynamic_cast<QPushButton*>(sender());
     if (button == reset){
        operand = new int{0};
        cal=0;
        disp->display(0);
        nums.clear();
        ops.clear();
}

}






