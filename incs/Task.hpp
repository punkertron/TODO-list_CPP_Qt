#ifndef TASK_HPP
#define TASK_HPP

#include <QDate>

struct Task
{
   public:
    QString m_name;
    QString m_description = "";
    QDate m_deadline_date;
    QString m_task_status;
    bool isVisible = true;

    Task() = default;

    Task(const QString& name, const QString& description, const QDate& deadline_date,
         const QString& task_status = "default") :
        m_name(name), m_description(description), m_deadline_date(deadline_date), m_task_status(task_status)
    {
    }
};

#endif  // TASK_HPP