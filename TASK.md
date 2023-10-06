## TODO List Application with Qt.

GUI.
1. A list of current tasks should be displayed
2. There should be interfaces for managing tasks in the list according to commands
3. there should be an interface for filtering tasks by status, date range, name and description independently. The applied filter should be reset by button.

Commands: 
1. Adding a new task
  A task is an object with the following attributes
  - Name
  - Description
  - Date of event/task
  - State (Running or Completed)
2. mark the task as completed (or return it to its original state)
3. update task description, which allows you to update only the Task Name, Description and Date of the task
4. Delete task 

The list of tasks should be stored in permanent memory and loaded at application startup. Storage options can be different file, database, etc.

It is mandatory to use:
- C++17 language
- Qt6
- CMake 3.20+

---
[**Back to main page**](README.md)