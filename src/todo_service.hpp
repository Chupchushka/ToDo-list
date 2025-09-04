#include <stdio.h>
#include "db_service.hpp"

class TodoService {
    private:
        DbService &dbService;
    public:
        TodoService(DbService &db) : dbService(db) {
        }

        void addTask(const char* task) {
            char sql[256];
            snprintf(sql, sizeof(sql), "INSERT INTO tasks (task, done) VALUES ('%s', 0);", task);
            dbService.execSQL(sql);
        }

        void removeTask(const int id) {
            char sql[256];
            snprintf(sql, sizeof(sql), "DELETE FROM tasks WHERE id = ('%d')", id);
            dbService.execSQL(sql);
        }

        void listTasks() {
            dbService.readDataStmt("tasks");
        }

        void markTaskDone(const int id, bool done) {
            char sql[256];
            snprintf(sql, sizeof(sql), "UPDATE tasks SET done = %d WHERE id = %d;", done ? 1 : 0, id);
            dbService.execSQL(sql);
        }
    
};