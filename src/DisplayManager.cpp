#include <DisplayManager.h>
#include <Helper.h>
#include <iostream>
#include <sstream>
#include <vector>

using std::string;
using std::cout;
using std::endl;
using namespace HelperFuncs;

void DisplayManager::drawHorLine() {
    cout << "\033[35m" << line << reset << endl;
}

void DisplayManager::drawVertLine() {
    cout << vert;
    for (int i = 0; i < spaces; i++) {cout << " ";};
    cout << vert << endl;
}

void DisplayManager::drawMultiLine(int n) {
    for (int i = 0; i < n; i++) {drawVertLine();}
}

void DisplayManager::drawTop(int n) {
    drawHorLine();
    drawMultiLine(n);
}

void DisplayManager::drawBot(int n) {
    drawMultiLine(n);
    drawHorLine();
}

void DisplayManager::drawEven(int offset, string input, string color) {
    cout << vert;
    for (int i = 0; i < offset; i++) {cout << " ";};

    string paint = "\033[" + color + "m";
    cout << paint << input << reset;
    
    for (int i = 0; i < offset-1; i++) {cout << " ";};
    cout << vert << endl;
}

void DisplayManager::drawOdd(int offset, string input, string color) {
    cout << vert;
    for (int i = 0; i < offset; i++) {cout << " ";};

    string paint = "\033[" + color + "m";
    cout << paint << input << reset;

    for (int i = 0; i < offset; i++) {cout << " ";};
    cout << vert << endl;
}

void DisplayManager::drawInput(string input, string color) {
    int offset = 0;

    if (input.length() % 2 == 0) {
        offset = (spaces - input.length())/2 + 1;
        drawEven(offset, input, color);
    } else {
        offset = (spaces - input.length())/2;
        drawOdd(offset, input, color);
    }
}

void DisplayManager::displayAct(Activity &act) {
    drawInput("Activity: " + act.name, "31");
    drawInput("Start: " + act.time_start, "34");
    drawInput("End: " + act.time_end, "34");
    drawInput("Duration: " + act.duration, "33");
    drawInput("Date: " + act.date, "33");
}

void DisplayManager::drawMenu() {
    drawTop(0);
    drawInput("1. Add an activity", "32");
    drawInput("2. Find an activity", "34");
    drawInput("3. Show recorded activities", "33");
    // drawInput("4. Display all activities", "35");
    drawInput("4. Delete an activity", "35");
    drawInput("5. To quit", "31");
    drawBot(0);
}

void DisplayManager::congrats() {
    drawTop(0);
    drawInput("Congrats! New high score!", "34");
    drawBot(0);
}

void DisplayManager::drawActTable(Activity &act) {
    drawTop(0);
    displayAct(act);
    drawBot(0);
}

void DisplayManager::drawDistinctNames(std::vector<string> names) {
    drawTop(0);
    drawInput("List of available activities: ", "31");
    for (int i = 0; i < names.size(); i++) {
        drawInput(names.at(i), "32");
    }
    drawBot(0);
}

void DisplayManager::drawTableOfActs(actmap acts) {
    line = std::string(99, '-');
    spaces = line.length()-2;
    auto it = acts.begin();
    string name = it->second.name;
    string line_input = "";
    string space = "  ";
    Activity curr;

    drawTop(0);
    drawInput("Showing results for: "+name, "32");

    for (it; it != acts.end(); it++) {
        curr = it->second;
        string id = std::to_string(it->first);
        line_input = "ID: " + id + space + " Date: " + curr.date + space
            + "Start: " + curr.time_start + space
            + "End: " + curr.time_end + space
            + "Duration: " + curr.duration;
        drawInput(line_input, "34");
    }
    drawBot(0);
    line = std::string(37, '-');
    spaces = line.length()-2;
}

Activity DisplayManager::takeInput() {
    Activity act;
    bool valid = false;
    string time_format = "HH:MM AM/PM";
    string date_format = "YYYY-MM-DD";        // YYYY-MM-DD per ISO 8601 strings

    while (!valid) {
        Name res;
        string name = "";
        cout << "Enter activity name: ";
        getline(std::cin, name);
        res = parseNameInput(name, line.length());
        valid = res.flag;
        if (valid)
            act.name = res.name;
    }
    INPUT:
    valid = false;
    while (!valid) {
        Time res;
        string time = "";
        cout << "(" << time_format << ")" << " Enter start time: ";
        getline(std::cin, time);
        res = parseTimeInput(time);
        valid = res.flag;
        if (valid) {
            act.time_start = res.time;
            act.secs_start = res.secs;
        }
    }

    valid = false;
    while (!valid) {
        Time res;
        string time = "";
        cout << "(" << time_format << ")" << " Enter end time: ";
        getline(std::cin, time);
        res = parseTimeInput(time);
        valid = res.flag;
        if (valid) {
            act.time_end = res.time;
            act.secs_end = res.secs;
        }
    }

    valid = false;
    while (!valid) {
        Date res;
        string date = "";
        cout << "(" << date_format << ")" << " Enter date: ";
        getline(std::cin, date);
        res = parseDateInput(date);
        valid = res.flag;
        if (valid)
            act.date = date;
    }

    if (!calcDuration(act))
        goto INPUT;
    
    return act;
}

string DisplayManager::getName() {
    string name;
    cout << "Enter activity name: ";
    getline(std::cin, name);
    return name;
}

int DisplayManager::getInt(string prompt) {
    int ret_int;
    string str_num;

    while (true) {
        cout << prompt;
        getline(std::cin, str_num);
        std::stringstream convert(str_num);

        if (convert >> ret_int && !(convert >> str_num)) return ret_int;

        std::cin.clear();
        std::cerr << "Input was not a valid integer!\n"; 
    }
}

