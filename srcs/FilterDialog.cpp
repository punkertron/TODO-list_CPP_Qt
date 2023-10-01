#include "../incs/FilterDialog.hpp"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "../incs/FilterParams.hpp"

FilterDialog::FilterDialog(FilterParams* filterParams, QWidget* parent) : QDialog(parent), m_filterParams(filterParams)
{
    setWindowTitle("Filter Tasks");
    setMinimumSize(QSize(600, 500));
    setWindowIcon(QIcon("./icons/filter_icon.png"));

    m_cbxDefault  = new QCheckBox("default", this);
    m_cbxProgress = new QCheckBox("in progress", this);
    m_cbxDone     = new QCheckBox("done", this);
    m_cbxDefault->setChecked(filterParams->m_defaultTaskStatus);
    m_cbxProgress->setChecked(filterParams->m_progressTaskStatus);
    m_cbxDone->setChecked(filterParams->m_doneTaskStatus);

    m_lineName        = new QLineEdit(filterParams->m_name, this);
    m_lineDescription = new QLineEdit(filterParams->m_description, this);

    QVBoxLayout* vMainLayout = new QVBoxLayout;

    vMainLayout->addWidget(new QLabel("Select status (All by default):", this));
    vMainLayout->addWidget(m_cbxDefault);
    vMainLayout->addWidget(m_cbxProgress);
    vMainLayout->addWidget(m_cbxDone);
    vMainLayout->addSpacerItem(new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed));
    vMainLayout->addWidget(new QLabel("Enter name (case NON-sensitive, maybe NOT full):", this));
    vMainLayout->addWidget(m_lineName);
    vMainLayout->addSpacerItem(new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed));
    vMainLayout->addWidget(new QLabel("Enter description (case NON-sensitive, maybe NOT full):", this));
    vMainLayout->addWidget(m_lineDescription);
    vMainLayout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed));

    m_minDate = new QCalendarWidget(this);
    m_maxDate = new QCalendarWidget(this);

    m_minDate->setFirstDayOfWeek(Qt::DayOfWeek::Monday);
    m_maxDate->setFirstDayOfWeek(Qt::DayOfWeek::Monday);
    m_minDate->setSelectedDate(filterParams->m_minDate);
    m_maxDate->setSelectedDate(filterParams->m_maxDate);

    QVBoxLayout* vMinDateLayout = new QVBoxLayout;
    vMinDateLayout->addWidget(new QLabel("Enter min. date:", this));
    vMinDateLayout->addWidget(m_minDate);

    QVBoxLayout* vMaxDateLayout = new QVBoxLayout;
    vMaxDateLayout->addWidget(new QLabel("Enter max. date:", this));
    vMaxDateLayout->addWidget(m_maxDate);

    QHBoxLayout* hDatesLayout = new QHBoxLayout;
    hDatesLayout->addLayout(vMinDateLayout);
    hDatesLayout->addLayout(vMaxDateLayout);

    vMainLayout->addLayout(hDatesLayout);

    QPushButton* okButton       = new QPushButton("OK", this);
    QPushButton* cancelButton   = new QPushButton("Cancel", this);
    QHBoxLayout* hButtonsLayout = new QHBoxLayout;
    hButtonsLayout->addWidget(okButton);
    hButtonsLayout->addWidget(cancelButton);

    vMainLayout->addLayout(hButtonsLayout);

    setLayout(vMainLayout);

    connect(okButton, &QPushButton::clicked, this, &FilterDialog::onOKButtonClicked);
    connect(cancelButton, &QPushButton::clicked, this, &FilterDialog::onCancelButtonClicked);
}

void FilterDialog::onCancelButtonClicked()
{
    reject();
}

void FilterDialog::onOKButtonClicked()
{
    FilterParams userChoice(m_lineName->text(), m_lineDescription->text(), m_cbxDefault->isChecked(),
                            m_cbxProgress->isChecked(), m_cbxDone->isChecked(), m_minDate->selectedDate(),
                            m_maxDate->selectedDate());

    if (!(m_filterParams->isEqual(userChoice)))
    {
        emit userDataEntered(userChoice);
    }

    accept();
}
