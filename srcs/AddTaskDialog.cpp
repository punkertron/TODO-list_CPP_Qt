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
    setWindowIcon(QIcon("./icons/add_task.png"));

    m_lineName        = new QLineEdit(this);
    m_textDescription = new QTextEdit(this);
    m_calDate         = new QCalendarWidget(this);
    m_calDate->setFirstDayOfWeek(Qt::DayOfWeek::Monday);

    QPushButton* okButton       = new QPushButton("OK", this);
    QPushButton* cancelButton   = new QPushButton("Cancel", this);
    QHBoxLayout* hButtonsLayout = new QHBoxLayout;
    hButtonsLayout->addWidget(okButton);
    hButtonsLayout->addWidget(cancelButton);

    QVBoxLayout* vMainLayout = new QVBoxLayout;

    vMainLayout->addWidget(new QLabel("Enter Name:", this));
    vMainLayout->addWidget(m_lineName);
    vMainLayout->addSpacerItem(new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed));
    vMainLayout->addWidget(new QLabel("Enter Description (optional):", this));
    vMainLayout->addWidget(m_textDescription);
    vMainLayout->addSpacerItem(new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed));
    vMainLayout->addWidget(new QLabel("Select Deadline (default - Today):", this));
    vMainLayout->addWidget(m_calDate);
    vMainLayout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed));
    vMainLayout->addLayout(hButtonsLayout);

    setLayout(vMainLayout);

    connect(okButton, &QPushButton::clicked, this, &AddTaskDialog::onOKButtonClicked);
    connect(cancelButton, &QPushButton::clicked, this, &AddTaskDialog::onCancelButtonClicked);
}

void AddTaskDialog::onOKButtonClicked()
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

void AddTaskDialog::onCancelButtonClicked()
{
    reject();
}
