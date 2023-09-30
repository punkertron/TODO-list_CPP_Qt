#include "../incs/DbTaskController.hpp"

#include <QMessageBox>
#include <iostream>

DbTaskController::DbTaskController() : db(QSqlDatabase::addDatabase("QPSQL"))
{
    // getenv() ?

    db.setHostName("127.0.0.1");
    db.setDatabaseName("todo_db");
    db.setUserName("todo_user");
    db.setPassword("todo_user_password");

    if (!db.open())
    {
        QString errorMessage = "Error: Failed to connect to the database\n";
        errorMessage += "Error details: " + db.lastError().text();
        QMessageBox::critical(nullptr, "Database Connection Error", errorMessage);
        exit(EXIT_FAILURE);
    }

    // retrieve all tasks from db
    retrieveTasks();
}

void DbTaskController::retrieveTasks()
{
    QSqlQuery query(db);
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
            taskMap[query.value(0).toInt()] = std::move(task);
        }
    }
    else
    {
        errorExec(query.lastError().text());
    }

    // for (auto& t : taskList)
    // {
    //     std::cout << t.task_id << t.m_name.toStdString() << t.m_description.toStdString()
    //               << t.m_deadline_date.toString().toStdString() << t.m_task_status.toStdString() << std::endl;
    // }
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
    if (taskMap.isEmpty())
        idNewTask = 0;
    else
        idNewTask = taskMap.lastKey() + 1;

    QSqlQuery query(db);
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

    taskMap[idNewTask] = std::move(task);
}

void DbTaskController::deleteTask(int32_t task_id)
{
    QSqlQuery query(db);
    query.prepare(R"(
        DELETE FROM todo.tasks
        WHERE task_id = :task_id;
    )");
    query.bindValue(":task_id", task_id);

    if (!query.exec())
        errorExec(query.lastError().text());

    taskMap.remove(task_id);
}

void DbTaskController::setStatus(int32_t task_id, const char* task_status)
{
    QSqlQuery query(db);
    query.prepare(R"(
        UPDATE todo.tasks
        SET task_status = :task_status
        WHERE task_id = :task_id;
    )");
    query.bindValue(":task_status", task_status);
    query.bindValue(":task_id", task_id);

    if (!query.exec())
        errorExec(query.lastError().text());

    taskMap[task_id].m_task_status = task_status;
}

void DbTaskController::setTask(int32_t task_id, const Task& task)
{
    QSqlQuery query(db);
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

    taskMap[task_id] = task;
}
