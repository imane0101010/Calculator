#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QGridLayout>
#include <QVector>
#include <QPushButton>
#include <QLCDNumber>
#include <QString>

class Calculator : public QWidget
{
    Q_OBJECT
public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();
    int fact(int n);



 // Add you custom slots here

protected:
    void createWidgets();        //Function to create the widgets
    void placeWidget();         // Function to place the widgets
    void makeConnexions();// Create all the connectivity
    int calculate(QVector <QString> &s,QVector<int> &s1);

//events
protected:
    void keyPressEvent(QKeyEvent *e)override;     //Override the keypress events

private:
    QGridLayout *buttonsLayout; // layout for the buttons
    QVBoxLayout *layout;        //main layout for the button
    QVector<QPushButton*> digits;  //Vector for the digits
    QPushButton *enter;  // enter button
    QPushButton *reset;
    QVector<QPushButton*> operations; //operation buttons
    QLCDNumber *disp;             // Where to display the numbers
    QVector <int> nums;
    QVector <QString> ops;

private:

    int * operand;// operand
    QString *operation= nullptr; // Pointer on the current operation
    int cal=0;
public slots:
   void newDigit();
   void changeOperation();
   void enter_button();
   void reset_();

};
#endif // CALCULATOR_H
