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

        void addActivity();
        void displayAll();
        void displayDistinctActs();
        void findActivity();

        void dropTable();
        void showTable();

    public:
        Tracker();
        ~Tracker();
        Tracker(Tracker &t);
};