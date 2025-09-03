#include <stdio.h>
#include "db-control.hpp"

dbControl db_controller;
char* filename = "db.sqlite3";

int main() {
    db_controller.openDB(filename, db_controller.db);

    return 0;
}