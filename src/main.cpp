#include <Tracker.h>

/*
    Features:
    - Add date and parsing
    - Schedule:
        - slot activities and time
*/


int main() {
    Tracker tracker;

    tracker.addActivity();
    tracker.displayAll();
    // tracker.dropTable();

    return 0;
}