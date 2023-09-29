#!/bin/bash

DB_USER="postgres"

TODO_DB_NAME="todo_db"
TODO_USER="todo_user"

TODO_SCHEMA="todo"
TODO_SEQUENCE="todo_id_sequence"


sudo -u $DB_USER psql -q -d $TODO_DB_NAME -c "DROP SCHEMA $TODO_SCHEMA CASCADE;" &> /dev/null
sudo -u $DB_USER psql -q -d $TODO_DB_NAME -c "DROP SEQUENCE $TODO_SEQUENCE;"
sudo -u $DB_USER psql -q -c "DROP DATABASE $TODO_DB_NAME;"
sudo -u $DB_USER psql -q -c "DROP USER $TODO_USER;"

echo "The TODO_APP database has been cleaned!"