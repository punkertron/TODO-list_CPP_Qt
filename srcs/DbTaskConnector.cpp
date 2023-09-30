#include <QMessageBox>
#include <iostream>

#include "../incs/DbTaskController.hpp"

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
            Task task(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(), query.value(3).toDate(),
                      query.value(4).toString());
            taskList.push_front(std::move(task));
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
    if (taskList.size() == 0)
        task.task_id = 0;
    else
        task.task_id = taskList.front().task_id + 1;

    QSqlQuery query(db);
    query.prepare(R"(
        INSERT INTO todo.tasks (task_id, name, description, deadline_date)
        VALUES (:task_id, :name, :description, :deadline_date);
    )");

    query.bindValue(":task_id", task.task_id);
    query.bindValue(":name", task.m_name);
    query.bindValue(":description", task.m_description);
    query.bindValue(":deadline_date", task.m_deadline_date);

    if (!query.exec())
        errorExec(query.lastError().text());

    taskList.push_front(std::move(task));
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

    taskList.removeIf(
        [task_id](const Task& t)
        {
            return t.task_id == task_id;
        });
}
