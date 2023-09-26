#include <QApplication>

#include "MainWindow.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    if (1 == 1)
        (void)w;
    // int *b = new int(5);
    //(void) b;
    return a.exec();
}
