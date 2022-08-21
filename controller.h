
#ifndef INC_3_CONTROLLER_CONTROLLER_H
#define INC_3_CONTROLLER_CONTROLLER_H

#include <QMainWindow>
#include <QLCDNumber>
#include <QProgressBar>
#include <QElapsedTimer>
#include <QLabel>
#include <QTimer>
#include <QPushButton>

class Controller : public QMainWindow {

   Q_OBJECT

public:
    Controller(QWidget *parent = nullptr);
    ~Controller();

    void setResultDisplays(QLCDNumber* ch, QLCDNumber* vol, QProgressBar* pBar, QLabel* indic);
    void setVolumeButtons(QPushButton* up, QPushButton* down);

public slots:
    void volumeUp();
    void volumeDown();
    void channelUp();
    void channelDown();

    void num0();
    void num1();
    void num2();
    void num3();
    void num4();
    void num5();
    void num6();
    void num7();
    void num8();
    void num9();

    void setSpeedVolUp();
    void setSpeedVolDown();

    void blinkingIndicator();


private:

    void printDigit(int num);
    void setDigitToDisplay(int digit);
    void addDigitToDisplay(int digit);
    QLCDNumber* channel;
    QLCDNumber* volume;
    QProgressBar* volumeBar;

    QElapsedTimer timeForInput;
    QPushButton *butVolumeUp, *butVolumeDown;
    static void speedUpVolume(QPushButton* target); //не совсем понял почему, но static - по рекомендации CLion

    QLabel* indicator;
    bool indicatorOn = false;
    QTimer* timerIndicator;

};

//#include <controller.moc>
#endif //INC_3_CONTROLLER_CONTROLLER_H
