#include <DisplayManager.h>
#include <Helper.h>
#include <iostream>
#include <sstream>

using std::string;
using std::cout;
using std::endl;
using namespace HelperFuncs;

void DisplayManager::drawHorLine() {
    cout << line << endl;
}

void DisplayManager::drawVertLine() {
    cout << "|";
    for (int i = 0; i < spaces; i++) {cout << " ";};
    cout << "|" << endl;
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

void DisplayManager::drawEven(int offset, string input) {
    cout << "|";
    for (int i = 0; i < offset; i++) {cout << " ";};

    cout << input;
    
    for (int i = 0; i < offset-1; i++) {cout << " ";};
    cout << "|" << endl;
}

void DisplayManager::drawOdd(int offset, string input) {
    cout << "|";
    for (int i = 0; i < offset; i++) {cout << " ";};

    cout << input;
    
    for (int i = 0; i < offset; i++) {cout << " ";};
    cout << "|" << endl;
}

void DisplayManager::drawInput(string input) {
    int offset = 0;

    if (input.length() % 2 == 0) {
        offset = (spaces - input.length())/2 + 1;
        drawEven(offset, input);
    } else {
        offset = (spaces - input.length())/2;
        drawOdd(offset, input);
    }
}

void DisplayManager::displayAct(Activity &act) {
    drawInput("Activity: " + act.name);
    drawInput("Start: " + act.time_start);
    drawInput("End: " + act.time_end);
    drawInput("Duration: " + act.duration);
    drawInput("Date: " + act.date);
}

void DisplayManager::drawMenu() {
    drawTop(2);
    drawInput("1. Add an activity");
    drawInput("2. Find an activity");
    drawInput("3. Display all activities");
    drawInput("4. To quit");
    drawBot(2);
}

void DisplayManager::congrats() {
    drawTop(2);
    drawInput("Congrats! New high score!");
    drawBot(2);
}

void DisplayManager::drawActTable(Activity &act) {
    drawTop(2);
    displayAct(act);
    drawBot(2);
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

