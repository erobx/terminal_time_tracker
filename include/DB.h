#pragma once
#include <Activity.h>
#include <Types.h>
#include <sqlite3.h>
#include <iostream>

class DB {
    private:
        sqlite3 *db = nullptr;          // connection
        sqlite3_stmt *stmt = nullptr;   // db statement
        std::string sql = "";           // query
        int rc = 0;                     // result of opening the file
        char* errMsg = 0;               // save any error msg
        static int printCallback(void *notUsed, int count, char* data[], char* cols[]);
        void checkDBErrors();
        void createTable();
    public:
        DB();
        void insertData(Activity act);
        void showTable();
        void deleteRow(std::string id);
        void closeDB();
        void dropTable();
        void loadActivities(u_map_sa &acts);
};