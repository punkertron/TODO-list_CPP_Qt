#ifndef DB_TASK_CONTROLLER_HPP
#define DB_TASK_CONTROLLER_HPP

#include <QList>
#include <QtSql>

#include "Task.hpp"

class DbTaskController final
{
   private:
    QSqlDatabase db;
    QList<Task> taskList;

    void errorExec(const QString& lastErrorText);

   public:
    DbTaskController();

    void addNewTask(Task& task);
    const Task& getFrontTask() const
    {
        return taskList.front();
    }

    void deleteTask(uint32_t task_id);
};

#endif  // DB_TASK_CONTROLLER_HPP