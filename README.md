# Calculator

The goal of this lab is to use SIGNALS and SLOTS to simulate a basic calculator behavior.The supported operations are *, +, -, / .

# Setup
## Static Calculator:

![image](https://github.com/imane0101010/Calculator/blob/d46c93b877cacea3a8bec4d1f65537faeaccd687/Calc.PNG)

 You will find a detailed explanation in the previous lab [FUN WITH LAYOUTS](Fun_With_Layouts/README.md).
 
## Reactivity:

For now our application has no reactivity. The goal of the rest of the section is to obtain step/step a fully functional widget.
In order to have a generalized computing functionality, we will represent any mathematical operation by:  operand (operation)
where (operation) is one of the following allowed operation + - * /.
The idea is to create two QVectors in which we will collect the numbers and the operations used and then we will try to perform the mathematical 
operations according to the math priority rules.
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

Now it´s time to get the final result of these mathematical operations.But before we should create and implement the method calculate that takes as paramenters the operation QVector and numbers Qvector and returns a number.
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


N.B: This calculator ignores the decimal part and can´t display larger numbers(more than 6 digits).Stay tuned for future updates!
