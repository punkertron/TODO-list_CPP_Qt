#ifndef CHANGE_PARAMETERS_DIALOG_HPP
#define CHANGE_PARAMETERS_DIALOG_HPP

#include <QCalendarWidget>
#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>

#include "Task.hpp"

class ChangeParametersDialog final : public QDialog
{
    Q_OBJECT

   private:
    QLineEdit* m_Enter_name;
    QTextEdit* m_Enter_description;
    QCalendarWidget* m_Enter_deadline_date;

   private slots:
    void onOKButtonClicked();
    void onCancelButtonClicked();

   public:
    ChangeParametersDialog() = delete;
    ChangeParametersDialog(const Task& task);

   signals:
    void userDataEntered(Task& task);
};

#endif  // CHANGE_PARAMETERS_DIALOG_HPP