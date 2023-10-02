#include "../incs/MainWindow.hpp"

#include <QMenuBar>
#include <QMessageBox>

#include "../incs/AddTaskDialog.hpp"
#include "../incs/FilterDialog.hpp"
#include "../incs/SortDialog.hpp"
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

    setMenu();
    showAllTasks();
}

void MainWindow::setMenu()
{
    QMenuBar *menuBar = new QMenuBar(this);

    QMenu *settingsMenu    = menuBar->addMenu("Settings");
    QAction *settingAction = new QAction(QIcon("./icons/smile.png"), "No settings :)", this);
    settingsMenu->addAction(settingAction);
    connect(settingAction, &QAction::triggered, this, &MainWindow::showSettingsDialog);

    QMenu *aboutMenu     = menuBar->addMenu("Help");
    QAction *aboutAction = new QAction(QIcon("./icons/about.png"), "About", this);
    aboutMenu->addAction(aboutAction);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAboutDialog);

    setMenuBar(menuBar);
}

void MainWindow::showSettingsDialog()
{
    QString warningText = "<br>I told you there's no settings!";

    QMessageBox::warning(this, "Warning!!!", warningText);
}

void MainWindow::showAboutDialog()
{
    QString aboutText = "<br>This is the best TODO-list in the world!<br><br>";
    aboutText += "Use and Enjoy!<br>";

    QMessageBox::about(this, "About", aboutText);
}

void MainWindow::onAddNewTask(Task &task)
{
    m_dbTaskController->addNewTask(task);
    m_dbTaskController->setFilterVisible(m_dbTaskController->getLastTaskId());

    if (m_isSorted)
    {
        deleteAllTasks();
        showAllTasks();
    }
    if (m_dbTaskController->getLastTask().m_isVisible)
        addTaskToScrollArea(m_dbTaskController->getLastTaskId());
}

void MainWindow::setFilterView()
{
    m_dbTaskController->setFilterParams(m_filterParams);
    m_dbTaskController->setFilterVisibleAll();
    deleteAllTasks();
    showAllTasks();
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
        {
            m_isFiltered = true;
            createDefaultFilterButton();
        }
    }
}

void MainWindow::createDefaultFilterButton()
{
    m_defaultFilter = new QPushButton("Reset filters", this);
    m_defaultFilter->setStyleSheet("background-color: #00E6E6");
    m_hFilterSortLayout->insertWidget(2, m_defaultFilter, 0, Qt::AlignLeft);
    connect(m_defaultFilter, &QPushButton::clicked, this, &MainWindow::onDefaultFilterClicked);
}

void MainWindow::createDefaultSortButton()
{
    m_defaultSort = new QPushButton("Reset sort", this);
    if (!m_isFiltered)
        m_hFilterSortLayout->insertWidget(2, m_defaultSort, 0, Qt::AlignLeft);
    else
        m_hFilterSortLayout->insertWidget(3, m_defaultSort, 0, Qt::AlignLeft);
    m_defaultSort->setStyleSheet("background-color: #00E6E6");

    connect(m_defaultSort, &QPushButton::clicked, this, &MainWindow::onDefaultSortClicked);
}

void MainWindow::onDefaultFilterClicked()
{
    m_filterParams = FilterParams();
    setFilterView();
    m_isFiltered = false;
    removeDefaultFilterButton();
}

void MainWindow::onDefaultSortClicked()
{
    m_sortOpt  = sortOption::Default;
    m_isSorted = false;
    showSortedFilteredTasks();
    removeDefaultSortButton();
}

void MainWindow::removeDefaultFilterButton()
{
    QLayoutItem *item = m_hFilterSortLayout->layout()->takeAt(2);
    delete item->widget();
    delete item;
}

void MainWindow::removeDefaultSortButton()
{
    QLayoutItem *item;

    if (!m_isFiltered)
        item = m_hFilterSortLayout->layout()->takeAt(2);
    else
        item = m_hFilterSortLayout->layout()->takeAt(3);
    delete item->widget();
    delete item;
}

void MainWindow::addNewTask()
{
    AddTaskDialog dialog;

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
    connect(sortButton, &QPushButton::clicked, this, &MainWindow::sortTasks);
}

void MainWindow::showSortedFilteredTasks()
{
    deleteAllTasks();
    showAllTasks();
}

void MainWindow::sortTasks()
{
    SortDialog dialog(m_sortOpt);
    int result = dialog.exec();

    if (result == QDialog::Accepted)
    {
        m_sortOpt = dialog.getSortOption();
        if (!m_isSorted && m_sortOpt == sortOption::Default)
            return;

        if (m_isSorted)
        {
            if (m_sortOpt == sortOption::Default)
            {
                m_isSorted = false;
                removeDefaultSortButton();
                showSortedFilteredTasks();
            }
            else
            {
                showSortedFilteredTasks();
            }
        }
        else
        {
            m_isSorted = true;
            createDefaultSortButton();
            showSortedFilteredTasks();
        }
    }
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

void MainWindow::showAllTasks()
{
    if (!m_isSorted)
    {
        for (const auto &[key, value] : m_dbTaskController->getMapTask().toStdMap())
        {
            if (value.m_isVisible)
                addTaskToScrollArea(key);
        }
    }
    else
    {
        for (const auto &[key, value] : m_dbTaskController->getSortedTasks(m_sortOpt))
        {
            if (value.m_isVisible)
                addTaskToScrollArea(key);
        }
    }
}

void MainWindow::addTaskToScrollArea(int32_t task_id)
{
    TaskWidget *taskWidget = new TaskWidget(task_id, m_dbTaskController /*, this */);
    m_vScrollLayout->insertWidget(0, taskWidget, 0, Qt::AlignTop);
    m_vScrollLayout->addStretch();
    connect(taskWidget, &TaskWidget::taskParamsChanged, this, &MainWindow::sortFilterAfterChangeTaskParams);
}

void MainWindow::sortFilterAfterChangeTaskParams(int32_t task_id)
{
    if (m_isSorted || m_isFiltered)
    {
        if (m_isFiltered)
            m_dbTaskController->setFilterVisible(task_id);
        showSortedFilteredTasks();
    }
}
