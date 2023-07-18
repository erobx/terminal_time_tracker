#include <Tracker.h>

void Tracker::closeDB() {
    db.closeDB();
}

void Tracker::showTable() {
    db.showTable();
}

void Tracker::dropTable() {
    db.dropTable();
}

void Tracker::start() {
    int i = 0;
    std::string name;

    do {
        dm.drawMenu();
        i = dm.getInt("Enter menu option: ");

        switch (i) {
            case 1:
                // addActivity();
                break;
            case 2:
                // name = dm.getName();
                // displayActivity(name);
                break;
            case 3:
                // displayAll();
                break;
        }

    } while (i != 4);
}

Tracker::Tracker() {
    // dm.congrats();
    // start();
}

Tracker::~Tracker() {
    closeDB();
}

Tracker::Tracker(Tracker &t) {
    this->dm = t.dm;
    this->db = t.db;
}

// void Tracker::displayActivity(std::string name) {
//     std::vector<Activity> list_of_acts = activities.at(name);

// }

void Tracker::addActivity() {
    Activity act = dm.takeInput();
    db.insertAct(act);
}

// void Tracker::displayAll() {
//     for (auto it = activities.begin(); it != activities.end(); it++) {
//         displayActivity(it->first);
//     }
// }

// void Tracker::insertData() {
//     for (auto it = newActs.begin(); it != newActs.end(); it++) {
//         db.insertData(it->second);
//     }
// }

