#ifndef FILTER_DIALOG_HPP
#define FILTER_DIALOG_HPP

#include <QCalendarWidget>
#include <QCheckBox>
#include <QDialog>
#include <QLineEdit>

#include "../incs/FilterParams.hpp"

class FilterDialog final : public QDialog
{
    Q_OBJECT

   private:
    FilterParams* m_filterParams;

    QLineEdit* m_lineName;
    QLineEdit* m_lineDescription;
    QCalendarWidget* m_minDate;
    QCalendarWidget* m_maxDate;
    QCheckBox* m_cbxDefault;
    QCheckBox* m_cbxProgress;
    QCheckBox* m_cbxDone;

   private slots:
    void onOKButtonClicked();
    void onCancelButtonClicked();

   public:
    FilterDialog()                                         = delete;
    ~FilterDialog()                                        = default;
    FilterDialog(const FilterDialog& /*other*/)            = delete;
    FilterDialog(FilterDialog&& /*other*/)                 = delete;
    FilterDialog& operator=(const FilterDialog& /*other*/) = delete;
    FilterDialog& operator=(FilterDialog&& /*other*/)      = delete;

    FilterDialog(FilterParams* filterParams, QWidget* parent = nullptr);

   signals:
    void userDataEntered(FilterParams& task);
};

#endif  // FILTER_DIALOG_HPP