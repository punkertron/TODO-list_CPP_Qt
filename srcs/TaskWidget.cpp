#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include <QVBoxLayout>

#include "../incs/TaskWidgwet.hpp"

TaskWidget::TaskWidget(int32_t task_id, DbTaskController* dbTaskController, QWidget* parent) :
    QWidget(parent), dbTaskController(dbTaskController), task_id(task_id)
{
    QString nameStr = dbTaskController->getTask(task_id).m_name;
    QString res     = QString("Task: <b>%1</b>").arg(nameStr.left(40) + (nameStr.size() > 40 ? "..." : ""));
    QLabel* name    = new QLabel(res);
    name->setTextFormat(Qt::RichText);
    name->setIndent(10);

    QDate date            = dbTaskController->getTask(task_id).m_deadline_date;
    QString deadlineStr   = QString("Deadline: <b>%1</b>").arg(date.toString("d MMM, dddd"));
    QLabel* deadline_date = new QLabel(deadlineStr);
    deadline_date->setTextFormat(Qt::RichText);
    deadline_date->setStyleSheet("margin-right: 10px;");

    QLabel* description;
    QWidget* line;
    QString descriptionStr = dbTaskController->getTask(task_id).m_description;
    if (descriptionStr.size())  // no descr. if empty
    {
        line = new QWidget;
        line->setFixedHeight(2);
        line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        line->setStyleSheet(QString("margin-right: 10px; background-color: #000000;"));

        description = new QLabel("Description: " + descriptionStr.left(250) + (descriptionStr.size() > 250 ? "..." : ""));
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

    if (descriptionStr.size())
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

    setFixedSize(QSize(715, 120));
    // setFixedHeight(120);

    fillColour();

    connect(resume, &QPushButton::clicked, this, &TaskWidget::onResumeButtonClicked);
    connect(pause, &QPushButton::clicked, this, &TaskWidget::onPauseButtonClicked);
    connect(done, &QPushButton::clicked, this, &TaskWidget::onDoneButtonClicked);
}

// TODO: change status in Database

void TaskWidget::onResumeButtonClicked()
{
    const char* s = "in progress";
    dbTaskController->setStatus(task_id, s);
    fillColour();
}

void TaskWidget::onPauseButtonClicked()
{
    const char* s = "default";
    dbTaskController->setStatus(task_id, s);
    fillColour();
}

void TaskWidget::onDoneButtonClicked()
{
    const char* s = "done";
    dbTaskController->setStatus(task_id, s);
    fillColour();
}

void TaskWidget::fillColour()
{
    QString statusStr = dbTaskController->getTask(task_id).m_task_status;
    QDate date        = dbTaskController->getTask(task_id).m_deadline_date;
    if (statusStr == "default" && date < QDate::currentDate())
        setStyleSheet("background-color:  #FF855B;");  // #FE5733
    else if (statusStr == "default")
        setStyleSheet("background-color: #FEFEFE;");
    else if (statusStr == "in progress")
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
