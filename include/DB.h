#pragma once
#include <Activity.h>
#include <DisplayManager.h>
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

        static int printCallback(void *dm, int count, char* data[], char* cols[]);
        static int distinctCallback(void *v, int count, char* data[], char* cols[]);
        static int findCallback(void *v, int count, char* data[], char* cols[]);

        void checkDBErrors();
        void createTable();
    public:
        DB();
        void insertAct(Activity act);
        void findAct(DisplayManager *dm, std::string name);
        void showDistinctActs(DisplayManager *dm);

        void showTable(DisplayManager *dm);
        void deleteRow(int id);
        void closeDB();
        void dropTable();
        
};