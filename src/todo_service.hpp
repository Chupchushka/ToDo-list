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
            snprintf(sql, sizeof(sql), "INSERT INTO tasks (task) VALUES ('%s');", task);
            dbService.execSQL(sql);
        }

        void removeTask(const int id) {
            char sql[256];
            snprintf(sql, sizeof(sql), "DELETE FROM tasks WHERE id = ('%d')", id);
            dbService.execSQL(sql);
        }

        void createTasksTable() {
            dbService.execSQL("CREATE TABLE IF NOT EXISTS tasks (id INTEGER PRIMARY KEY, task TEXT NOT NULL);");
        }

        void listTasks() {
            dbService.readDataStmt("tasks");
        }
    
};