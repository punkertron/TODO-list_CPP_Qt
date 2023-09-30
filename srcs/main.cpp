#include <QApplication>

#include "../incs/DbTaskController.hpp"
#include "../incs/MainWindow.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DbTaskController dbTaskController;

    MainWindow w(&dbTaskController);
    w.show();
    return a.exec();
}
