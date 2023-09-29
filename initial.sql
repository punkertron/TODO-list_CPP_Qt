CREATE SCHEMA todo AUTHORIZATION todo_user;

CREATE SEQUENCE todo_id_sequence;

CREATE TYPE e_task_status AS ENUM (
    'default',
    'in progress',
    'done'
);

CREATE TABLE todo.tasks (
    task_id INTEGER PRIMARY KEY DEFAULT nextval('todo_id_sequence'),
    name TEXT NOT NULL,
    description TEXT,
    deadline_date DATE,
    task_status e_task_status DEFAULT 'default'
);

GRANT ALL ON ALL TABLES IN SCHEMA todo TO todo_user;
GRANT USAGE ON SEQUENCE todo_id_sequence TO todo_user;