# Calculator

The goal of this lab is to use SIGNALS and SLOTS to simulate a basic calculator behavior.The supported operations are *, +, -, / .

# Setup
## Static Calculator:

 You will find a detailed explanation in the previous lab FUN WITH LAYOUTS.
 
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

Get the identity of the sender button.
Store the clicked operation.
Reset the display to 0

```cpp
void Calculator::changeOperation()
{
   
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



