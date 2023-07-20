#include <Tracker.h>

void Tracker::closeDB() {
    db.closeDB();
}

void Tracker::showTable() {
    db.showTable(&dm);
}

void Tracker::dropTable() {
    db.dropTable();
}

void Tracker::start() {
    int i, input = 0;
    std::string name;

    do {
        dm.drawMenu();
        i = dm.getInt("Enter menu option: ");

        switch (i) {
            case -1:
                dropTable();
                break;
            case 1:
                addActivity();
                break;
            case 2:
                findActivity();
                break;
            case 3:
                displayDistinctActs();
                break;
            // case 4:
            //     displayAll();
            //     break;
            case 4:
                input = dm.getInt("Enter row id: ");
                db.deleteRow(input);
                break;
        }
    } while (i != 5);
}

Tracker::Tracker() {
    start();
}

Tracker::~Tracker() {
    closeDB();
}

Tracker::Tracker(Tracker &t) {
    this->dm = t.dm;
    this->db = t.db;
}

void Tracker::addActivity() {
    Activity act = dm.takeInput();
    db.insertAct(act);
}

void Tracker::displayAll() {
    db.showTable(&dm);
}

void Tracker::displayDistinctActs() {
    db.showDistinctActs(&dm);
}

void Tracker::findActivity() {
    std::string name = "";
    std::cout << "Enter activity name: ";
    std::getline(std::cin, name);
    db.findAct(&dm, name);
}

