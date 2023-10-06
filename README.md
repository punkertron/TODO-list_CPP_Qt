# TODO List Application with Qt

Adding, modifying, deleting tasks:
![todo-part1.gif](assets/todo_part1.gif)

<br>

Filtering, sorting. Restarting the application (and saving tasks):
![todo-part2.gif](assets/todo_part2.gif)

---

## Table of Contents

1. [Project Idea](#project-idea)
2. [Installation](#installation)
3. [Testing](#testing)
4. [Deleting tasks from DB](#deleting-tasks-from-db)
5. [TODO](#todo)

---

### Project Idea
Need to implement a small TODO-list application using Qt6. User should be able to add/delete tasks, change their status and filter them. Full description of the task is available [**here**](TASK.md).

To ensure that tasks are not deleted when the application is closed, I add them to a PostgreSQL database.

From the bonuses:
- Sorting tasks.
- Checking the "In Progress", "Paused" and "Done" boxes.
- Task highlighting, including overdue tasks.
- Ability to delete several tasks at once.

---

### Installation
The development was done on **Debian 12** using only standard packages.

**Important**: the `clang-format` command is automatically called first every time a project is built. It can be disabled by removing lines 44-50 and 54 from [CMakeLists.txt](CMakeLists.txt).

First you need to prepare the database for work (otherwise the programme will terminate with an error):
```bash
bash init_db.sh
```
And then build the project with a Makefile that already runs cmake:
```bash
make
```
Run the application from the root folder of the project:
```bash
./TODO-list
```
---

The programme has also been tested to run on **Ubuntu**. This will require:
- Firstly, install the required packages:

```bash
sudo apt install g++ make cmake postgresql qt6-base-dev libqt6sql6-psql clang-format libgl1-mesa-dev libglvnd-dev
```
- Second, you may need to downgrade `cmake_minimum_required`. And also in [CMakeLists.txt](CMakeLists.txt) replace `qt_standard_project_project_setup()` with:
```bash
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
```
- Thirdly, there may be access problems with the postgres user. In this case, execution of `bash init_db.sh` will be accompanied by strange messages about Permission denied. Then you should run each command from the [initial.sql](initial.sql) file line by line:
```bash
sudo -u postgres psql -q -d todo_db -c ¨CREATE SCHEMA todo AUTHORIZATION todo_user;¨
...
sudo -u postgres psql -q -d todo_db -c ¨GRANT ALL ON ALL TABLES IN SCHEMA todo TO todo_user;¨
```

Now the app will launch for sure!

---

### Testing
- It is possible to build an application with `-fsanitize=address -fsanitize=leak -fsanitize=undefined` :
```bash
make debug
```
A programme is created with the same name - `TODO-list`.

<br>

- Tests using **QtTest** are written for the project (namely for the part of the project that is responsible for interacting with the database, filtering and sorting tasks - **DbTaskController**). The tests are located in the [tests](tests) folder. Build and run the tests:

```bash
make tests && ./TODO-tests
```

Output:

![test_output](assets/test_output.png)

---

### Deleting tasks from DB
All database objects used in the application can be deleted with the following command:
```bash
bash clear_db.sh
```

---

### TODO
What could be added and what could be improved?
- Write more tests.
- Work out filtering and sorting of tasks. The current algorithm doesn't seem to be the most efficient (especially sorting, when there is a complete deletion and creation of tasks at each operation).
- Add translation to other languages.
- Add support for other OS.
- Remove the incs folder.
- Move visual design to ui files (to separate design from logic).
- Move icons to resource files.