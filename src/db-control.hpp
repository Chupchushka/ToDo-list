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

        void readDataStmt(const char* tableName){
            char sql[256];
            snprintf(sql, sizeof(sql), "SELECT * FROM '%s';", tableName);

            sqlite3_stmt* stmt;
            int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
            if(rc != SQLITE_OK){
                printf("error occurred: %s\n", sqlite3_errmsg(db));
            } else {
                int NoOfCols = sqlite3_column_count(stmt);
                bool done = false;
                while(!done){
                    switch(sqlite3_step(stmt)){
                    case SQLITE_ROW:
                        for(int i=0; i<NoOfCols; i++){
                            const char* colName = sqlite3_column_name(stmt, i);
                            const unsigned char* text = sqlite3_column_text(stmt, i);
                            printf("Col: %s = %s \n", colName, text);
                        }
                        printf("\n");
                        break;
                    case SQLITE_DONE:
                        printf("done reading all rows \n");
                        sqlite3_finalize(stmt);
                        done = true;
                        break;
                    }
                }
            }
        }
};
