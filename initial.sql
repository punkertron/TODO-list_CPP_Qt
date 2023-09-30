CREATE SCHEMA todo AUTHORIZATION todo_user;

CREATE TYPE e_task_status AS ENUM (
    'default',
    'in progress',
    'done'
);

CREATE TABLE todo.tasks (
    task_id INTEGER PRIMARY KEY,
    name TEXT NOT NULL,
    description TEXT,
    deadline_date DATE,
    task_status e_task_status DEFAULT 'default'
);

GRANT ALL ON ALL TABLES IN SCHEMA todo TO todo_user;