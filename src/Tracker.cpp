#include <Tracker.h>

void Tracker::loadActivities() {
    db.loadActivities(activities);
}

void Tracker::closeDB() {
    db.closeDB();
}

void Tracker::showTable() {
    db.showTable();
}

void Tracker::dropTable() {
    db.dropTable();
}

Tracker::Tracker() {
    loadActivities();
}

Tracker::~Tracker() {
    insertData();
    // showTable();
    closeDB();
}

Tracker::Tracker(Tracker &t) {
    this->dm = t.dm;
    this->activities = t.activities;
    this->newActs = t.newActs;
    this->db = t.db;
}

void Tracker::displayActivity(std::string name) {
    Activity act = activities.at(name);
    dm.drawTable(act);
}

void Tracker::addActivity() {
    Activity act = dm.takeInput();
    newActs.emplace(act.name, act);
    activities.emplace(act.name, act);
}

void Tracker::displayAll() {
    for (auto it = activities.begin(); it != activities.end(); it++) {
        displayActivity(it->first);
    }
}

void Tracker::insertData() {
    for (auto it = newActs.begin(); it != newActs.end(); it++) {
        db.insertData(it->second);
    }
}

