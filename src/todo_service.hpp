#include <stdio.h>
#include <iostream>
#include "db_service.hpp"

class TodoService
{
private:
    DbService &dbService;

public:
    TodoService(DbService &db) : dbService(db)
    {
    }

    void addTask(const char *task)
    {
        char sql[256];
        snprintf(sql, sizeof(sql), "INSERT INTO tasks (task, done) VALUES ('%s', 0);", task);
        dbService.execSQL(sql);
    }

    void removeTask(const int id)
    {
        char sql[256];
        snprintf(sql, sizeof(sql), "DELETE FROM tasks WHERE id = ('%d')", id);
        dbService.execSQL(sql);
    }

    void listTasks()
    {
        dbService.readDataStmt("tasks");
    }

    void markTaskDone(const int id, bool done)
    {
        char sql[256];
        snprintf(sql, sizeof(sql), "UPDATE tasks SET done = %d WHERE id = %d;", done ? 1 : 0, id);
        dbService.execSQL(sql);
    }

    void addTag(const char *tag, int taskId)
    {
        char sql[256];
        snprintf(sql, sizeof(sql), "UPDATE tasks SET tags = '%s' WHERE id = %d;", tag, taskId);
        dbService.execSQL(sql);
    }
    void removeTag(const int id)
    {
        char sql[256];
        snprintf(sql, sizeof(sql), "UPDATE tasks SET tags = '' WHERE id = %d;", id);
        dbService.execSQL(sql);
    }

    void print_help()
    {
        std::cout << "Clist CLI Help\n";
        std::cout << "Usage:\n";
        std::cout << "  add <task>            or -a <task>              : Add a new task\n";
        std::cout << "  remove <id>           or -r <id>                : Remove a task by id\n";
        std::cout << "  list                  or -l                     : List all tasks\n";
        std::cout << "  mark <id> done/false  or -m <id> done/false     : Mark task as done/false\n";
        std::cout << "  tag <tag> <id>        or -t <tag> <id>          : Add a tag to a task\n";
        std::cout << "  rtag <id>             or -rt <id>               : Remove tag from a task\n";
        std::cout << "  help                  or -h                     : Show this help message\n";
    }
};