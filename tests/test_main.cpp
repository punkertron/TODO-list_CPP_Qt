#include <QVector>
#include <QtTest>

#include "../incs/DbTaskController.hpp"

class TestDbTaskController : public QObject
{
    Q_OBJECT

   private:
    DbTaskController c;

    void deleteAllTasks()
    {
        for (const auto& [key, value] : c.getMapTask().toStdMap())
            c.deleteTask(key);
    }

   private slots:

    void initTestCase()
    {
        deleteAllTasks();
    }

    void addDeleteChangeTaskTestCase()
    {
        QVector<Task> v;
        v.emplace_back("hello"      , "some"            , QDate(2023, 5, 1)); // done
        v.emplace_back("HeLLOO"     , "___123____"      , QDate(2023, 5, 11)); // progress
        v.emplace_back("Yhello Y"   , "text"            , QDate(2023, 5, 1));
        v.emplace_back("ello"       , "123"             , QDate(2023, 6, 1));
        v.emplace_back("h"          , "_______________" , QDate(2023, 4, 1));
        v.emplace_back("world"      , "good"            , QDate(2023, 5, 1)); // progress
        v.emplace_back("hwolrd"     , "TrgoOdE"         , QDate(2023, 7, 1));
        v.emplace_back("123"        , "__gOo0_"         , QDate(2023, 3, 1)); // done
        v.emplace_back("h123t"      , "_TEXT_"          , QDate(2023, 3, 1)); // progress
        v.emplace_back("hell world" , "_SOME_"          , QDate(2023, 5, 1));
        v.emplace_back("world123"   , "_GOOD_"          , QDate(2023, 5, 1));
        v.emplace_back("hello"      , "SoMe TeXT "      , QDate(2023, 9, 1));
        v.emplace_back("hello"      , "some text"       , QDate(2023, 8, 1)); // done

        for (auto t : v)  // not &
            c.addNewTask(t);

        QVERIFY(c.getMapTask().size() == v.size());

        deleteAllTasks();

        QVERIFY(!c.getMapTask().size());

        for (auto t : v)  // not &
            c.addNewTask(t);

        QVERIFY(c.getMapTask().size() == v.size());

        QVERIFY(c.getLastTask().m_name == "hello"
                && c.getLastTask().m_description == "some text"
                && c.getLastTask().m_deadline_date == QDate(2023, 8, 1)
                && c.getLastTask().m_isVisible == true
                && c.getLastTask().m_task_status == "default"
        );
        QVERIFY(c.getLastTaskId() == 12);

        c.deleteTask(12);
        QVERIFY(c.getLastTask().m_name == "hello"
                && c.getLastTask().m_description == "SoMe TeXT "
                && c.getLastTask().m_deadline_date == QDate(2023, 9, 1)
                && c.getLastTask().m_isVisible == true
                && c.getLastTask().m_task_status == "default"
        );

        QVERIFY(c.getMapTask().size() == 12);

        Task t("hello", "", QDate(2023, 1, 1));
        c.setTask(11, t);

        QVERIFY(c.getLastTask().m_name == "hello"
                && c.getLastTask().m_description == ""
                && c.getLastTask().m_deadline_date == QDate(2023, 1, 1)
                && c.getLastTask().m_isVisible == true
                && c.getLastTask().m_task_status == "default"
        );

        c.setStatus(11, "done");
        QVERIFY(c.getLastTask().m_task_status == "done");

        c.setStatus(1, "in progress");
        QVERIFY(c.getTask(1).m_name == "HeLLOO"
            && c.getTask(1).m_description == "___123____"
            && c.getTask(1).m_deadline_date == QDate(2023, 5, 11)
            && c.getTask(1).m_isVisible == true
            && c.getTask(1).m_task_status == "in progress"
        );

        deleteAllTasks();
        for (auto t : v)  // not &
            c.addNewTask(t);
        
        c.setStatus(1, "in progress");
        c.setStatus(5, "in progress");
        c.setStatus(8, "in progress");
        c.setStatus(0, "done");
        c.setStatus(7, "done");
        c.setStatus(12, "done");
    }

    void filterTaskTestCase()
    {
        FilterParams d;
        c.setFilterParams(d);

        for (auto& t : c.getMapTask())
            QVERIFY(t.m_isVisible == true);
        
        d.m_name = "hello";
        c.setFilterParams(d);
        c.setFilterVisibleAll();
        for (const auto& [key, value] : c.getMapTask().toStdMap())
        {
            if (key == 0 || key == 1 || key == 2 || key == 11 || key == 12)
                QVERIFY(value.m_isVisible == true);
            else
                QVERIFY(value.m_isVisible == false);
        }

        d.m_description = "SOME";
        c.setFilterParams(d);
        c.setFilterVisibleAll();
        for (const auto& [key, value] : c.getMapTask().toStdMap())
        {
            if (key == 0 || key == 11 || key == 12)
                QVERIFY(value.m_isVisible == true);
            else
                QVERIFY(value.m_isVisible == false);
        }

        d.m_defaultTaskStatus = false;
        c.setFilterParams(d);
        c.setFilterVisibleAll();
        for (const auto& [key, value] : c.getMapTask().toStdMap())
        {
            if (key == 0 || key == 12)
                QVERIFY(value.m_isVisible == true);
            else
                QVERIFY(value.m_isVisible == false);
        }

        d.m_doneTaskStatus = false;
        c.setFilterParams(d);
        c.setFilterVisibleAll();
        for (const auto& [key, value] : c.getMapTask().toStdMap())
        {
            QVERIFY(value.m_isVisible == false);
        }

        d.m_defaultTaskStatus = true;
        c.setFilterParams(d);
        c.setFilterVisibleAll();
        for (const auto& [key, value] : c.getMapTask().toStdMap())
        {
            if (key == 11)
                QVERIFY(value.m_isVisible == true);
            else
                QVERIFY(value.m_isVisible == false);
        }

        d.m_description = "TEXT";
        c.setFilterParams(d);
        c.setFilterVisibleAll();
        for (const auto& [key, value] : c.getMapTask().toStdMap())
        {
            if (key == 2 || key == 11)
                QVERIFY(value.m_isVisible == true);
            else
                QVERIFY(value.m_isVisible == false);
        }

        ////////////////////
        // DEFAULT
        ////////////////////
        d = FilterParams();
        c.setFilterParams(d);
        c.setFilterVisibleAll();
        for (const auto& [key, value] : c.getMapTask().toStdMap())
        {
            QVERIFY(value.m_isVisible == true);
        }


        d.m_minDate = QDate(2023, 5, 1);
        c.setFilterParams(d);
        c.setFilterVisibleAll();
        for (const auto& [key, value] : c.getMapTask().toStdMap())
        {
            if (key == 0 || key == 1 || key == 2 || key == 3
                || key == 5 || key == 6 || key == 9
                || key == 10 || key == 11 || key == 12)
                QVERIFY(value.m_isVisible == true);
            else
                QVERIFY(value.m_isVisible == false);
        }

        d.m_minDate = QDate(2023, 5, 2);
        c.setFilterParams(d);
        c.setFilterVisibleAll();
        for (const auto& [key, value] : c.getMapTask().toStdMap())
        {
            if (key == 1 || key == 3 || key == 6 || key == 11 || key == 12)
                QVERIFY(value.m_isVisible == true);
            else
                QVERIFY(value.m_isVisible == false);
        }

        d.m_progressTaskStatus = false;
        c.setFilterParams(d);
        c.setFilterVisibleAll();
        for (const auto& [key, value] : c.getMapTask().toStdMap())
        {
            if (key == 3 || key == 6 || key == 11 || key == 12)
                QVERIFY(value.m_isVisible == true);
            else
                QVERIFY(value.m_isVisible == false);
        }

        d.m_maxDate = QDate(2023, 7, 15);
        c.setFilterParams(d);
        c.setFilterVisibleAll();

        Task t("hello", "world", QDate(2023, 2, 5));
        c.addNewTask(t);
        c.setFilterVisible(c.getLastTaskId());

        for (const auto& [key, value] : c.getMapTask().toStdMap())
        {
            if (key == 3 || key == 6)
                QVERIFY(value.m_isVisible == true);
            else
                QVERIFY(value.m_isVisible == false);
        }
    }

    void cleanupTestCase()
    {
        deleteAllTasks();
    }
};

QTEST_MAIN(TestDbTaskController)
#include "test_main.moc"