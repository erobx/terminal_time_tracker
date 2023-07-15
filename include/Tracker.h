#pragma once
#include <DisplayManager.h>
#include <DB.h>
#include <Types.h>
#include <unordered_map>

class Tracker {
    private:
        DisplayManager dm;
        u_map_sa activities;
        u_map_sa newActs;
        DB db;
        void loadActivities();
        void closeDB();
        void insertData();
        void showTable();
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
};