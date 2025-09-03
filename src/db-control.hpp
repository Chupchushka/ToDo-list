#pragma once
#include <stdio.h>
#include <sqlite3.h>

class dbControl {
    private:
        sqlite3 *db;
    public:
        

        void openDB(char* filename) {
            int opened = sqlite3_open(filename, &db);
            if(opened){ // check if opening the database is successful
             printf("Database could not be opened %s \n", sqlite3_errmsg(db));
            } else {
              printf("opened database successfuly \n");
                //db = db;
            }
        }

        void execSQL(char* sql) {
            char* errMsg;
            
            int rc = sqlite3_exec(db, sql, NULL, 0, &errMsg);
            if(rc != SQLITE_OK) {
                printf("error occured %s\n", errMsg);
                sqlite3_free(errMsg);
            } else {
                printf("sql runned succesfully \n");
            }
        }

        void closeDB() {
            sqlite3_close(db);
            printf("closed database successfully \n");
        }
};
