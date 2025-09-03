#include <stdio.h>
#include "db-control.hpp"

dbControl db_controller;
char* filename = "db.sqlite3";


int main() {
    db_controller.openDB(filename);
    db_controller.execSQL("CREATE TABLE IF NOT EXISTS tasks (id INTEGER PRIMARY KEY, task TEXT NOT NULL);");
    db_controller.execSQL("DELETE FROM tasks;"); // Clear existing data
    db_controller.execSQL("INSERT INTO tasks (task) VALUES ('Task 1');");
    db_controller.readDataStmt("tasks");
    db_controller.closeDB();
    return 0;
}