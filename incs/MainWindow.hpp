#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QHBoxLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>

#include "../incs/DbTaskController.hpp"
#include "../incs/FilterParams.hpp"
#include "../incs/SortDialog.hpp"
#include "../incs/Task.hpp"

class MainWindow final : public QMainWindow
{
    Q_OBJECT

   private:
    DbTaskController *m_dbTaskController;

    FilterParams m_filterParams;
    bool m_isFiltered = false;

    sortOption m_sortOpt = sortOption::Default;
    bool m_isSorted      = false;

    QHBoxLayout *m_hCommandsLayout;
    QHBoxLayout *m_hFilterSortLayout;
    QScrollArea *m_scrollArea;
    QVBoxLayout *m_vScrollLayout;
    QPushButton *m_defaultFilter;
    QPushButton *m_defaultSort;

    void setCommands();
    void setScrollArea();
    void addTaskToScrollArea(int32_t task_id);
    void showAllTasks();
    void deleteAllTasks();
    void removeDefaultFilterButton();
    void createDefaultFilterButton();
    void createDefaultSortButton();
    void removeDefaultSortButton();
    void setMenu();
    void showSortedFilteredTasks();

   private slots:
    void addNewTask();
    void deleteSelectedTasks();
    void filterTasks();
    void onAddNewTask(Task &task);
    void onFilterTasks(FilterParams &filterParams);
    void onDefaultFilterClicked();
    void onDefaultSortClicked();
    void setFilterView();
    void showAboutDialog();
    void showSettingsDialog();
    void sortTasks();
    void sortFilterAfterChangeTaskParams(int32_t task_id);

   public:
    MainWindow()                                        = delete;
    ~MainWindow()                                       = default;
    MainWindow(const MainWindow & /*other*/)            = delete;
    MainWindow(MainWindow && /*other*/)                 = delete;
    MainWindow &operator=(const MainWindow & /*other*/) = delete;
    MainWindow &operator=(MainWindow && /*other*/)      = delete;

    MainWindow(DbTaskController *dbTaskController, QWidget *parent = nullptr);
};

#endif  // MAIN_WINDOW_HPP