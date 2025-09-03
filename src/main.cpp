#include <stdio.h>
#include "db_service.hpp"
#include "todo_service.hpp"
#include <memory>
#include <string>
#include <iostream>

auto db_controller = std::unique_ptr<DbService>(new DbService());
auto todo_service = std::unique_ptr<TodoService>(new TodoService(*db_controller));

char* filename = "db.sqlite3";


int main() {
    std::string input;

    db_controller->openDB(filename);

    while (true)
    {
        std::cout << "Enter command: ";
        std::getline(std::cin, input);

        if (input == "add") {
            std::string task;
            printf("Enter task description: ");
            std::getline(std::cin, task);
            todo_service->addTask(task.c_str());
        }
        else if (input == "remove") {
            int id;
            printf("Enter task ID to remove: ");
            std::cin >> id;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            todo_service->removeTask(id);
        }
        else if (input == "list") {
            todo_service->listTasks();
        }
        else if (input == "exit") {
            printf("Exiting...\n");
            break;
        }
        else {
            printf("Unknown command. Available commands: add, remove, list, exit\n");
        }
    }
    
    db_controller->closeDB();

    return 0;
}
