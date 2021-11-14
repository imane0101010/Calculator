#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include <QWidget>

class QRadioButton;

class TrafficLight: public QWidget{
  Q_OBJECT

public:

  TrafficLight(QWidget * parent = nullptr);

protected:
     void createWidgets();
     void placeWidgets();
     void timerEvent(QTimerEvent *e)override;
     void keyPressEvent( QKeyEvent *e)override;

private:

  QRadioButton * redlight;
  QRadioButton * yellowlight;
  QRadioButton * greenlight;
  QVector<QRadioButton*> lights;
  int index=0;
  int lifetime =0;

};


#endif
