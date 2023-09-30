#ifndef TASK_WIDGET_HPP
#define TASK_WIDGET_HPP

#include <QHBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "DbTaskController.hpp"
#include "Task.hpp"

class TaskWidget : public QWidget
{
    Q_OBJECT

   private:
    DbTaskController* dbTaskController;
    int32_t task_id;

    QLabel* name;
    QLabel* deadline_date;
    QLabel* description = nullptr;
    QWidget* line       = nullptr;

    QHBoxLayout* hLayout;
    QVBoxLayout* vLayoutTask;
    QVBoxLayout* vLayoutButtons;
    QHBoxLayout* mainLayout;

    QPushButton* resume;
    QPushButton* pause;
    QPushButton* done;

    bool isDescriptionExists;

    bool selected = false;

    void fillColour();

    void paintEvent(QPaintEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;

    void setSelected(bool selected)
    {
        this->selected = selected;
        update();  // Request widget repaint to reflect the change
    }

    void contextMenuEvent(QContextMenuEvent* event) override;

    void setButtons();
    void prepareLayouts();
    void prepareWidgets();
    void prepareDescription();
    void formatWidgets();
    void formatDescriptionLayout();
    void formatLayouts();
    void formatDescription();
    void removeDescription();

   private slots:
    void onResumeButtonClicked();
    void onPauseButtonClicked();
    void onDoneButtonClicked();
    void onUserDataEntered(Task& task);

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