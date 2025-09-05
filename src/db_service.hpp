#pragma once
#include <stdio.h>
#include <sqlite3.h>

class DbService
{
private:
public:
    sqlite3 *db;

    void openDB(char *filename)
    {
        int opened = sqlite3_open(filename, &db);
        if (opened)
        { // check if opening the database is successful
          // printf("Database could not be opened %s \n", sqlite3_errmsg(db));
        }
        else
        {
            // printf("opened database successfuly \n");
            execSQL("CREATE TABLE IF NOT EXISTS tasks (id INTEGER PRIMARY KEY AUTOINCREMENT, task TEXT NOT NULL, done BOOLEAN NOT NULL CHECK (done IN (0, 1)), tags TEXT, color TEXT);");
            // db = db;
        }
    }

    void execSQL(char *sql)
    {
        char *errMsg;

        int rc = sqlite3_exec(db, sql, NULL, 0, &errMsg);
        if (rc != SQLITE_OK)
        {
            printf("error occured %s\n", errMsg);
            sqlite3_free(errMsg);
        }
        else
        {
            // printf("sql runned succesfully \n");
        }
    }

    void closeDB()
    {
        sqlite3_close(db);
        // printf("closed database successfully \n");
    }

    void readDataStmt(const char *tableName)
    {
        char sql[256];
        snprintf(sql, sizeof(sql), "SELECT id, task, done, tags FROM '%s';", tableName);

        sqlite3_stmt *stmt;
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
        if (rc != SQLITE_OK)
        {
            printf("error occurred: %s\n", sqlite3_errmsg(db));
        }
        else
        {
            // Print table header
            printf("+----+----------------------+-------+----------------------+\n");
            printf("| ID | Task                 | Done  | Tags                 |\n");
            printf("+----+----------------------+-------+----------------------+\n");

            while (sqlite3_step(stmt) == SQLITE_ROW)
            {
                int id = sqlite3_column_int(stmt, 0);
                const unsigned char *task = sqlite3_column_text(stmt, 1);
                int done = sqlite3_column_int(stmt, 2);
                const unsigned char *tags = sqlite3_column_text(stmt, 3);

                printf("| %-2d | %-20s | %-5s | %-20s |\n", id, task ? (const char *)task : "", done ? "TRUE" : "FALSE", tags ? (const char *)tags : "");
            }
            printf("+----+----------------------+-------+----------------------+\n");
            printf("done reading all rows \n");
            sqlite3_finalize(stmt);
        }
    }
};
