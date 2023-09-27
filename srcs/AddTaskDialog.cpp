#include "AddTaskDialog.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

// TODO: pointers should be members of the class?

AddTaskDialog::AddTaskDialog(QWidget* parent) : QDialog(parent)
{
    setWindowTitle("Add New Task");
    setMinimumSize(QSize(400, 400));
    setWindowIcon(QIcon("../icons/add_task.png"));

    QLabel* enter_name = new QLabel("Enter name:", this);
    m_Enter_name       = new QLineEdit(this);

    QLabel* enter_description = new QLabel("Enter description (optional):", this);
    m_Enter_description       = new QTextEdit(this);

    QLabel* enter_deadline_date = new QLabel("Select deadline (optional):", this);
    m_Enter_deadline_date       = new QCalendarWidget(this);

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
}
