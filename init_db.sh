#!/bin/bash

DB_USER="postgres"

TODO_DB_NAME="todo_db"
TODO_USER="todo_user"
TODO_USER_PASSWORD="todo_user_password"

SQL_SCRIPT="initial.sql"


sudo -u $DB_USER psql -q -c "CREATE USER $TODO_USER WITH PASSWORD '$TODO_USER_PASSWORD';"
sudo -u $DB_USER psql -q -c "CREATE DATABASE $TODO_DB_NAME;"

sudo -u $DB_USER psql -q -d $TODO_DB_NAME -f $SQL_SCRIPT

sudo -u $DB_USER psql -q -c "GRANT ALL PRIVILEGES ON DATABASE $TODO_DB_NAME TO $TODO_USER;"

echo "The database is prepared! Now you can use the TODO-list app."