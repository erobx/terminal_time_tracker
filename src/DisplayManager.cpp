#include <DisplayManager.h>
#include <Helper.h>
#include <iostream>

using std::string;
using namespace HelperFuncs;

void DisplayManager::drawHorLine() {
    std::cout << line << std::endl;
}

void DisplayManager::drawVertLine() {
    std::cout << "|";
    for (int i = 0; i < spaces; i++) {std::cout << " ";};
    std::cout << "|" << std::endl;
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
    std::cout << "|";
    for (int i = 0; i < offset; i++) {std::cout << " ";};

    std::cout << input;
    
    for (int i = 0; i < offset-1; i++) {std::cout << " ";};
    std::cout << "|" << std::endl;
}

void DisplayManager::drawOdd(int offset, string input) {
    std::cout << "|";
    for (int i = 0; i < offset; i++) {std::cout << " ";};

    std::cout << input;
    
    for (int i = 0; i < offset; i++) {std::cout << " ";};
    std::cout << "|" << std::endl;
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

void DisplayManager::congrats() {
    drawTop(2);

    drawInput("Congrats! New high score!");

    drawBot(2);
}

void DisplayManager::drawTable(Activity &act) {
    drawTop(2);

    displayAct(act);

    drawBot(2);
}

Activity DisplayManager::takeInput() {
    Activity act;
    bool valid = false;
    string time_format = "HH:MM AM/PM";
    string date_format = "MM/DD/YY";

    while (!valid) {
        Name res;
        string name = "";
        std::cout << "Enter activity name: ";
        getline(std::cin, name);
        res = parseNameInput(name, line.length());
        valid = res.flag;
        if (valid)
            act.name = res.name;
    }

    valid = false;

    while (!valid) {
        Time res;
        string time = "";
        std::cout << "(" << time_format << ")" << " Enter start time: ";
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
        std::cout << "(" << time_format << ")" << " Enter end time: ";
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
        std::cout << "(" << date_format << ")" << " Enter date: ";
        getline(std::cin, date);
        res = parseDateInput(date);
        valid = res.flag;
        if (valid)
            act.date = date;
    }

    try {
        act.secs_duration = act.secs_end - act.secs_start;
        if (act.secs_duration < 0) throw std::exception{};
        act.duration = secsToTime(act.secs_duration);
        std::cout << "Duration: " << act.duration << std::endl;
    } catch (...) {
        std::cout << "End time is earlier than start time." << std::endl;
    }
    
    return act;
}

