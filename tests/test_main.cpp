#include <QApplication>
#include <QtTest/QtTest>

#include "../incs/DbTaskController.hpp"

class MyTest : public QObject
{
    Q_OBJECT

   private:
    DbTaskController controller;
   private slots:

    void testCase1()
    {
        QVERIFY(1 + 1 == 2);
        QVERIFY(1 + 1 == 3);
    }
};

QTEST_APPLESS_MAIN(MyTest)
#include "test_main.moc"