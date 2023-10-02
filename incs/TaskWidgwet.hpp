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

class TaskWidget final : public QWidget
{
    Q_OBJECT

   private:
    DbTaskController* m_dbTaskController;
    int32_t m_task_id;

    QLabel* m_name;
    QLabel* m_deadline_date;
    QLabel* m_description = nullptr;
    QWidget* m_line       = nullptr;

    QHBoxLayout* m_hLayoutNameDate;
    QVBoxLayout* m_vLayoutTask;
    QVBoxLayout* m_vLayoutButtons;
    QHBoxLayout* m_hMainLayout;

    QPushButton* m_resume;
    QPushButton* m_pause;
    QPushButton* m_done;

    bool m_isDescriptionExists;

    bool m_selected = false;

    void fillColour();

    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

    void setSelected(bool selected)
    {
        this->m_selected = selected;
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
    TaskWidget()                                       = delete;
    ~TaskWidget()                                      = default;
    TaskWidget(const TaskWidget& /*other*/)            = delete;
    TaskWidget(TaskWidget&& /*other*/)                 = delete;
    TaskWidget& operator=(const TaskWidget& /*other*/) = delete;

    TaskWidget(int32_t task_id, DbTaskController* dbTaskController, QWidget* parent = nullptr);

    bool isSelected() const
    {
        return m_selected;
    }

    int32_t getTaskId() const
    {
        return m_task_id;
    }

   signals:
    void taskParamsChanged(int32_t task_id);  // if data changes we should update our view according filters
};

#endif  // TASK_WIDGET_HPP