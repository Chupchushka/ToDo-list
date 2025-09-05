#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <map>
#include "db_service.hpp"

class TodoService
{
private:
public:
    DbService &dbService;

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

    void markTaskDone(const int id, bool done)
    {
        char sql[256];
        snprintf(sql, sizeof(sql), "UPDATE tasks SET done = %d WHERE id = %d;", done ? 1 : 0, id);
        dbService.execSQL(sql);
    }

    void addTag(const char *tag, const char *color, int taskId)
    {
        char sql[256];
        snprintf(sql, sizeof(sql), "UPDATE tasks SET tags = '%s', color = '%s' WHERE id = %d;", tag, color, taskId);
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

    void print_table()
    {
        // ANSI color codes map
        std::map<std::string, std::string> color_codes = {
            {"red", "\033[31m"},
            {"green", "\033[32m"},
            {"yellow", "\033[33m"},
            {"blue", "\033[34m"},
            {"magenta", "\033[35m"},
            {"cyan", "\033[36m"},
            {"reset", "\033[0m"}};

        char sql[256];
        snprintf(sql, sizeof(sql), "SELECT id, task, tags, done, color FROM tasks;");

        sqlite3_stmt *stmt;
        int rc = sqlite3_prepare_v2(dbService.db, sql, -1, &stmt, NULL);
        // check for errors in preparing the statement
        if (rc != SQLITE_OK)
        {
            std::cout << "Error: " << sqlite3_errmsg(dbService.db) << std::endl;
            return;
        }

        // Print table header
        std::cout << "+----+----------------------+----------------------+-------+" << std::endl;
        std::cout << "| ID | Task                 | Tag                  | Done  |" << std::endl;
        std::cout << "+----+----------------------+----------------------+-------+" << std::endl;

        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            int id = sqlite3_column_int(stmt, 0);
            const unsigned char *task = sqlite3_column_text(stmt, 1);
            const unsigned char *tag = sqlite3_column_text(stmt, 2);
            int done = sqlite3_column_int(stmt, 3);
            const unsigned char *color = sqlite3_column_text(stmt, 4);

            std::string color_code = color ? color_codes[std::string(reinterpret_cast<const char *>(color))] : "";
            std::string reset_code = color_codes["reset"];

            // Print row with color for task and tag
            std::cout << "| "
                      << id << "  | "
                      << color_code << std::setw(20) << std::left << (task ? reinterpret_cast<const char *>(task) : "") << reset_code << " | "
                      << color_code << std::setw(20) << std::left << (tag ? reinterpret_cast<const char *>(tag) : "") << reset_code << " | "
                      << std::setw(5) << std::left << (done ? "TRUE" : "FALSE") << " |" << std::endl;
        }

        std::cout << "+----+----------------------+----------------------+-------+" << std::endl;
        sqlite3_finalize(stmt);
    }
};