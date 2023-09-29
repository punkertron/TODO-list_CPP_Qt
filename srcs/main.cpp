#include <QApplication>

#include "../incs/DbTaskManager.hpp"
#include "../incs/MainWindow.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DbTaskManager dbTaskManager;

    MainWindow w(&dbTaskManager);
    w.show();
    return a.exec();
}
