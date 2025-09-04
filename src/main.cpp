#include <stdio.h>
#include "db_service.hpp"
#include "todo_service.hpp"
#include <memory>
#include <string>
#include <iostream>

auto db_controller = std::unique_ptr<DbService>(new DbService());
auto todo_service = std::unique_ptr<TodoService>(new TodoService(*db_controller));

char* filename = "db.sqlite3";

    std::string input;

    db_controller->openDB(filename);

    }
    
    db_controller->closeDB();

    return 0;
}
