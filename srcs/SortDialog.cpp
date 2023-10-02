#include "../incs/SortDialog.hpp"

#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>

SortDialog::SortDialog(sortOption opt)
{
    setWindowTitle("Sort");
    setMinimumSize(QSize(200, 140));
    setWindowIcon(QIcon("./icons/sort.png"));

    rbDateAsc  = new QRadioButton("Deadline (ASC)", this);
    rbDateDesc = new QRadioButton("Deadline (DESC)", this);
    rbDefault  = new QRadioButton("default (creation date)", this);

    QPushButton* okButton       = new QPushButton("OK", this);
    QPushButton* cancelButton   = new QPushButton("Cancel", this);
    QHBoxLayout* hButtonsLayout = new QHBoxLayout;
    hButtonsLayout->addWidget(okButton);
    hButtonsLayout->addWidget(cancelButton);

    QVBoxLayout* vMainLayout = new QVBoxLayout(this);
    vMainLayout->addWidget(rbDateAsc);
    vMainLayout->addWidget(rbDateDesc);
    vMainLayout->addWidget(rbDefault);
    vMainLayout->addLayout(hButtonsLayout);

    switch (opt)
    {
        case sortOption::Default:
            rbDefault->setChecked(true);
            break;

        case sortOption::DateAsc:
            rbDateAsc->setChecked(true);
            break;
        case sortOption::DateDesc:
            rbDateDesc->setChecked(true);
            break;

        default:
            break;
    }

    // beter than slots in my other classes
    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

sortOption SortDialog::getSortOption() const
{
    if (rbDateAsc->isChecked())
        return sortOption::DateAsc;
    if (rbDateDesc->isChecked())
        return sortOption::DateDesc;
    return sortOption::Default;
}
