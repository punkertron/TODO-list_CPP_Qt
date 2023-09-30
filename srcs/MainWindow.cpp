#include "../incs/MainWindow.hpp"

#include <QDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QScrollArea>
#include <iostream>

#include "../incs/AddTaskDialog.hpp"
#include "../incs/FilterDialog.hpp"
#include "../incs/Task.hpp"
#include "../incs/TaskWidgwet.hpp"

void MainWindow::onAddNewTask(Task &task)
{
    dbTaskController->addNewTask(task);
    dbTaskController->setFilterVisible(dbTaskController->getLastTaskId());

    if (dbTaskController->getLastTask().isVisible)
        addTaskToScrollArea(dbTaskController->getLastTaskId());
}

void MainWindow::setFilterView()
{
    dbTaskController->setFilterParams(filterParams);
    dbTaskController->setFilterVisibleAll();
    deleteAllTasks();
    showTaskFromDb();
}

void MainWindow::onFilterTasks(FilterParams &newFilterParams)
{
    filterParams = newFilterParams;
    setFilterView();

    FilterParams defaultFilter;
    if (defaultFilter.isEqual(filterParams))
    {
        isFiltered = false;
        removeDefaultFilterButton();
    }
    else
    {
        if (!isFiltered)
            createDefaultFilterButton();
        isFiltered = true;
    }
}

void MainWindow::createDefaultFilterButton()
{
    defaultFilter = new QPushButton("Reset filters", this);
    filter_sort_Layout->addWidget(defaultFilter, 1, Qt::AlignLeft);
    defaultFilter->setStyleSheet("background-color: #00E6E6");

    connect(defaultFilter, &QPushButton::clicked, this, &MainWindow::onDefaultFilterClicked);
}

void MainWindow::onDefaultFilterClicked()
{
    filterParams = FilterParams();
    setFilterView();
    isFiltered = false;
    removeDefaultFilterButton();
}

void MainWindow::removeDefaultFilterButton()
{
    QLayoutItem *item = filter_sort_Layout->layout()->takeAt(3);
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
    FilterDialog dialog(&filterParams);

    connect(&dialog, &FilterDialog::userDataEntered, this, &MainWindow::onFilterTasks);

    (void)dialog.exec();
}

void MainWindow::setCommands()
{
    // fisrt row. Add task and Delete it
    QPushButton *addTaskButton = new QPushButton(this);
    addTaskButton->setIcon(QIcon("../icons/add_task.png"));
    addTaskButton->setFixedSize(QSize(50, 50));
    addTaskButton->setIconSize(QSize(40, 40));

    QPushButton *deleteTask = new QPushButton(this);
    deleteTask->setIcon(QIcon("../icons/remove_task.png"));
    deleteTask->setFixedSize(QSize(50, 50));
    deleteTask->setIconSize(QSize(40, 40));

    commands_Layout = new QHBoxLayout;
    commands_Layout->addWidget(addTaskButton, 0, Qt::AlignLeft);
    commands_Layout->addWidget(deleteTask, 1, Qt::AlignLeft);

    // second row. Filter and Sorting
    QPushButton *filterButton = new QPushButton("Filter", this);
    QPushButton *sortButton   = new QPushButton("Sort", this);

    filter_sort_Layout = new QHBoxLayout;
    filter_sort_Layout->addWidget(filterButton);
    filter_sort_Layout->addWidget(sortButton);

    spacerItem = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);
    filter_sort_Layout->addSpacerItem(spacerItem);

    // QObject::connect(addTaskButton, SIGNAL(clicked()), this, SLOT(addNewTask()));
    connect(addTaskButton, &QPushButton::clicked, this, &MainWindow::addNewTask);
    connect(deleteTask, &QPushButton::clicked, this, &MainWindow::deleteTasks);
    connect(filterButton, &QPushButton::clicked, this, &MainWindow::filterTasks);
}

void MainWindow::deleteAllTasks()
{
    QLayoutItem *item;
    while ((item = scrollLayout->layout()->takeAt(0)) != nullptr)
    {
        delete item->widget();
        delete item;
    }
}

void MainWindow::deleteTasks()
{
    for (int i = 0; i < scrollLayout->count(); ++i)
    {
        QWidget *widget = scrollLayout->layout()->itemAt(i)->widget();

        TaskWidget *taskWidget = qobject_cast<TaskWidget *>(widget);
        if (taskWidget && taskWidget->isSelected())
        {
            dbTaskController->deleteTask(taskWidget->getTaskId());

            // FIXME: Should we delete stretch? In addTaskToScrollArea we addStretch()
            delete scrollLayout->itemAt(i)->widget();
            delete scrollLayout->itemAt(i)->layout();

            i = -1;  // to start from beginning
        }
    }
    // scrollLayout->update();
}

MainWindow::MainWindow(DbTaskController *dbTaskController, QWidget *parent) :
    QMainWindow(parent), dbTaskController(dbTaskController)
{
    setWindowTitle("TODO-list");
    setWindowIcon(QIcon("../icons/todo_logo.png"));
    setFixedSize(QSize(770, 800));  // Fixed?

    QWidget *widget = new QWidget(this);
    setCentralWidget(widget);

    setCommands();  // add task and remove task, filter and sort

    setScrollArea();

    QVBoxLayout *main_layout = new QVBoxLayout;

    main_layout->addLayout(commands_Layout);
    main_layout->addLayout(filter_sort_Layout);
    main_layout->addWidget(scroll_Area);

    widget->setLayout(main_layout);

    showTaskFromDb();
}

void MainWindow::setScrollArea()
{
    scroll_Area = new QScrollArea(this);  // for tasks
    scroll_Area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scroll_Area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QWidget *scrollWidget = new QWidget(this);
    scrollLayout          = new QVBoxLayout(scrollWidget);
    scrollLayout->setContentsMargins(10, 10, 10, 10);

    scroll_Area->setWidget(scrollWidget);
    scroll_Area->setWidgetResizable(true);
}

void MainWindow::showTaskFromDb()
{
    for (const auto &[key, value] : dbTaskController->getMapTask().toStdMap())
    {
        if (value.isVisible)
            addTaskToScrollArea(key);
    }
}

void MainWindow::addTaskToScrollArea(int32_t task_id)
{
    TaskWidget *taskWidget = new TaskWidget(task_id, dbTaskController /*, this*/);
    scrollLayout->insertWidget(0, taskWidget, 0, Qt::AlignTop);
    scrollLayout->addStretch();
}
