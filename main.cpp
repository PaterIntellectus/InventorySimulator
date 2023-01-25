#include "mainmenudialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainMenuDialog d;
    d.show();
    return a.exec();
}
