#include "../incs/MainWindow.hpp"

#include <QDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QScrollArea>

// #include <iostream>

#include <iostream>

#include "../incs/AddTaskDialog.hpp"
#include "../incs/FilterDialog.hpp"
#include "../incs/Task.hpp"
#include "../incs/TaskWidgwet.hpp"

void MainWindow::onUserDataEntered(Task &task)
{
    dbTaskController->addNewTask(task);

    addTaskToScrollArea(dbTaskController->getLastTask());
}

void MainWindow::addNewTask()
{
    AddTaskDialog dialog;
    Task task;

    connect(&dialog, &AddTaskDialog::userDataEntered, this, &MainWindow::onUserDataEntered);

    (void)dialog.exec();  // it doesn't matter what exec returns
}

void MainWindow::filterTasks()
{
    // QMessageBox::information(nullptr, "Action Triggered", "MyAction was triggered!");
    FilterDialog d;
    int result = d.exec();
    (void)result;
}

void MainWindow::setCommands(QWidget *parent)
{
    // fisrt row. Add task and Delete it
    QPushButton *addTaskButton = new QPushButton(parent);
    addTaskButton->setIcon(QIcon("../icons/add_task.png"));
    addTaskButton->setFixedSize(QSize(50, 50));
    addTaskButton->setIconSize(QSize(40, 40));

    QPushButton *deleteTask = new QPushButton(parent);
    deleteTask->setIcon(QIcon("../icons/remove_task.png"));
    deleteTask->setFixedSize(QSize(50, 50));
    deleteTask->setIconSize(QSize(40, 40));

    commands_Layout = new QHBoxLayout;
    commands_Layout->addWidget(addTaskButton, 0, Qt::AlignLeft);
    commands_Layout->addWidget(deleteTask, 1, Qt::AlignLeft);

    // second row. Filter and Sorting
    QPushButton *filterButton = new QPushButton("Filter", parent);
    QPushButton *sortButton   = new QPushButton("Sort", parent);

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

    setCommands(widget);  // add task and remove task, filter and sort

    scroll_Area = new QScrollArea(widget);  // for tasks
    scroll_Area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scroll_Area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QWidget *scrollWidget = new QWidget(this);
    scrollLayout          = new QVBoxLayout(scrollWidget);
    scrollLayout->setContentsMargins(10, 10, 10, 10);

    scroll_Area->setWidget(scrollWidget);
    scroll_Area->setWidgetResizable(true);

    QVBoxLayout *main_layout = new QVBoxLayout;

    main_layout->addLayout(commands_Layout);
    main_layout->addLayout(filter_sort_Layout);
    main_layout->addWidget(scroll_Area);

    widget->setLayout(main_layout);

    showTaskFromDb();
}

void MainWindow::showTaskFromDb()
{
    for (const auto &[key, value] : dbTaskController->getMapTask().toStdMap())
    {
        addTaskToScrollArea(key);
    }
}

void MainWindow::addTaskToScrollArea(int32_t task_id)
{
    TaskWidget *taskWidget = new TaskWidget(task_id, dbTaskController /*, this*/);
    scrollLayout->insertWidget(0, taskWidget, 0, Qt::AlignTop);
    scrollLayout->addStretch();
}
