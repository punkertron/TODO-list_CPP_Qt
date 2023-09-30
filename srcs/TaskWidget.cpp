#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include <QVBoxLayout>

#include "../incs/TaskWidgwet.hpp"

TaskWidget::TaskWidget(const Task& task, QWidget* parent) :
    QWidget(parent), task_id(task.task_id), m_task_status(task.m_task_status), deadline_date(task.m_deadline_date)
{
    QString res  = QString("Task: <b>%1</b>").arg(task.m_name.left(40) + (task.m_name.size() > 40 ? "..." : ""));
    QLabel* name = new QLabel(res);
    name->setTextFormat(Qt::RichText);
    name->setIndent(10);

    QString deadlineStr   = QString("Deadline: <b>%1</b>").arg(deadline_date.toString("d MMM, dddd"));
    QLabel* deadline_date = new QLabel(deadlineStr);
    deadline_date->setTextFormat(Qt::RichText);
    deadline_date->setStyleSheet("margin-right: 10px;");

    QLabel* description;
    QWidget* line;
    if (task.m_description.size())  // no descr. if empty
    {
        line = new QWidget;
        line->setFixedHeight(2);
        line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        line->setStyleSheet(QString("margin-right: 10px; background-color: #000000;"));

        description =
            new QLabel("Description: " + task.m_description.left(230) + (task.m_description.size() > 230 ? "..." : ""));
        description->setWordWrap(true);
        description->setIndent(10);
        description->setStyleSheet("margin-right: 10px;");
    }

    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addWidget(name, 1);
    hLayout->addWidget(deadline_date, 0, Qt::AlignRight);
    hLayout->setSpacing(0);

    QVBoxLayout* vLayoutTask = new QVBoxLayout;
    vLayoutTask->addLayout(hLayout);

    if (task.m_description.size())
    {
        vLayoutTask->addWidget(line);
        vLayoutTask->addWidget(description);
    }

    vLayoutTask->setSpacing(0);

    QPushButton* resume = new QPushButton(QIcon("../icons/resume.png"), "", this);
    QPushButton* pause  = new QPushButton(QIcon("../icons/pause.png"), "", this);
    QPushButton* done   = new QPushButton(QIcon("../icons/done.png"), "", this);

    resume->setIconSize(QSize(30, 30));
    pause->setIconSize(QSize(30, 30));
    done->setIconSize(QSize(30, 30));

    QVBoxLayout* vLayoutButtons = new QVBoxLayout;
    vLayoutButtons->addWidget(resume);
    vLayoutButtons->addWidget(pause);
    vLayoutButtons->addWidget(done);
    vLayoutButtons->setSpacing(0);

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->addLayout(vLayoutButtons);
    mainLayout->addLayout(vLayoutTask);
    mainLayout->setSpacing(10);

    setFixedHeight(120);
    // setMaximumWidth(690);
    // setMinimumWidth(670);

    fillColour();

    connect(resume, &QPushButton::clicked, this, &TaskWidget::onResumeButtonClicked);
    connect(pause, &QPushButton::clicked, this, &TaskWidget::onPauseButtonClicked);
    connect(done, &QPushButton::clicked, this, &TaskWidget::onDoneButtonClicked);
}

// TODO: change status in Database

void TaskWidget::onResumeButtonClicked()
{
    m_task_status = "in progress";
    fillColour();
}

void TaskWidget::onPauseButtonClicked()
{
    m_task_status = "default";
    fillColour();
}

void TaskWidget::onDoneButtonClicked()
{
    m_task_status = "done";
    fillColour();
}

void TaskWidget::fillColour()
{
    if (m_task_status == "default" && deadline_date < QDate::currentDate())
        setStyleSheet("background-color:  #FF855B;");  // #FE5733
    else if (m_task_status == "default")
        setStyleSheet("background-color: #FEFEFE;");
    else if (m_task_status == "in progress")
        setStyleSheet("background-color: #FEF233;");
    else  // done
        setStyleSheet("background-color: #33FE39;");
}

void TaskWidget::paintEvent(QPaintEvent* /*event*/)
{
    QPainter painter(this);
    if (selected)
        painter.fillRect(rect(), QColor("#B3D9FF"));
    else
        painter.fillRect(rect(), QColor("#FEFEFE"));
}
