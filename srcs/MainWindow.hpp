#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QHBoxLayout>
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

   private:
    QHBoxLayout *commands_Layout;
    QHBoxLayout *filter_sort_Layout;
    QSpacerItem *spacerItem;

    void setCommands(QWidget *parent);

   private slots:
    void addNewTask();
    void filterTasks();

   public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;
};

#endif  // MAIN_WINDOW_HPP