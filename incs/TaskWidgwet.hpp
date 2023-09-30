#ifndef TASK_WIDGET_HPP
#define TASK_WIDGET_HPP

#include <QWidget>

#include "DbTaskController.hpp"
#include "Task.hpp"

class TaskWidget : public QWidget
{
    Q_OBJECT

   private:
    DbTaskController* dbTaskController;
    int32_t task_id;

    bool selected = false;

    void fillColour();

    void paintEvent(QPaintEvent* event) override;

    void mousePressEvent(QMouseEvent* /*event*/) override
    {
        setSelected(!isSelected());
        emit selectionChanged(selected);
    }

    void setSelected(bool selected)
    {
        this->selected = selected;
        update();  // Request widget repaint to reflect the change
    }

   signals:
    void selectionChanged(bool selected);

   private slots:
    void onResumeButtonClicked();
    void onPauseButtonClicked();
    void onDoneButtonClicked();

   public:
    TaskWidget(int32_t task_id, DbTaskController* dbTaskController, QWidget* parent = nullptr);

    bool isSelected() const
    {
        return selected;
    }

    int32_t getTaskId() const
    {
        return task_id;
    }
};

#endif  // TASK_WIDGET_HPP