#pragma once
#include <DisplayManager.h>
#include <DB.h>
#include <Types.h>

class Tracker {
    private:
        DisplayManager dm;
        DB db;
        void closeDB();
        void start();

        void findActivity(std::string name);
        void addActivity();
        void displayAll();

        void dropTable();
        void showTable();

    public:
        Tracker();
        ~Tracker();
        Tracker(Tracker &t);
};