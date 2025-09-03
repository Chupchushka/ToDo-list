#pragma once
#include <stdio.h>
#include <sqlite3.h>

class dbControl {
    private:
        
    public:
        sqlite3 *db;
        
        void openDB(char* filename, sqlite3* database) {
            int opened = sqlite3_open(filename, &database);
            if(opened){ // check if opening the database is successful
             printf("Database could not be opened %s \n", sqlite3_errmsg(database));
            } else {
              printf("opened database successfuly \n");
                db = database;
            }
        }

        void execSQL(sqlite3* db, char* sql) {
            char* errMsg;
            
            int rc = sqlite3_exec(db, sql, NULL, 0, &errMsg);
            if(rc != SQLITE_OK) {
                printf("error occured %s\n", errMsg);
                sqlite3_free(errMsg);
            } else {
                printf("deleted record successfully \n");
            }
        }

        void closeDB(sqlite3* db) {
            sqlite3_close(db);
            printf("closed database successfully \n");
        }
};
