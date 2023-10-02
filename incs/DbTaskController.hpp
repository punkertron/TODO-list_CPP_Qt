#ifndef DB_TASK_CONTROLLER_HPP
#define DB_TASK_CONTROLLER_HPP

#include <QMap>
#include <QVector>
#include <QtSql>

#include "FilterParams.hpp"
#include "SortDialog.hpp"
#include "Task.hpp"

class DbTaskController final
{
   private:
    QSqlDatabase m_db;
    QMap<int32_t, Task> m_taskMap;
    FilterParams m_filterParams;

    void retrieveTasks();
    void errorExec(const QString& lastErrorText);

   public:
    DbTaskController();  // exists
    ~DbTaskController()                                            = default;
    DbTaskController(const DbTaskController& /*other*/)            = delete;
    DbTaskController(DbTaskController&& /*other*/)                 = delete;
    DbTaskController& operator=(const DbTaskController& /*other*/) = delete;

    void setFilterParams(const FilterParams& other)
    {
        m_filterParams = other;
    }

    void setFilterVisible(int32_t task_id);
    void setFilterVisibleAll();

    void addNewTask(Task& task);

    const Task& getLastTask() const
    {
        return m_taskMap.last();
    }

    int32_t getLastTaskId() const
    {
        return m_taskMap.lastKey();
    }

    void deleteTask(int32_t task_id);

    const QMap<int32_t, Task>& getMapTask() const
    {
        return m_taskMap;
    }

    const Task& getTask(int32_t task_id) const
    {
        return *(m_taskMap.find(task_id));
    }

    const QVector<std::pair<int32_t, Task> > getSortedTasks(sortOption opt);

    void setStatus(int32_t task_id, const char* status_type);

    void setTask(int32_t task_id, const Task& task);
};

#endif  // DB_TASK_CONTROLLER_HPP