#include "../incs/FilterDialog.hpp"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "../incs/FilterParams.hpp"

FilterDialog::FilterDialog(FilterParams* filterParams, QWidget* parent) : QDialog(parent), filterParams(filterParams)
{
    setWindowTitle("Filter Tasks");
    setMinimumSize(QSize(600, 500));
    setWindowIcon(QIcon("../icons/filter_icon.png"));

    cbxDefault  = new QCheckBox("default", this);
    cbxProgress = new QCheckBox("in progress", this);
    cbxDone     = new QCheckBox("done", this);
    cbxDefault->setChecked(filterParams->m_defaultTaskStatus);
    cbxProgress->setChecked(filterParams->m_progressTaskStatus);
    cbxDone->setChecked(filterParams->m_doneTaskStatus);

    lineName        = new QLineEdit(filterParams->m_name, this);
    lineDescription = new QLineEdit(filterParams->m_description, this);

    QVBoxLayout* mainLayout = new QVBoxLayout;

    mainLayout->addWidget(new QLabel("Select status (All by default):", this));
    mainLayout->addWidget(cbxDefault);
    mainLayout->addWidget(cbxProgress);
    mainLayout->addWidget(cbxDone);
    mainLayout->addSpacerItem(new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed));
    mainLayout->addWidget(new QLabel("Enter name (case NON-sensitive, maybe NOT full):", this));
    mainLayout->addWidget(lineName);
    mainLayout->addSpacerItem(new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed));
    mainLayout->addWidget(new QLabel("Enter description (case NON-sensitive, maybe NOT full):", this));
    mainLayout->addWidget(lineDescription);
    mainLayout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed));

    minDate = new QCalendarWidget(this);
    maxDate = new QCalendarWidget(this);

    minDate->setFirstDayOfWeek(Qt::DayOfWeek::Monday);
    maxDate->setFirstDayOfWeek(Qt::DayOfWeek::Monday);
    minDate->setSelectedDate(filterParams->m_minDate);
    maxDate->setSelectedDate(filterParams->m_maxDate);

    QVBoxLayout* calStartLayout = new QVBoxLayout;
    calStartLayout->addWidget(new QLabel("Enter min. date:", this));
    calStartLayout->addWidget(minDate);

    QVBoxLayout* calEndLayout = new QVBoxLayout;
    calEndLayout->addWidget(new QLabel("Enter max. date:", this));
    calEndLayout->addWidget(maxDate);

    QHBoxLayout* calLayout = new QHBoxLayout;
    calLayout->addLayout(calStartLayout);
    calLayout->addLayout(calEndLayout);

    mainLayout->addLayout(calLayout);

    QPushButton* okButton      = new QPushButton("OK", this);
    QPushButton* cancelButton  = new QPushButton("Cancel", this);
    QHBoxLayout* buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(okButton);
    buttonsLayout->addWidget(cancelButton);

    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);

    connect(okButton, &QPushButton::clicked, this, &FilterDialog::onOKButtonClicked);
    connect(cancelButton, &QPushButton::clicked, this, &FilterDialog::onCancelButtonClicked);
}

void FilterDialog::onCancelButtonClicked()
{
    reject();
}

#include <iostream>

void FilterDialog::onOKButtonClicked()
{
    FilterParams userChoice(lineName->text(), lineDescription->text(), cbxDefault->isChecked(), cbxProgress->isChecked(),
                            cbxDone->isChecked(), minDate->selectedDate(), maxDate->selectedDate());

    if (!(filterParams->isEqual(userChoice)))
    {
        emit userDataEntered(userChoice);
    }

    accept();
}
