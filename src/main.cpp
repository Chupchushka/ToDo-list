#include <stdio.h>
#include "db-control.hpp"

dbControl db_controller;
char* filename = "db.sqlite3";


int main() {
    db_controller.openDB(filename);
    db_controller.execSQL("CREATE TABLE IF NOT EXISTS tasks (id INTEGER PRIMARY KEY, task TEXT NOT NULL);");
    db_controller.closeDB();
    return 0;
}