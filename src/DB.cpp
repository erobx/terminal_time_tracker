#include <DB.h>
#include <Types.h>
#include <Helper.h>
#include <cstring>
#include <iostream>

using std::string;
using namespace HelperFuncs;

int DB::printCallback(void *notUsed, int count, char* data[], char* cols[]) {
    int idx;

    std::cout << "There are " << count << " column(s)" << "\n";

    for (idx = 0; idx < count; idx++) {
        std::cout << "The data in column " << cols[idx] << " is: " << data[idx] << "\n";
    }

    std::cout << "\n";
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
    // std::cout << "DB Opened" << "\n\n";
}

void DB::createTable() {
    sql = "CREATE TABLE IF NOT EXISTS Activities ("
            "ID INTEGER PRIMARY KEY, "
            "NAME TEXT NOT NULL, "
            "TIME_START TEXT NOT NULL, "
            "TIME_END TEXT NOT NULL, "
            "DURATION TEXT NOT NULL, "
            "DATE TEXT NOT NULL"
          ");";
    rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);
}

void DB::insertData(Activity act) {
    char* query = 0;

    sql = "INSERT INTO Activities ('NAME', 'TIME_START', 'TIME_END', 'DURATION', 'DATE')"
          "VALUES ('%s', '%s', '%s', '%s', '%s');";

    asprintf(&query, sql.c_str(), act.name.c_str(), act.time_start.c_str(), act.time_end.c_str(), act.duration.c_str(), act.date.c_str());

    sqlite3_prepare(db, query, strlen(query), &stmt, NULL);

    rc = sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    free(query);
}

void DB::showTable() {
    sql = "SELECT * FROM Activities;";

    rc = sqlite3_exec(db, sql.c_str(), printCallback, 0, &errMsg);
}

void DB::deleteRow(string id) {
    char *query = NULL;

    // Build a string using asprintf()
    asprintf(&query, "DELETE FROM Activities WHERE ID = '%s';", id.c_str());

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

void DB::loadActivities(u_map_sa &acts) {
    sql = "SELECT * FROM Activities;";

    rc = sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL);
    checkDBErrors();

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int id              = sqlite3_column_int (stmt, 0);
        const u_char* name  = sqlite3_column_text(stmt, 1);
        const u_char* start = sqlite3_column_text(stmt, 2);
        const u_char* end   = sqlite3_column_text(stmt, 3);
        const u_char* dur   = sqlite3_column_text(stmt, 4);
        const u_char* date  = sqlite3_column_text(stmt, 5);

        string name_str = convertCharToString(name);
        string start_str = convertCharToString(start);
        string end_str = convertCharToString(end);
        string dur_str = convertCharToString(dur);
        string date_str = convertCharToString(date);

        DBActivity newAct = {
            name_str,
            start_str,
            end_str,
            dur_str,
            date_str
        };

        acts.emplace(newAct.name, newAct);
    }

    // checkDBErrors();
    sqlite3_finalize(stmt);
}