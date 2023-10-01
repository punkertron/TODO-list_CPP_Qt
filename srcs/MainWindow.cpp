#include "../incs/MainWindow.hpp"

#include <QMenuBar>
#include <QMessageBox>

#include "../incs/AddTaskDialog.hpp"
#include "../incs/FilterDialog.hpp"
#include "../incs/Task.hpp"
#include "../incs/TaskWidgwet.hpp"

MainWindow::MainWindow(DbTaskController *dbTaskController, QWidget *parent) :
    QMainWindow(parent), m_dbTaskController(dbTaskController)
{
    setWindowTitle("TODO-list");
    setWindowIcon(QIcon("./icons/todo_logo.png"));
    setFixedSize(QSize(770, 800));  // Fixed?

    QWidget *widget = new QWidget(this);
    setCentralWidget(widget);

    setCommands();  // add task and remove task, filter and sort

    setScrollArea();

    QVBoxLayout *vMainLayout = new QVBoxLayout;

    vMainLayout->addLayout(m_hCommandsLayout);
    vMainLayout->addLayout(m_hFilterSortLayout);
    vMainLayout->addWidget(m_scrollArea);

    widget->setLayout(vMainLayout);

    // TODO:
    // QMenuBar *menuBar = new QMenuBar(this);
    // auto m_pSettings  = new QMenu(this);
    // menuBar->addMenu(m_pSettings);
    // m_pSettings->setTitle("Settings");
    // setMenuBar(menuBar);

    showTaskFromDb();
}

void MainWindow::onAddNewTask(Task &task)
{
    m_dbTaskController->addNewTask(task);
    m_dbTaskController->setFilterVisible(m_dbTaskController->getLastTaskId());

    if (m_dbTaskController->getLastTask().m_isVisible)
        addTaskToScrollArea(m_dbTaskController->getLastTaskId());
}

void MainWindow::setFilterView()
{
    m_dbTaskController->setFilterParams(m_filterParams);
    m_dbTaskController->setFilterVisibleAll();
    deleteAllTasks();
    showTaskFromDb();
}

void MainWindow::onFilterTasks(FilterParams &newFilterParams)
{
    m_filterParams = newFilterParams;
    setFilterView();

    FilterParams defaultFilter;
    if (defaultFilter.isEqual(m_filterParams))
    {
        m_isFiltered = false;
        removeDefaultFilterButton();
    }
    else
    {
        if (!m_isFiltered)
            createDefaultFilterButton();
        m_isFiltered = true;
    }
}

void MainWindow::createDefaultFilterButton()
{
    m_defaultFilter = new QPushButton("Reset filters", this);
    m_hFilterSortLayout->addWidget(m_defaultFilter, 1, Qt::AlignLeft);
    m_defaultFilter->setStyleSheet("background-color: #00E6E6");

    connect(m_defaultFilter, &QPushButton::clicked, this, &MainWindow::onDefaultFilterClicked);
}

void MainWindow::onDefaultFilterClicked()
{
    m_filterParams = FilterParams();
    setFilterView();
    m_isFiltered = false;
    removeDefaultFilterButton();
}

void MainWindow::removeDefaultFilterButton()
{
    QLayoutItem *item = m_hFilterSortLayout->layout()->takeAt(3);
    delete item->widget();
    delete item;
}

void MainWindow::addNewTask()
{
    AddTaskDialog dialog;
    Task task;

    connect(&dialog, &AddTaskDialog::userDataEntered, this, &MainWindow::onAddNewTask);

    (void)dialog.exec();  // it doesn't matter what exec returns
}

void MainWindow::filterTasks()
{
    FilterDialog dialog(&m_filterParams);

    connect(&dialog, &FilterDialog::userDataEntered, this, &MainWindow::onFilterTasks);

    (void)dialog.exec();
}

void MainWindow::setCommands()
{
    // fisrt row. Add task and Delete it
    QPushButton *addTaskButton = new QPushButton(this);
    addTaskButton->setIcon(QIcon("./icons/add_task.png"));
    addTaskButton->setFixedSize(QSize(50, 50));
    addTaskButton->setIconSize(QSize(40, 40));

    QPushButton *deleteTask = new QPushButton(this);
    deleteTask->setIcon(QIcon("./icons/remove_task.png"));
    deleteTask->setFixedSize(QSize(50, 50));
    deleteTask->setIconSize(QSize(40, 40));

    m_hCommandsLayout = new QHBoxLayout;
    m_hCommandsLayout->addWidget(addTaskButton, 0, Qt::AlignLeft);
    m_hCommandsLayout->addWidget(deleteTask, 1, Qt::AlignLeft);

    // second row. Filter and Sorting
    QPushButton *filterButton = new QPushButton("Filter", this);
    QPushButton *sortButton   = new QPushButton("Sort", this);

    m_hFilterSortLayout = new QHBoxLayout;
    m_hFilterSortLayout->addWidget(filterButton);
    m_hFilterSortLayout->addWidget(sortButton);
    m_hFilterSortLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));

    // QObject::connect(addTaskButton, SIGNAL(clicked()), this, SLOT(addNewTask()));
    connect(addTaskButton, &QPushButton::clicked, this, &MainWindow::addNewTask);
    connect(deleteTask, &QPushButton::clicked, this, &MainWindow::deleteSelectedTasks);
    connect(filterButton, &QPushButton::clicked, this, &MainWindow::filterTasks);
}

void MainWindow::deleteAllTasks()
{
    QLayoutItem *item;
    while ((item = m_vScrollLayout->layout()->takeAt(0)) != nullptr)
    {
        delete item->widget();
        delete item;
    }
}

void MainWindow::deleteSelectedTasks()
{
    for (int i = 0; i < m_vScrollLayout->count(); ++i)
    {
        QWidget *widget = m_vScrollLayout->layout()->itemAt(i)->widget();

        TaskWidget *taskWidget = qobject_cast<TaskWidget *>(widget);
        if (taskWidget && taskWidget->isSelected())
        {
            m_dbTaskController->deleteTask(taskWidget->getTaskId());

            // FIXME: Should we delete stretch? In addTaskToScrollArea we addStretch()
            delete m_vScrollLayout->itemAt(i)->widget();
            delete m_vScrollLayout->itemAt(i)->layout();

            i = -1;  // to start from beginning
        }
    }
    // m_vScrollLayout->update();
}

void MainWindow::setScrollArea()
{
    m_scrollArea = new QScrollArea(this);  // for tasks
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QWidget *scrollWidget = new QWidget(this);
    m_vScrollLayout       = new QVBoxLayout(scrollWidget);
    m_vScrollLayout->setContentsMargins(10, 10, 10, 10);

    m_scrollArea->setWidget(scrollWidget);
    m_scrollArea->setWidgetResizable(true);
}

void MainWindow::showTaskFromDb()
{
    for (const auto &[key, value] : m_dbTaskController->getMapTask().toStdMap())
    {
        if (value.m_isVisible)
            addTaskToScrollArea(key);
    }
}

void MainWindow::addTaskToScrollArea(int32_t task_id)
{
    TaskWidget *taskWidget = new TaskWidget(task_id, m_dbTaskController /*, this*/);
    m_vScrollLayout->insertWidget(0, taskWidget, 0, Qt::AlignTop);
    m_vScrollLayout->addStretch();
}
