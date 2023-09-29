#include "../incs/DbTaskManager.hpp"

#include <QMessageBox>
#include <iostream>

DbTaskManager::DbTaskManager() : db(QSqlDatabase::addDatabase("QPSQL"))
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
}

void DbTaskManager::addNewTask(Task& task)
{
    QSqlQuery query(db);
    query.prepare(R"(
        INSERT INTO todo.tasks (name, description, deadline_date)
        VALUES (:name, :description, :deadline_date);
    )");
    query.bindValue(":name", task.m_name);
    query.bindValue(":description", task.m_description);
    query.bindValue(":deadline_date", task.m_deadline_date);

    if (!query.exec())
    {
        QString errorMessage = "Error: Execution failure\n";
        errorMessage += "Error details: " + query.lastError().text();
        QMessageBox::critical(nullptr, "Execution failure", errorMessage);
        exit(EXIT_FAILURE);
    }

    if (taskList.size() == 0)
        task.task_id = 1;
    else
        task.task_id = taskList.front().task_id + 1;

    taskList.push_front(std::move(task));

    // std::cout << taskList.size() << std::endl;
}
