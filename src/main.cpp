#include <stdio.h>
#include "db_service.hpp"
#include "todo_service.hpp"
#include <memory>
#include <string>
#include <iostream>

auto db_controller = std::unique_ptr<DbService>(new DbService());
auto todo_service = std::unique_ptr<TodoService>(new TodoService(*db_controller));

char* filename = "db.sqlite3";

int main(int argc, char* argv[]) {
    std::string input;

    db_controller->openDB(filename);

    //Loop through command line arguments
    
    for (int i = 1; i < argc; i++) {

        if ((std::string(argv[i]) == "add" || std::string(argv[i]) == "-a") && i + 1 < argc) {
            todo_service->addTask(argv[i + 1]);
            i++;
        } else if ((std::string(argv[i]) == "remove" || std::string(argv[i]) == "-r") && i + 1 < argc) {
            int id = std::stoi(argv[i + 1]);
            todo_service->removeTask(id);
            i++;
        } else if (std::string(argv[i]) == "list" || std::string(argv[i]) == "-l") {
            todo_service->listTasks();
        } else if (std::string(argv[i]) == "mark" || std::string(argv[i]) == "-m" && i + 1 < argc) {
            todo_service->markTaskDone(std::stoi(argv[i + 1]), argv[i + 2] && std::string(argv[i + 2]) == "done" ? true : false);
            i++;
        } else if (std::string(argv[i]) == "help" || std::string(argv[i]) == "-h") {
            todo_service->print_help();
        } else {
            todo_service->print_help();
        }

    }
    
    db_controller->closeDB();

    return 0;
}
