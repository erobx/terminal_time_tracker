#pragma once
#include <DisplayManager.h>
#include <DB.h>
#include <Types.h>

class Tracker {
    private:
        DisplayManager dm;
        DB db;
        void loadActivities();
        void closeDB();
        void insertData();

        void start();
    public:
        Tracker();
        ~Tracker();
        Tracker(Tracker &t);

        // DM API
        void displayActivity(std::string name);
        void addActivity();
        void displayAll();

        // DB API
        void dropTable();
        void showTable();

};