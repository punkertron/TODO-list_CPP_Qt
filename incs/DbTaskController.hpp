#ifndef DB_TASK_CONTROLLER_HPP
#define DB_TASK_CONTROLLER_HPP

#include <QMap>
#include <QtSql>

#include "FilterParams.hpp"
#include "Task.hpp"

class DbTaskController final
{
   private:
    QSqlDatabase db;
    QMap<int32_t, Task> taskMap;
    FilterParams filterParams;

    void retrieveTasks();
    void errorExec(const QString& lastErrorText);

   public:
    DbTaskController();

    void setFilterParams(const FilterParams& other)
    {
        filterParams = other;
    }

    void setFilterVisible(int32_t task_id);
    void setFilterVisibleAll();

    void addNewTask(Task& task);

    const Task& getLastTask() const
    {
        return taskMap.last();
    }

    int32_t getLastTaskId() const
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