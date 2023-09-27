#include "FilterDialog.hpp"

#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

// TODO: pointers should be members of the class?

FilterDialog::FilterDialog(QWidget* parent) : QDialog(parent)
{
    setWindowTitle("Filter Tasks");
    setMinimumWidth(400);
    // setMinimumSize(QSize(400, 400));
    setWindowIcon(QIcon("../icons/filter_icon.png"));

    QLabel* selectStatus   = new QLabel("Select status (All by default):", this);
    QCheckBox* cbxProgress = new QCheckBox("In progress", this);
    QCheckBox* cbxDone     = new QCheckBox("Done", this);

    QLabel* filterName  = new QLabel("Enter name (case NON-sensitive, maybe NOT full):", this);
    QLineEdit* lineName = new QLineEdit(this);

    QLabel* filterDescription  = new QLabel("Enter description (case NON-sensitive, maybe NOT full):", this);
    QLineEdit* lineDescription = new QLineEdit(this);

    QPushButton* okButton     = new QPushButton("OK", this);
    QPushButton* cancelButton = new QPushButton("Cancel", this);

    QVBoxLayout* v_layout = new QVBoxLayout;

    v_layout->addWidget(selectStatus);
    v_layout->addWidget(cbxProgress);
    v_layout->addWidget(cbxDone);

    v_layout->addSpacerItem(new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed));

    v_layout->addWidget(filterName);
    v_layout->addWidget(lineName);

    v_layout->addSpacerItem(new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed));

    v_layout->addWidget(filterDescription);
    v_layout->addWidget(lineDescription);

    v_layout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed));

    QHBoxLayout* h_layout = new QHBoxLayout;
    h_layout->addWidget(okButton);
    h_layout->addWidget(cancelButton);

    v_layout->addLayout(h_layout);

    setLayout(v_layout);
}