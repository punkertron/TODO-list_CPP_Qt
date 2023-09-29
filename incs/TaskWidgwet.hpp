#ifndef TASK_WIDGET_HPP
#define TASK_WIDGET_HPP

#include <QWidget>

#include "Task.hpp"

class TaskWidget : public QWidget
{
    Q_OBJECT

   private:
    uint32_t task_id;
    QString m_task_status;
    QDate deadline_date;

    void fillColour();

   private slots:
    void onResumeButtonClicked();
    void onPauseButtonClicked();
    void onDoneButtonClicked();

   public:
    TaskWidget(const Task& task, QWidget* parent = nullptr);
};

#endif  // TASK_WIDGET_HPP