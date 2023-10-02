#include "../incs/DbTaskController.hpp"

#include <QMessageBox>
#include <algorithm>

DbTaskController::DbTaskController() : m_db(QSqlDatabase::addDatabase("QPSQL"))
{
    // getenv() ?

    m_db.setHostName("127.0.0.1");
    m_db.setDatabaseName("todo_db");
    m_db.setUserName("todo_user");
    m_db.setPassword("todo_user_password");

    if (!m_db.open())
    {
        QString errorMessage = "Error: Failed to connect to the database\n";
        errorMessage += "Error details: " + m_db.lastError().text();
        QMessageBox::critical(nullptr, "Database Connection Error", errorMessage);
        exit(EXIT_FAILURE);
    }

    // retrieve all tasks from Db
    retrieveTasks();
}

void DbTaskController::retrieveTasks()
{
    QSqlQuery query(m_db);
    query.prepare(R"(
        SELECT task_id, name, description, deadline_date, task_status
        FROM todo.tasks
        ORDER BY task_id;
    )");

    if (query.exec())
    {
        while (query.next())
        {
            Task task(query.value(1).toString(), query.value(2).toString(), query.value(3).toDate(),
                      query.value(4).toString());
            m_taskMap[query.value(0).toInt()] = std::move(task);
        }
    }
    else
        errorExec(query.lastError().text());
}

void DbTaskController::errorExec(const QString& lastErrorText)
{
    QString errorMessage = "Error: Execution failure\n";
    errorMessage += "Error details: " + lastErrorText;
    QMessageBox::critical(nullptr, "Execution failure", errorMessage);
    exit(EXIT_FAILURE);
}

void DbTaskController::addNewTask(Task& task)
{
    int32_t idNewTask;
    if (m_taskMap.isEmpty())
        idNewTask = 0;
    else
        idNewTask = m_taskMap.lastKey() + 1;

    QSqlQuery query(m_db);
    query.prepare(R"(
        INSERT INTO todo.tasks (task_id, name, description, deadline_date)
        VALUES (:task_id, :name, :description, :deadline_date);
    )");

    query.bindValue(":task_id", idNewTask);
    query.bindValue(":name", task.m_name);
    query.bindValue(":description", task.m_description);
    query.bindValue(":deadline_date", task.m_deadline_date);

    if (!query.exec())
        errorExec(query.lastError().text());

    m_taskMap[idNewTask] = std::move(task);
}

void DbTaskController::deleteTask(int32_t task_id)
{
    QSqlQuery query(m_db);
    query.prepare(R"(
        DELETE FROM todo.tasks
        WHERE task_id = :task_id;
    )");
    query.bindValue(":task_id", task_id);

    if (!query.exec())
        errorExec(query.lastError().text());

    m_taskMap.remove(task_id);
}

void DbTaskController::setStatus(int32_t task_id, const char* task_status)
{
    QSqlQuery query(m_db);
    query.prepare(R"(
        UPDATE todo.tasks
        SET task_status = :task_status
        WHERE task_id = :task_id;
    )");
    query.bindValue(":task_status", task_status);
    query.bindValue(":task_id", task_id);

    if (!query.exec())
        errorExec(query.lastError().text());

    m_taskMap[task_id].m_task_status = task_status;
}

void DbTaskController::setTask(int32_t task_id, const Task& task)
{
    QSqlQuery query(m_db);
    query.prepare(R"(
        UPDATE todo.tasks
        SET name = :name,
            description = :description,
            deadline_date = :deadline_date
        WHERE task_id = :task_id;
    )");
    query.bindValue(":name", task.m_name);
    query.bindValue(":description", task.m_description);
    query.bindValue(":deadline_date", task.m_deadline_date);
    query.bindValue(":task_id", task_id);

    if (!query.exec())
        errorExec(query.lastError().text());

    m_taskMap[task_id] = task;
    setFilterVisible(task_id);
}

// check filter condition. if something wrong then isVisible = false
void DbTaskController::setFilterVisible(int32_t task_id)
{
    Task task = m_taskMap[task_id];

    bool a = m_filterParams.m_name == "" ? true : task.m_name.toLower().contains(m_filterParams.m_name.toLower());
    bool b = m_filterParams.m_description == ""
                 ? true
                 : task.m_description.toLower().contains(m_filterParams.m_description.toLower());
    bool c = task.m_deadline_date >= m_filterParams.m_minDate;
    bool d = task.m_deadline_date <= m_filterParams.m_maxDate;
    bool e = (m_filterParams.m_defaultTaskStatus && task.m_task_status == "default") ||
             (m_filterParams.m_progressTaskStatus && task.m_task_status == "in progress") ||
             (m_filterParams.m_doneTaskStatus && task.m_task_status == "done");

    if (a && b && c && d && e)
        m_taskMap[task_id].m_isVisible = true;
    else
        m_taskMap[task_id].m_isVisible = false;
}

void DbTaskController::setFilterVisibleAll()
{
    for (const auto& [key, value] : m_taskMap.toStdMap())
        setFilterVisible(key);
}

static bool compareDateAsc(const std::pair<int32_t, Task>& a, const std::pair<int32_t, Task>& b)
{
    return a.second.m_deadline_date > b.second.m_deadline_date;
}

static bool compareDateDesc(const std::pair<int32_t, Task>& a, const std::pair<int32_t, Task>& b)
{
    return a.second.m_deadline_date < b.second.m_deadline_date;
}

const QVector<std::pair<int32_t, Task> > DbTaskController::getSortedTasks(sortOption opt)
{
    QVector<std::pair<int32_t, Task> > res;
    res.reserve(m_taskMap.size());

    for (const auto& [key, value] : m_taskMap.toStdMap())
        res.push_back({key, value});

    switch (opt)
    {
        case sortOption::DateAsc:
            std::stable_sort(res.begin(), res.end(), compareDateAsc);
            break;

        case sortOption::DateDesc:
            std::stable_sort(res.begin(), res.end(), compareDateDesc);
            break;

        default:
            break;
    }

    return res;
}
