#ifndef FILTER_DIALOG_HPP
#define FILTER_DIALOG_HPP

#include <QCalendarWidget>
#include <QCheckBox>
#include <QDialog>
#include <QLineEdit>

#include "../incs/FilterParams.hpp"

class FilterDialog : public QDialog
{
    Q_OBJECT

   private:
    FilterParams* filterParams;

    QLineEdit* lineName;
    QLineEdit* lineDescription;
    QCalendarWidget* minDate;
    QCalendarWidget* maxDate;
    QCheckBox* cbxDefault;
    QCheckBox* cbxProgress;
    QCheckBox* cbxDone;

   private slots:
    void onOKButtonClicked();
    void onCancelButtonClicked();

   public:
    FilterDialog(FilterParams* filterParams, QWidget* parent = nullptr);
    ~FilterDialog() = default;

   signals:
    void userDataEntered(FilterParams& task);
};

#endif  // FILTER_DIALOG_HPP