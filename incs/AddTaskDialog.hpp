#ifndef ADD_TASK_DIALOG_HPP
#define ADD_TASK_DIALOG_HPP

#include <QCalendarWidget>
#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>

#include "../incs/Task.hpp"

class AddTaskDialog final : public QDialog
{
    Q_OBJECT

   private:
    QLineEdit* m_lineName;
    QTextEdit* m_textDescription;
    QCalendarWidget* m_calDate;

   private slots:
    void onOKButtonClicked();
    void onCancelButtonClicked();

   public:
    AddTaskDialog(QWidget* parent = nullptr);
    // AddTaskDialog()                                          = default;

    ~AddTaskDialog()                                         = default;
    AddTaskDialog(const AddTaskDialog& /*other*/)            = delete;
    AddTaskDialog(AddTaskDialog&& /*other*/)                 = delete;
    AddTaskDialog& operator=(const AddTaskDialog& /*other*/) = delete;
    AddTaskDialog& operator=(AddTaskDialog&& /*other*/)      = delete;

   signals:
    void userDataEntered(Task& task);
};

#endif  // ADD_TASK_DIALOG_HPP