#include "../incs/ChangeParametersDialog.hpp"
#include "../incs/TaskWidgwet.hpp"

TaskWidget::TaskWidget(int32_t task_id, DbTaskController* dbTaskController, QWidget* parent) :
    QWidget(parent),
    m_dbTaskController(dbTaskController),
    m_task_id(task_id),
    m_isDescriptionExists(m_dbTaskController->getTask(task_id).m_description.size())
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
    m_hLayoutNameDate->addWidget(m_name, 1);
    m_hLayoutNameDate->addWidget(m_deadline_date, 0, Qt::AlignRight);

    m_vLayoutTask->addLayout(m_hLayoutNameDate);

    if (m_isDescriptionExists)
    {
        formatDescription();
        formatDescriptionLayout();
    }

    m_vLayoutButtons->addWidget(m_resume);
    m_vLayoutButtons->addWidget(m_pause);
    m_vLayoutButtons->addWidget(m_done);

    m_hMainLayout->addLayout(m_vLayoutButtons);
    m_hMainLayout->addLayout(m_vLayoutTask);
}

void TaskWidget::formatWidgets()
{
    QString nameStr = m_dbTaskController->getTask(m_task_id).m_name;
    QString nameRes = QString("Task: <b>%1</b>").arg(nameStr.left(40) + (nameStr.size() > 40 ? "..." : ""));
    m_name->setText(nameRes);

    QDate date          = m_dbTaskController->getTask(m_task_id).m_deadline_date;
    QString deadlineStr = QString("Deadline: <b>%1</b>").arg(date.toString("d MMM, dddd"));
    m_deadline_date->setText(deadlineStr);
}

void TaskWidget::setButtons()
{
    m_resume = new QPushButton(QIcon("./icons/resume.png"), "", this);
    m_pause  = new QPushButton(QIcon("./icons/pause.png"), "", this);
    m_done   = new QPushButton(QIcon("./icons/done.png"), "", this);

    m_resume->setIconSize(QSize(30, 30));
    m_pause->setIconSize(QSize(30, 30));
    m_done->setIconSize(QSize(30, 30));

    connect(m_resume, &QPushButton::clicked, this, &TaskWidget::onResumeButtonClicked);
    connect(m_pause, &QPushButton::clicked, this, &TaskWidget::onPauseButtonClicked);
    connect(m_done, &QPushButton::clicked, this, &TaskWidget::onDoneButtonClicked);
}

void TaskWidget::prepareWidgets()
{
    m_name          = new QLabel(this);
    m_deadline_date = new QLabel(this);

    m_name->setTextFormat(Qt::RichText);
    m_name->setIndent(10);
    m_deadline_date->setTextFormat(Qt::RichText);
    m_deadline_date->setStyleSheet("margin-right: 10px;");

    if (m_isDescriptionExists)
        prepareDescription();
}

void TaskWidget::prepareDescription()
{
    m_description = new QLabel(this);
    m_line        = new QWidget(this);
    m_description->setWordWrap(true);
    m_description->setIndent(10);
    m_description->setStyleSheet("margin-right: 10px;");
    m_line->setFixedHeight(2);
    m_line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_line->setStyleSheet(QString("margin-right: 10px; background-color: #000000;"));
}

void TaskWidget::formatDescription()
{
    QString descriptionStr = m_dbTaskController->getTask(m_task_id).m_description;
    QString descriptionRes = "Description: " + descriptionStr.left(250) + (descriptionStr.size() > 250 ? "..." : "");
    m_description->setText(descriptionRes);
}

void TaskWidget::formatDescriptionLayout()
{
    m_vLayoutTask->addWidget(m_line);
    m_vLayoutTask->addWidget(m_description);
}

void TaskWidget::removeDescription()
{
    m_vLayoutTask->removeWidget(m_description);
    m_vLayoutTask->removeWidget(m_line);

    delete m_description;
    delete m_line;
}

void TaskWidget::prepareLayouts()
{
    m_hLayoutNameDate = new QHBoxLayout;
    m_vLayoutTask     = new QVBoxLayout;
    m_vLayoutButtons  = new QVBoxLayout;
    m_hMainLayout     = new QHBoxLayout(this);

    m_hLayoutNameDate->setSpacing(0);
    m_vLayoutTask->setSpacing(0);
    m_vLayoutButtons->setSpacing(0);
    m_hMainLayout->setSpacing(10);
}

void TaskWidget::onResumeButtonClicked()
{
    const char* s = "in progress";
    m_dbTaskController->setStatus(m_task_id, s);
    fillColour();
    emit taskParamsChanged(m_task_id);
}

void TaskWidget::onPauseButtonClicked()
{
    const char* s = "default";
    m_dbTaskController->setStatus(m_task_id, s);
    fillColour();
    emit taskParamsChanged(m_task_id);
}

void TaskWidget::onDoneButtonClicked()
{
    const char* s = "done";
    m_dbTaskController->setStatus(m_task_id, s);
    fillColour();
    emit taskParamsChanged(m_task_id);
}

void TaskWidget::fillColour()
{
    QString statusStr = m_dbTaskController->getTask(m_task_id).m_task_status;
    QDate date        = m_dbTaskController->getTask(m_task_id).m_deadline_date;

    if (statusStr == "default" && date < QDate::currentDate())
        setStyleSheet("background-color:  #FF855B;");
    else if (statusStr == "default")
        setStyleSheet("background-color: #FEFEFE;");
    else if (statusStr == "in progress")
        setStyleSheet("background-color: #FEF233;");
    else  // done
        setStyleSheet("background-color: #33FE39;");
}

// coloгrs the selected task
void TaskWidget::paintEvent(QPaintEvent* /*event*/)
{
    QPainter painter(this);
    if (m_selected)
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

// A lot of checks for the presence of a description
void TaskWidget::onUserDataEntered(Task& task)
{
    m_dbTaskController->setTask(m_task_id, task);

    formatWidgets();
    if (m_isDescriptionExists)
    {
        if (task.m_description.size() == 0)
        {
            removeDescription();
            m_isDescriptionExists = false;
        }
        else
            formatDescription();
    }
    else
    {
        if (task.m_description.size() != 0)
        {
            m_isDescriptionExists = true;
            prepareDescription();
            formatDescription();
            formatDescriptionLayout();
        }
    }
    fillColour();

    emit taskParamsChanged(m_task_id);
}

void TaskWidget::contextMenuEvent(QContextMenuEvent* event)
{
    QMenu myMenu;
    QAction action(QIcon("./icons/change_parameters.png"), "Change task parameters");
    myMenu.addAction(&action);

    QAction* selectedItem = myMenu.exec(event->globalPos());
    if (selectedItem)
    {
        ChangeParametersDialog dialog(m_dbTaskController->getTask(m_task_id));

        connect(&dialog, &ChangeParametersDialog::userDataEntered, this, &TaskWidget::onUserDataEntered);
        (void)dialog.exec();
    }
}
