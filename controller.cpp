
#include "controller.h"

#define MAX_CHANNEL 999
#define MAX_VOLUME 100
#define INPUT_DELAY_MSEC 1500

Controller::Controller(QWidget *parent) : QMainWindow(parent) {
    timeForInput.start();
    timerIndicator = new QTimer(this);
    timerIndicator->setInterval(100);
    connect(timerIndicator, &QTimer::timeout, this, &Controller::blinkingIndicator);
}
Controller::~Controller() {}


///как и в первой задаче эти два метода собирают указатели на нужные обЪекты для последующей работы с ними
void Controller::setResultDisplays(QLCDNumber *ch, QLCDNumber *vol, QProgressBar* pBar, QLabel* indic){
    volume = vol;
    channel = ch;
    volumeBar = pBar;
    indicator = indic;
}

void Controller::setVolumeButtons(QPushButton* up, QPushButton* down) {
    butVolumeUp = up;
    butVolumeDown = down;
}

///методы инкремента и декремента номера канала
void Controller::channelUp() {
    if (channel->intValue() < MAX_CHANNEL) {
        channel->display(channel->intValue() + 1);
    }
}
void Controller::channelDown() {
    if (channel->intValue()) {
        channel->display(channel->intValue() - 1);
    }
}

///два слота click() громкости иникремент/декремент
void Controller::volumeUp() {
    if (volume->intValue() < MAX_VOLUME) {
        volume->display(volume->intValue() + 1);
        volumeBar->setValue(volume->intValue());
    }
}
void Controller::volumeDown() {
    if (volume->intValue()) {
        volume->display((volume->intValue() - 1));
        volumeBar->setValue(volume->intValue());
    }
}
/// ПС: сначала сделал, как в задаче с шагом 10, но потом переделал.
/// Думаю с ускорением скорости изменения громкости поинтереснее будет


///два слота release() кнопок громкости (авто-репит включен в дизайнере)
#define MIN_REPEAT_INTERVAL 10

void Controller::setSpeedVolUp() { speedUpVolume(butVolumeUp); }
void Controller::setSpeedVolDown() { speedUpVolume(butVolumeDown); }

void Controller::speedUpVolume(QPushButton* target) {
    ///проверка, если получен авто-релиз кнопки, но в действительности ее не отжали
    /// значит идет удержание и скорость изменения громкости увеличивается
    if (!target->isDown()) {
        target->setAutoRepeatInterval(100);
    } else {
        int newInterval = target->autoRepeatInterval() * 0.9;
        target->setAutoRepeatInterval(newInterval > MIN_REPEAT_INTERVAL ? newInterval : MIN_REPEAT_INTERVAL);
    }
}

void Controller::setDigitToDisplay(int digit) {
    channel->display(digit);
}

void Controller::addDigitToDisplay(int digit) {
    if (channel->intValue() <= (MAX_CHANNEL / 10)) {
        channel->display(channel->intValue() * 10 + digit);
    }
}
///в зависимоти от того сколько времени прошло после нажатия какой-либо кнопки
///новая цифра либо начинает новую запись, либо продолжает ввод номера канала
void Controller::printDigit(int num) {
    if (timeForInput.restart() < INPUT_DELAY_MSEC) {
        addDigitToDisplay(num);
    } else {
        setDigitToDisplay(num);
    }
    timerIndicator->start();
}

void Controller::num0() {printDigit(0);}
void Controller::num1() {printDigit(1);}
void Controller::num2() {printDigit(2);}
void Controller::num3() {printDigit(3);}
void Controller::num4() {printDigit(4);}
void Controller::num5() {printDigit(5);}
void Controller::num6() {printDigit(6);}
void Controller::num7() {printDigit(7);}
void Controller::num8() {printDigit(8);}
void Controller::num9() {printDigit(9);}

///моргание индикатора, пока возможен ввод цифры, если время вышло, метод сам выключает таймер.
/// (другого способ отключить мигание, например через сам QTimer я не нашёл)
void Controller::blinkingIndicator() {
    indicatorOn = !indicatorOn;
    if (timeForInput.elapsed() >= INPUT_DELAY_MSEC - 100) { //не знаю, почему -100, но вроде так лучше (минус пол такта)
        timerIndicator->stop();
        indicatorOn = false;
    }
    indicator->setStyleSheet(indicatorOn ? "color: rgb(255, 0, 0)" : "color: rgb(170, 170, 170)");
}
