#!/bin/bash

DB_USER="postgres"
DB_PASSWORD="your_password_here"

TODO_DB_NAME="todo_db"
TODO_USER="todo_user"
TODO_USER_PASSWORD="todo_user_password"

SQL_SCRIPT="initial.sql"


sudo -u $DB_USER psql -q -c "CREATE USER $TODO_USER WITH PASSWORD '$TODO_USER';"
sudo -u $DB_USER psql -q -c "CREATE DATABASE $TODO_DB_NAME;"
sudo -u $DB_USER psql -q -c "GRANT ALL PRIVILEGES ON DATABASE $TODO_DB_NAME TO $TODO_USER;"

sudo -u $DB_USER psql -q -d $TODO_DB_NAME -f $SQL_SCRIPT

echo "The database is prepared! Now you can use the TODO app."