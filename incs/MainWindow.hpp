#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QHBoxLayout>
#include <QMainWindow>
#include <QScrollArea>

#include "../incs/DbTaskController.hpp"
#include "../incs/Task.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

   private:
    DbTaskController *dbTaskController;

    QHBoxLayout *commands_Layout;
    QHBoxLayout *filter_sort_Layout;
    QSpacerItem *spacerItem;
    QScrollArea *scroll_Area;

    QVBoxLayout *scrollLayout;

    void setCommands(QWidget *parent);
    void addTaskToScrollArea(const Task &task);

   private slots:
    void addNewTask();
    void deleteTasks();
    void filterTasks();
    void onUserDataEntered(Task &task);

   public:
    MainWindow(DbTaskController *dbTaskController, QWidget *parent = nullptr);
    ~MainWindow() = default;
};

#endif  // MAIN_WINDOW_HPP