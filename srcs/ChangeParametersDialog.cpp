#include "../incs/ChangeParametersDialog.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

ChangeParametersDialog::ChangeParametersDialog(const Task& task) :
    m_lineName(new QLineEdit(task.m_name, this)),
    m_textDescription(new QTextEdit(task.m_description, this)),
    m_calDate(new QCalendarWidget(this))
{
    setWindowTitle("Change task parameters");
    setMinimumSize(QSize(400, 400));
    setWindowIcon(QIcon("./icons/change_parameters.png"));

    m_calDate->setSelectedDate(task.m_deadline_date);
    m_calDate->setFirstDayOfWeek(Qt::DayOfWeek::Monday);

    QPushButton* okButton       = new QPushButton("OK", this);
    QPushButton* cancelButton   = new QPushButton("Cancel", this);
    QHBoxLayout* hButtonsLayout = new QHBoxLayout;
    hButtonsLayout->addWidget(okButton);
    hButtonsLayout->addWidget(cancelButton);

    QVBoxLayout* vMainLayout = new QVBoxLayout;

    vMainLayout->addWidget(new QLabel("Change Name:", this));
    vMainLayout->addWidget(m_lineName);
    vMainLayout->addSpacerItem(new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed));
    vMainLayout->addWidget(new QLabel("Change Description (optional):", this));
    vMainLayout->addWidget(m_textDescription);
    vMainLayout->addSpacerItem(new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed));
    vMainLayout->addWidget(new QLabel("Change Deadline:", this));
    vMainLayout->addWidget(m_calDate);
    vMainLayout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed));
    vMainLayout->addLayout(hButtonsLayout);

    setLayout(vMainLayout);

    connect(okButton, &QPushButton::clicked, this, &ChangeParametersDialog::onOKButtonClicked);
    connect(cancelButton, &QPushButton::clicked, this, &ChangeParametersDialog::onCancelButtonClicked);
}

void ChangeParametersDialog::onOKButtonClicked()
{
    if (m_lineName->text().isEmpty())
    {
        QMessageBox::critical(this, "Invalid Input", "Please enter Name.");
        return;
    }

    Task task(m_lineName->text(), m_textDescription->toPlainText(), m_calDate->selectedDate());

    emit userDataEntered(task);

    accept();
}

void ChangeParametersDialog::onCancelButtonClicked()
{
    reject();
}
