#include "trafficlight.h"
#include <QWidget>
#include <QLayout>
#include <QRadioButton>
#include <QVector>
#include <QApplication>
#include <QKeyEvent>
TrafficLight::TrafficLight(QWidget * parent): QWidget(parent){

    //Creatign the widgets
    createWidgets();
    //place Widgets
    placeWidgets();
    startTimer(1000);

}

void TrafficLight::createWidgets()
{

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


}


void TrafficLight::placeWidgets()
{

  // Placing the widgets
  auto layout = new QVBoxLayout;
  layout->addWidget(redlight);
  layout->addWidget(yellowlight);
  layout->addWidget(greenlight);
  setLayout(layout);
}
void TrafficLight::timerEvent(QTimerEvent *e){
/*
    index =(index+1)%3;
     lights[index]->toggle();

*/
    lifetime++;
    if(redlight->isChecked() &&lifetime==4){
        yellowlight->toggle();
        lifetime=0;
    }else if(yellowlight->isChecked() && lifetime==1){
        greenlight->toggle();
        lifetime=0;
    }else if(greenlight->isChecked() && lifetime ==3){
        redlight->toggle();
        lifetime=0;
    }








   }


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
