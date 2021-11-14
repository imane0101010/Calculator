# Calculator

The goal of this lab is to use SIGNALS and SLOTS to simulate a basic calculator behavior.The supported operations are *, +, -, / .

# Setup
## Static Calculator:

![image](https://github.com/imane0101010/Calculator/blob/d46c93b877cacea3a8bec4d1f65537faeaccd687/Calc.PNG)

 You will find a detailed explanation in the previous lab [FUN WITH LAYOUTS](https://github.com/imane0101010/Fun_With_Layouts/blob/main/README.md).
 
## Reactivity:

For now our application has no reactivity. The goal of the rest of the section is to obtain step/step a fully functional widget.
In order to have a generalized computing functionality, we will represent any mathematical operation by:  operand (operation)
where (operation) is one of the following allowed operation + - * /.
The idea is to create two QVectors in where we will collect the numbers and the operations used and then we will try to perform the mathematical 
operations according to the operator precedence.
So,we will add the following members to our class calculator.h.

```cpp
 QVector <int> nums;
 QVector <QString> ops;
   QString *operation; 
  int * operand;
```

## Custom Slots:
For our case, we will use the Sender approach which allow a slot to get the identity of the sender object. From that we could get which button was clicked. Hence we will define the following slot:

```cpp
 public slots:
   void newDigit();
 ```
   
   ## Digits interaction:
 The idea of this new connexion, it to connect all the button to this slot. This function will use the Sender method to get the identity of which button was clicked and act accordingly.

 1-Hence we will add the connect the connect all the digits buttons to this slot.

```cpp
 //Connecting the digits
 for(int i=0; i <10; i++)
     connect(digits[i], &QPushButton::clicked,this, &Calculator::newDigit);
 ```
 
 2-Now, we will implement the newDigit slot to show the digit in the LCDNumber.
 
 ```cpp
 //Getting the identity of the button using dynamic_cast
auto button  = dynamic_cast<QPushButton*>(sender());

// Each button has his own digit in the text
auto value = button->text()->toInt();

//Displaying the digit
disp->display(value);
```

## Integer numbers
Now that we can react to each digit, it is time to correctly implement the newDigit slot. We should know if we are adding a digit to an existing number or if we are constructing the number.Here is the full implementation of the newDigit method:

```cpp
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
```

## Operation Interaction

Now we will move on the operation of the four buttons. We will the same mechanism using the sender method. Hence we will define a single slot to handle the click on the operations buttons:

```cpp
public slots:
    void changeOperation();  //Slot to handle the click on operations
    void newDigit();
```

This slot will simply execute the following operations:

Stores the operand in the QVector nums.

Get the identity of the sender button.

Stores the operation in the QVector ops.

Store the clicked operation.

Reset the display to 0

```cpp
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
```
## Enter Button:

Now it´s time to get the final result of these mathematical operations.But before we should create and implement the method calculate that takes as parameters the operation two QVectors of type int and qstring and returns the result of the operations.
Here is the entire implementation:

```cpp
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
                 break;
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
             if(num[i+1]==0){
              std::cout<<"syntax error";
              break;
            }else{
            num[i]=num[i]/num[i+1];
            num.removeAt(i+1);
            op.removeAt(i);
            i=i-1;
        }
     }
  }
 calculate(op,num);
}
  return cal;
}
```
Now we are ready to create and implement the enter_button slot. Here is the full implementation of the method:
```cpp
   public slots:
   void enter_button;
 ```
```cpp
void Calculator::enter_button()
{
 nums.push_back(*operand); //storing the last operand in nums
 auto button = dynamic_cast<QPushButton*>(sender());
if(button == enter){
  disp->display(calculate(ops,nums));
}
}
```
Now, let's connect the close button:
```cpp
connect(enter,&QPushButton::clicked,this, &Calculator::enter_button);
```
## Reset Button:

While clicking on the reset button the whole calculation process must be refreshed.To do so we should clear all the vectors,set the operand and the cal variable to zero,and display 0 in the LCDNumber.
Here is the code:
```cpp
 public slots:
   void reset_();
 ```

```cpp
void Calculator::reset_(){
     auto button = dynamic_cast<QPushButton*>(sender());
     if (button == reset){
        operand = new int{0};
        cal=0;
        disp->display(0);
        nums.clear();
        ops.clear();
}
```
Now, let's connect the close button:
```cpp
  connect(reset,SIGNAL(clicked()),this,SLOT(reset_()));
```
N.B: This calculator ignores the decimal part and can´t display larger numbers(more than 6 digits).Stay tuned for more updates!

# Traffic Light
In this second part, we will use the QTimer to simulate a traffic light.
## Setup
First of all, let´s create and customize the widgets:

trafficlight.h
```cpp
QRadioButton * redlight;
  QRadioButton * yellowlight;
  QRadioButton * greenlight;
  QVector<QRadioButton*> lights;
```
trafficlight.cpp

```cpp
redlight = new QRadioButton;
  redlight->setEnabled(false);
  redlight->toggle();
  redlight->setStyleSheet("QRadioButton::indicator:checked { background-color: red;}");

  yellowlight = new QRadioButton;
  yellowlight->setEnabled(false);
  yellowlight->setStyleSheet("QRadioButton::indicator:checked { background-color: yellow;}");

  greenlight = new QRadioButton;
  greenlight->setEnabled(false);
  greenlight->setStyleSheet("QRadioButton::indicator:checked { background-color: green;}");
  lights.append(redlight);
  lights.append(yellowlight);
  lights.append(greenlight);
```cpp
Then let´s create the layouts and place the widgets:
```cpp
auto layout = new QVBoxLayout;
  layout->addWidget(redlight);
  layout->addWidget(yellowlight);
  layout->addWidget(greenlight);
  setLayout(layout);
  ```
  ## Interaction
For now our application has no reactivity. The goal of this section is to obtain an automatic traffic light.To do so let's override the timer event method.
Here is the full implementation:

```cpp
void TrafficLight::timerEvent(QTimerEvent *e){
    lifetime++;
    if(redlight->isChecked() &&lifetime==4){
        yellowlight->toggle();
        lifetime=0;
    }else if(yellowlight->isChecked() && lifetime==1){
        greenlight->toggle();
        lifetime=0;
    }else if(greenlight->isChecked() && lifetime ==3){
        redlight->toggle();
}        lifetime=0;
 
   }
```
constructor:
```cpp
 startTimer(1000);
 ```
Now, we will override the keypress event method in order to be able to change the traffic light colors manually (using keyboard).
```cpp
void TrafficLight::keyPressEvent(QKeyEvent *e)
{

    if (e->key() == Qt::Key_Escape)
        qApp->exit();

    else if(e->key() == Qt::Key_R){
          //index=-1;
        redlight->toggle();
    }else if(e->key() == Qt::Key_Y){
        yellowlight->toggle();
          //index=0;
    }else if(e->key() == Qt::Key_G){
        greenlight->toggle();
         //index=1;
    }
}
```
![image](https://github.com/imane0101010/Calculator/blob/3c418fc61cfe416bc91d141467d5069878142ba6/traffic_light.PNG)
