#include "../incs/ChangeParametersDialog.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

ChangeParametersDialog::ChangeParametersDialog(const Task& task) :
    m_Enter_name(new QLineEdit(task.m_name, this)),
    m_Enter_description(new QTextEdit(task.m_description, this)),
    m_Enter_deadline_date(new QCalendarWidget(this))
{
    m_Enter_deadline_date->setSelectedDate(task.m_deadline_date);
    m_Enter_deadline_date->setFirstDayOfWeek(Qt::DayOfWeek::Monday);

    setWindowTitle("Change task parameters");
    setMinimumSize(QSize(400, 400));
    setWindowIcon(QIcon("../icons/change_parameters.png"));

    QLabel* enter_name          = new QLabel("Change Name:", this);
    QLabel* enter_description   = new QLabel("Change Description (optional):", this);
    QLabel* enter_deadline_date = new QLabel("Change Deadline:", this);

    QPushButton* okButton     = new QPushButton("OK", this);
    QPushButton* cancelButton = new QPushButton("Cancel", this);

    QVBoxLayout* v_layout = new QVBoxLayout;

    v_layout->addWidget(enter_name);
    v_layout->addWidget(m_Enter_name);

    v_layout->addSpacerItem(new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed));

    v_layout->addWidget(enter_description);
    v_layout->addWidget(m_Enter_description);

    v_layout->addSpacerItem(new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed));

    v_layout->addWidget(enter_deadline_date);
    v_layout->addWidget(m_Enter_deadline_date);

    v_layout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed));

    QHBoxLayout* h_layout = new QHBoxLayout;
    h_layout->addWidget(okButton);
    h_layout->addWidget(cancelButton);

    v_layout->addLayout(h_layout);

    setLayout(v_layout);

    connect(okButton, &QPushButton::clicked, this, &ChangeParametersDialog::onOKButtonClicked);
    connect(cancelButton, &QPushButton::clicked, this, &ChangeParametersDialog::onCancelButtonClicked);
}

void ChangeParametersDialog::onOKButtonClicked()
{
    if (m_Enter_name->text().isEmpty())
    {
        QMessageBox::critical(this, "Invalid Input", "Please enter Name.");
        return;
    }

    Task task;

    task.m_name          = m_Enter_name->text();
    task.m_description   = m_Enter_description->toPlainText();
    task.m_deadline_date = m_Enter_deadline_date->selectedDate();

    // Emit the signal with the collected data
    emit userDataEntered(task);

    // Close the dialog
    accept();
}

void ChangeParametersDialog::onCancelButtonClicked()
{
    reject();
}