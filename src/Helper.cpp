#include <Helper.h>
#include <string>
#include <iostream>
#include <exception>
#include <cstring>

using std::string;
using namespace HelperFuncs;

Name HelperFuncs::parseNameInput(string name, int length) {
    Name result;
    bool flag = true;
    string act_str = "Activity: ";
    int act_len = act_str.length();

    try {
        if (name.length() + act_len >= length - 2) throw std::exception{};
    } catch (...) {
        std::cout << "Name too long!" << std::endl;
        flag = false;
    }

    result.name = name;
    result.flag = flag;

    return result;
}

Time HelperFuncs::parseTimeInput(string time) {
    Time result;
    bool flag = true;
    int hours, mins = 0;

    try {
        int semicolon_pos = time.find(":");
        int space_pos = time.find(" ");

        if (semicolon_pos == -1) throw std::exception{};
        if (space_pos == -1) throw std::exception{};

        // parse hours
        string temp = time.substr(0, semicolon_pos);
        if (temp.length() > 2) throw std::exception{};
        try {
            hours = stoi(temp);
            if (hours < 1 || hours > 12) throw std::exception{};
            hours = hours * 3600;
        } catch (...) {throw;}

        // parse mins
        temp = time.substr(semicolon_pos+1, 2);
        if (temp.length() > 2 || temp.length() == 1) throw std::exception{};
        try {
            mins = stoi(temp);
            if (mins < 0 || mins > 59) throw std::exception{};
            mins = mins * 60;
        } catch (...) {throw;}

        // parse AM/PM
        temp = time.substr(space_pos+1);
        if (temp.length() != 2) throw std::exception{};
        try {
            const char* am = "AM";
            const char* pm = "PM";

            if (strcasecmp(am, temp.c_str()) != 0) {
                if (strcasecmp(pm, temp.c_str()) != 0) {
                    throw std::exception{};
                }
            }

            int check = strcasecmp(am, temp.c_str());
            if (check == 0) {
                time = time.substr(0, space_pos+1) + am;
            } else {
                time = time.substr(0, space_pos+1) + pm;
            }
        } catch (...) {throw;}
    } catch (...) {
        std::cout << "Invalid time" << std::endl;
        flag = false;
    }

    result.time = time;
    result.flag = flag;
    result.secs = hours + mins;

    return result;
}

Date HelperFuncs::parseDateInput(string date) {
    Date result;
    bool flag = true;

    // MM/DD/YY
    try {
        int slash_pos = date.find("/");
        
        // if no / is found initially
        if (slash_pos == -1) throw std::exception{};

        /*
            1. MM/DD/YY 01-12, 01-31, 00-99
            2. DD/YY
            3. YY
        */
        


    } catch (...) {
        std::cout << "Invalid date" << std::endl;
        flag = false;
    }

    result.date = date;
    result.flag = flag;

    return result;
}

string HelperFuncs::secsToTime(int secs) {
    int hrs = secs / 3600;
    secs = secs - (hrs * 3600);
    int mins = secs / 60;

    string result;
    if (hrs == 1) {
        if (mins == 0) {                            // 1:00
            result = std::to_string(hrs) + " hr";
        } else if (mins == 1) {                     // 1:01
            result = std::to_string(hrs) + " hr " + std::to_string(mins) + " min";
        } else {                                    // 1:02-1:59
            result = std::to_string(hrs) + " hr " + std::to_string(mins) + " mins";
        }
    } else if (mins == 0) {                         // 2:00-12:00
        result = std::to_string(hrs) + " hrs";
    } else if (mins == 1) {                         // 00:01
        result = std::to_string(mins) + " min";
    } else {                                        // everything else
        result = std::to_string(hrs) + " hrs " + std::to_string(mins) + " mins";
    }
    return result;
}

string HelperFuncs::convertCharToString(const u_char* s) {
    const char* a = reinterpret_cast<const char*>(s);
    char* temp = const_cast<char*>(a);
    return string(temp);
}

