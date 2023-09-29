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
    dbTaskManager->addNewTask(task);

    addTaskToScrollArea(dbTaskManager->getFrontTask());

    // std::cout << task.m_name.toStdString() << std::endl;
    // std::cout << task.m_description.toStdString() << std::endl;
    // std::cout << task.m_deadline_date.toString().toStdString() << std::endl;
}

void MainWindow::addNewTask()
{
    AddTaskDialog dialog;
    Task task;

    connect(&dialog, &AddTaskDialog::userDataEntered, this, &MainWindow::onUserDataEntered);

    (void)dialog.exec();  // it doesn't matter what exec returns

    // int result = dialog.exec();
    // if (result == QDialog::Accepted)
    // {
    //     ;
    // }
    // if (result == QDialog::Rejected)
    // {
    //     std::cout << "Hello worodl" << std::endl;
    // }
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
    // fisrt row
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

    // second row
    QPushButton *filterButton = new QPushButton("Filter", parent);
    QPushButton *sortButton   = new QPushButton("Sort", parent);

    filter_sort_Layout = new QHBoxLayout;
    filter_sort_Layout->addWidget(filterButton);
    filter_sort_Layout->addWidget(sortButton);

    spacerItem = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);
    filter_sort_Layout->addSpacerItem(spacerItem);

    // TODO: add slots
    // QObject::connect(addTaskButton, SIGNAL(clicked()), this, SLOT(addNewTask()));
    connect(addTaskButton, &QPushButton::clicked, this, &MainWindow::addNewTask);

    connect(filterButton, &QPushButton::clicked, this, &MainWindow::filterTasks);
}

MainWindow::MainWindow(DbTaskManager *dbTaskManager, QWidget *parent) : QMainWindow(parent), dbTaskManager(dbTaskManager)
{
    setWindowTitle("TODO-list");
    setWindowIcon(QIcon("../icons/todo_logo.png"));
    setMinimumSize(QSize(730, 800));

    QWidget *widget = new QWidget(this);
    setCentralWidget(widget);

    setCommands(widget);  // add task and remove task, filter and sort

    scroll_Area = new QScrollArea(widget);  // for tasks
    scroll_Area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scroll_Area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QWidget *scrollWidget = new QWidget(this);
    scrollLayout          = new QVBoxLayout(scrollWidget);

    scroll_Area->setWidget(scrollWidget);
    scroll_Area->setWidgetResizable(true);

    QVBoxLayout *main_layout = new QVBoxLayout;

    main_layout->addLayout(commands_Layout);
    main_layout->addLayout(filter_sort_Layout);
    main_layout->addWidget(scroll_Area);

    widget->setLayout(main_layout);

    // scrollLayout->addWidget(new QPushButton(this));
}

void MainWindow::addTaskToScrollArea(const Task &task)
{
    TaskWidget *taskWidget = new TaskWidget(task, this);
    scrollLayout->insertWidget(0, taskWidget, 0, Qt::AlignTop);
    scrollLayout->addStretch();
}
