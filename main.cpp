#include <QApplication>

#include "ui_controller.h"
#include "controller.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Controller controller(nullptr);

    Ui::MainWindow mainUI;
    mainUI.setupUi(&controller);
    controller.setResultDisplays(mainUI.channel, mainUI.volume, mainUI.volProgressBar, mainUI.InputIndicator);
    controller.setVolumeButtons(mainUI.volIncrement, mainUI.volDecrement);

    controller.show();
    return QApplication::exec();
}

