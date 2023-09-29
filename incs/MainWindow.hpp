#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QHBoxLayout>
#include <QMainWindow>
#include <QScrollArea>

#include "../incs/DbTaskManager.hpp"
#include "../incs/Task.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

   private:
    DbTaskManager *dbTaskManager;

    QHBoxLayout *commands_Layout;
    QHBoxLayout *filter_sort_Layout;
    QSpacerItem *spacerItem;
    QScrollArea *scroll_Area;

    QVBoxLayout *scrollLayout;

    void setCommands(QWidget *parent);
    void addTaskToScrollArea(const Task &task);

   private slots:
    void addNewTask();
    void filterTasks();
    void onUserDataEntered(Task &task);

   public:
    MainWindow(DbTaskManager *dbTaskManager, QWidget *parent = nullptr);
    ~MainWindow() = default;
};

#endif  // MAIN_WINDOW_HPP