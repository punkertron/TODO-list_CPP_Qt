#ifndef TASK_HPP
#define TASK_HPP

#include <QDate>

struct Task
{
   public:
    uint32_t task_id = 0;
    QString m_name;
    QString m_description = "";
    QDate m_deadline_date;
    QString m_task_status = "default";
    bool isVisible        = true;
};

#endif  // TASK_HPP