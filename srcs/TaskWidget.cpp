#include "../incs/TaskWidgwet.hpp"

TaskWidget::TaskWidget(int32_t task_id, DbTaskController* dbTaskController, QWidget* parent) :
    QWidget(parent),
    dbTaskController(dbTaskController),
    task_id(task_id),
    isDescriptionExists(dbTaskController->getTask(task_id).m_description.size())
{
    setButtons();

    prepareLayouts();
    prepareWidgets();

    formatWidgets();
    formatLayouts();

    setFixedSize(QSize(715, 120));
    fillColour();
}

void TaskWidget::formatLayouts()
{
    hLayout->addWidget(name, 1);
    hLayout->addWidget(deadline_date, 0, Qt::AlignRight);

    vLayoutTask->addLayout(hLayout);

    if (isDescriptionExists)
        formatDescription();

    vLayoutButtons->addWidget(resume);
    vLayoutButtons->addWidget(pause);
    vLayoutButtons->addWidget(done);

    mainLayout->addLayout(vLayoutButtons);
    mainLayout->addLayout(vLayoutTask);
}

void TaskWidget::formatWidgets()
{
    QString nameStr = dbTaskController->getTask(task_id).m_name;
    QString nameRes = QString("Task: <b>%1</b>").arg(nameStr.left(40) + (nameStr.size() > 40 ? "..." : ""));
    name->setText(nameRes);

    QDate date          = dbTaskController->getTask(task_id).m_deadline_date;
    QString deadlineStr = QString("Deadline: <b>%1</b>").arg(date.toString("d MMM, dddd"));
    deadline_date->setText(deadlineStr);
}

void TaskWidget::setButtons()
{
    resume = new QPushButton(QIcon("../icons/resume.png"), "", this);
    pause  = new QPushButton(QIcon("../icons/pause.png"), "", this);
    done   = new QPushButton(QIcon("../icons/done.png"), "", this);

    resume->setIconSize(QSize(30, 30));
    pause->setIconSize(QSize(30, 30));
    done->setIconSize(QSize(30, 30));

    connect(resume, &QPushButton::clicked, this, &TaskWidget::onResumeButtonClicked);
    connect(pause, &QPushButton::clicked, this, &TaskWidget::onPauseButtonClicked);
    connect(done, &QPushButton::clicked, this, &TaskWidget::onDoneButtonClicked);
}

void TaskWidget::prepareWidgets()
{
    name          = new QLabel(this);
    deadline_date = new QLabel(this);

    name->setTextFormat(Qt::RichText);
    name->setIndent(10);
    deadline_date->setTextFormat(Qt::RichText);
    deadline_date->setStyleSheet("margin-right: 10px;");

    if (isDescriptionExists)
        prepareDescription();
}

void TaskWidget::prepareDescription()
{
    description = new QLabel(this);
    line        = new QWidget(this);
    description->setWordWrap(true);
    description->setIndent(10);
    description->setStyleSheet("margin-right: 10px;");
    line->setFixedHeight(2);
    line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    line->setStyleSheet(QString("margin-right: 10px; background-color: #000000;"));
}

void TaskWidget::formatDescription()
{
    QString descriptionStr = dbTaskController->getTask(task_id).m_description;
    QString descriptionRes = "Description: " + descriptionStr.left(250) + (descriptionStr.size() > 250 ? "..." : "");
    description->setText(descriptionRes);

    vLayoutTask->addWidget(line);
    vLayoutTask->addWidget(description);
}

void TaskWidget::removeDescription()
{
    vLayoutTask->removeWidget(description);
    vLayoutTask->removeWidget(line);

    delete description;
    delete line;
}

void TaskWidget::prepareLayouts()
{
    hLayout        = new QHBoxLayout;
    vLayoutTask    = new QVBoxLayout;
    vLayoutButtons = new QVBoxLayout;
    mainLayout     = new QHBoxLayout(this);

    hLayout->setSpacing(0);
    vLayoutTask->setSpacing(0);
    vLayoutButtons->setSpacing(0);
    mainLayout->setSpacing(10);
}

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
        setStyleSheet("background-color:  #FF855B;");
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

// select and then delete selected tasks
void TaskWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
        setSelected(!isSelected());
}

void TaskWidget::contextMenuEvent(QContextMenuEvent* event)
{
    QMenu myMenu;
    QAction action(QIcon("../icons/change_parameters.png"), "Change task parameters");
    myMenu.addAction(&action);

    QAction* selectedItem = myMenu.exec(event->globalPos());
    if (selectedItem)
    {
        // TODO:

        prepareDescription();
        formatDescription();

        // vLayoutTask->removeWidget(description);
        // vLayoutTask->removeWidget(line);

        // delete description;
        // delete line;
    }
}