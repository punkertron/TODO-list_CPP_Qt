#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QHBoxLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QScrollArea>

#include "../incs/DbTaskController.hpp"
#include "../incs/FilterParams.hpp"
#include "../incs/Task.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

   private:
    DbTaskController *dbTaskController;

    FilterParams filterParams;
    bool isFiltered = false;

    QHBoxLayout *commands_Layout;
    QHBoxLayout *filter_sort_Layout;
    QSpacerItem *spacerItem;
    QScrollArea *scroll_Area;
    QVBoxLayout *scrollLayout;
    QPushButton *defaultFilter;

    void setCommands();
    void setScrollArea();
    void addTaskToScrollArea(int32_t task_id);
    void showTaskFromDb();
    void deleteAllTasks();
    void removeDefaultFilterButton();
    void createDefaultFilterButton();

   private slots:
    void addNewTask();
    void deleteTasks();
    void filterTasks();
    void onAddNewTask(Task &task);
    void onFilterTasks(FilterParams &filterParams);
    void onDefaultFilterClicked();
    void setFilterView();

   public:
    MainWindow(DbTaskController *dbTaskController, QWidget *parent = nullptr);
    ~MainWindow() = default;
};

#endif  // MAIN_WINDOW_HPP