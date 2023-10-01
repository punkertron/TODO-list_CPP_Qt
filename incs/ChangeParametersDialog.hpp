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
    QLineEdit* m_lineName;
    QTextEdit* m_textDescription;
    QCalendarWidget* m_calDate;

   private slots:
    void onOKButtonClicked();
    void onCancelButtonClicked();

   public:
    ChangeParametersDialog()                                                   = delete;
    ~ChangeParametersDialog()                                                  = default;
    ChangeParametersDialog(const ChangeParametersDialog& /*other*/)            = delete;
    ChangeParametersDialog(ChangeParametersDialog&& /*other*/)                 = delete;
    ChangeParametersDialog& operator=(const ChangeParametersDialog& /*other*/) = delete;

    ChangeParametersDialog(const Task& task);

   signals:
    void userDataEntered(Task& task);
};

#endif  // CHANGE_PARAMETERS_DIALOG_HPP