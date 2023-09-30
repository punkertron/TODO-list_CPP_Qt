#ifndef TASK_HPP
#define TASK_HPP

#include <QDate>

struct Task
{
   public:
    int32_t task_id = 0;
    QString m_name;
    QString m_description = "";
    QDate m_deadline_date;
    QString m_task_status = "default";
    bool isVisible        = true;

    Task() = default;

    Task(int32_t task_id, const QString& name, const QString& description, const QDate& deadline_date,
         const QString& task_status) :
        task_id(task_id),
        m_name(name),
        m_description(description),
        m_deadline_date(deadline_date),
        m_task_status(task_status)
    {
    }
};

#endif  // TASK_HPP