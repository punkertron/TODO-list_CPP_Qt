#include "MainWindow.hpp"

#include <QDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QScrollArea>

// #include <iostream>

#include "AddTaskDialog.hpp"
#include "FilterDialog.hpp"

void MainWindow::addNewTask()
{
    // QMessageBox::information(nullptr, "Action Triggered", "MyAction was triggered!");
    AddTaskDialog d;
    int result = d.exec();
}

void MainWindow::filterTasks()
{
    // QMessageBox::information(nullptr, "Action Triggered", "MyAction was triggered!");
    FilterDialog d;
    int result = d.exec();
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

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("TODO-list");
    setWindowIcon(QIcon("../icons/todo_logo.png"));
    setMinimumSize(QSize(600, 700));

    QWidget *widget = new QWidget(this);
    setCentralWidget(widget);

    setCommands(widget);  // add task and remove task, filter and sort

    QScrollArea *scroll_Area = new QScrollArea(widget);  // for tasks
    scroll_Area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scroll_Area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    QVBoxLayout *main_layout = new QVBoxLayout;
    main_layout->addLayout(commands_Layout);
    main_layout->addLayout(filter_sort_Layout);
    main_layout->addWidget(scroll_Area);

    widget->setLayout(main_layout);
}
