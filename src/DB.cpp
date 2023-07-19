#include <DB.h>
#include <DisplayManager.h>
#include <Types.h>
#include <Helper.h>
#include <cstring>
#include <iostream>

using std::string;
using namespace HelperFuncs;

int DB::printCallback(void *notUsed, int count, char* data[], char* cols[]) {
    DisplayManager dm;
    Activity act = convertRowToAct(count, data);

    dm.drawActTable(act);

    return 0;
}

void DB::checkDBErrors() {
    if (rc) {
        std::cout << "DB Error: " << sqlite3_errmsg(db) << std::endl;
        closeDB();
    }
}

DB::DB() {
    // save the result of opening the file
    rc = sqlite3_open("database.db", &db);
    checkDBErrors();
    createTable();
}

void DB::createTable() {
    sql = "CREATE TABLE IF NOT EXISTS Activities ("
            "ID INTEGER PRIMARY KEY, "
            "NAME TEXT NOT NULL, "
            "TIME_START INT NOT NULL, "
            "TIME_END INT NOT NULL, "
            "DURATION INT NOT NULL, "
            "DATE TEXT NOT NULL"
          ");";
    rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);
}

void DB::insertAct(Activity act) {
    char* query = 0;

    sql = "INSERT INTO Activities ('NAME', 'TIME_START', 'TIME_END', 'DURATION', 'DATE')"
          "VALUES ('%s', '%i', '%i', '%i', '%s');";

    asprintf(&query, sql.c_str(), act.name.c_str(), act.secs_start, act.secs_end, act.secs_duration, act.date.c_str());

    sqlite3_prepare(db, query, strlen(query), &stmt, NULL);

    rc = sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    free(query);
}

void DB::showTable() {
    sql = "SELECT * FROM Activities;";

    rc = sqlite3_exec(db, sql.c_str(), printCallback, 0, &errMsg);
}

void DB::deleteRow(int id) {
    char *query = NULL;

    // Build a string using asprintf()
    asprintf(&query, "DELETE FROM Activities WHERE ID = '%i';", id);

    // Prepare the query
    sqlite3_prepare(db, query, strlen(query), &stmt, NULL);

    // Test it
    rc = sqlite3_step(stmt);

    // Finalize the usage
    sqlite3_finalize(stmt);

    // Free up the query space
    free(query);
}

void DB::closeDB() {
    sqlite3_close(db);
    // std::cout << "DB Closed" << "\n";
}

void DB::dropTable() {
    sql = "DROP TABLE Activities;";
    rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);
}

