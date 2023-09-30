#ifndef DB_TASK_CONTROLLER_HPP
#define DB_TASK_CONTROLLER_HPP

#include <QMap>
#include <QtSql>

#include "Task.hpp"

class DbTaskController final
{
   private:
    QSqlDatabase db;
    QMap<int32_t, Task> taskMap;

    void retrieveTasks();
    void errorExec(const QString& lastErrorText);

   public:
    DbTaskController();

    void addNewTask(Task& task);
    int32_t getLastTask() const
    {
        return taskMap.lastKey();
    }

    void deleteTask(int32_t task_id);

    const QMap<int32_t, Task>& getMapTask() const
    {
        return taskMap;
    }

    const Task& getTask(int32_t task_id) const
    {
        return *(taskMap.find(task_id));
    }

    void setStatus(int32_t task_id, const char* status_type);

    void setTask(int32_t task_id, const Task& task);
};

#endif  // DB_TASK_CONTROLLER_HPP