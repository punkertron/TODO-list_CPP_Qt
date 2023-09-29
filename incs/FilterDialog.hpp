#ifndef FILTER_DIALOG_HPP
#define FILTER_DIALOG_HPP

#include <QDialog>

class FilterDialog : public QDialog
{
    Q_OBJECT

   private:
    // QLineEdit* m_Enter_name;
    // QTextEdit* m_Enter_description;
    // QCalendarWidget* m_Enter_deadline_date;
    // std::string m_Enter_task_status;

   public:
    FilterDialog(QWidget* parent = nullptr);
    ~FilterDialog() = default;
};

#endif  // FILTER_DIALOG_HPP