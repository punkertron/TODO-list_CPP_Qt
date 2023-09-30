#include "../incs/AddTaskDialog.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

#include "../incs/Task.hpp"

AddTaskDialog::AddTaskDialog(QWidget* parent) : QDialog(parent)
{
    setWindowTitle("Add New Task");
    setMinimumSize(QSize(400, 400));
    setWindowIcon(QIcon("../icons/add_task.png"));

    m_Enter_name          = new QLineEdit(this);
    m_Enter_description   = new QTextEdit(this);
    m_Enter_deadline_date = new QCalendarWidget(this);
    m_Enter_deadline_date->setFirstDayOfWeek(Qt::DayOfWeek::Monday);

    QVBoxLayout* mainLayout = new QVBoxLayout;

    mainLayout->addWidget(new QLabel("Enter Name:", this));
    mainLayout->addWidget(m_Enter_name);
    mainLayout->addSpacerItem(new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed));
    mainLayout->addWidget(new QLabel("Enter Description (optional):", this));
    mainLayout->addWidget(m_Enter_description);
    mainLayout->addSpacerItem(new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed));
    mainLayout->addWidget(new QLabel("Select Deadline (default - Today):", this));
    mainLayout->addWidget(m_Enter_deadline_date);
    mainLayout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed));

    QPushButton* okButton     = new QPushButton("OK", this);
    QPushButton* cancelButton = new QPushButton("Cancel", this);

    QHBoxLayout* buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(okButton);
    buttonsLayout->addWidget(cancelButton);

    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);

    connect(okButton, &QPushButton::clicked, this, &AddTaskDialog::onOKButtonClicked);
    connect(cancelButton, &QPushButton::clicked, this, &AddTaskDialog::onCancelButtonClicked);
}

void AddTaskDialog::onOKButtonClicked()
{
    if (m_Enter_name->text().isEmpty())
    {
        QMessageBox::critical(this, "Invalid Input", "Please enter Name.");
        return;
    }

    Task task(m_Enter_name->text(), m_Enter_description->toPlainText(), m_Enter_deadline_date->selectedDate());

    emit userDataEntered(task);

    accept();
}

void AddTaskDialog::onCancelButtonClicked()
{
    reject();
}
