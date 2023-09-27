#ifndef ADD_TASK_DIALOG_HPP
#define ADD_TASK_DIALOG_HPP

#include <QCalendarWidget>
#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>

class AddTaskDialog : public QDialog
{
    Q_OBJECT

   private:
    QLineEdit* m_Enter_name;
    QTextEdit* m_Enter_description;
    QCalendarWidget* m_Enter_deadline_date;
    // std::string m_Enter_task_status;

   public:
    AddTaskDialog(QWidget* parent = nullptr);
    ~AddTaskDialog() = default;
};

#endif  // ADD_TASK_DIALOG_HPP