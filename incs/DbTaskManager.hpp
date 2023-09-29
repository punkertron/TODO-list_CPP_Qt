#ifndef DB_MANAGER_HPP
#define DB_MANAGER_HPP

#include <QList>
#include <QtSql>

#include "Task.hpp"

class DbTaskManager final
{
   private:
    QSqlDatabase db;
    QList<Task> taskList;

   public:
    DbTaskManager();

    void addNewTask(Task& task);
    const Task& getFrontTask() const
    {
        return taskList.front();
    }
};

#endif  // DB_MANAGER_HPP
