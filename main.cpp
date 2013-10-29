#include <QApplication>

#include "caculator.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    Caculator *winDialog = new Caculator;
    winDialog->show();

    return app.exec();
}
