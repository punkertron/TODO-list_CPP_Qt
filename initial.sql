CREATE SCHEMA todo AUTHORIZATION todo_user;

CREATE TYPE enum_task_status AS ENUM ('default', 'in progress', 'done');

CREATE TABLE todo.tasks (
    task_id SERIAL PRIMARY KEY,
    name TEXT NOT NULL,
    description VARCHAR(64) DEFAULT '',
    deadline_date DATE,
    task_status enum_task_status DEFAULT 'default'
);