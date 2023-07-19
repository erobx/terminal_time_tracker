#include <Helper.h>
#include <string>
#include <iostream>
#include <exception>
#include <cstring>
#include <regex>

using std::string;
using std::regex;
using std::exception;
using namespace HelperFuncs;

Name HelperFuncs::parseNameInput(string name, int length) {
    Name result;
    bool flag = true;
    string act_str = "Activity: ";
    int act_len = act_str.length();

    try {
        if (name.length() + act_len >= length - 2) throw exception{};
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
    int hours, mins, extra = 0;

    try {
        int semicolon_pos = time.find(":");
        int space_pos = time.find(" ");

        if (semicolon_pos == -1) throw exception{};
        if (space_pos == -1) throw exception{};

        // parse hours
        string temp = time.substr(0, semicolon_pos);
        if (temp.length() > 2) throw exception{};
        try {
            hours = stoi(temp);
            if (hours < 1 || hours > 12) throw exception{};
            if (hours == 12)
                hours = 0;
            else
                hours = hours * 3600;
        } catch (...) {throw;}

        // parse mins
        temp = time.substr(semicolon_pos+1, 2);
        if (temp.length() > 2 || temp.length() == 1) throw exception{};
        try {
            mins = stoi(temp);
            if (mins < 0 || mins > 59) throw exception{};
            mins = mins * 60;
        } catch (...) {throw;}

        // parse AM/PM
        temp = time.substr(space_pos+1);
        if (temp.length() != 2) throw exception{};
        try {
            const char* am = "AM";
            const char* pm = "PM";

            if (strcasecmp(am, temp.c_str()) != 0) {
                if (strcasecmp(pm, temp.c_str()) != 0) {
                    throw exception{};
                }
            }

            int check = strcasecmp(am, temp.c_str());
            if (check == 0) {
                time = time.substr(0, space_pos+1) + am;
            } else {
                time = time.substr(0, space_pos+1) + pm;
                if ((hours/3600) < 12)
                    extra = 43200;
            }
        } catch (...) {throw;}
    } catch (...) {
        std::cout << "Invalid time" << std::endl;
        flag = false;
    }

    result.time = time;
    result.flag = flag;
    result.secs = hours + mins + extra;

    return result;
}

Date HelperFuncs::parseDateInput(string date) {
    Date result;
    bool flag = true;

    // sanitize
    regex specialChars { R"([[\],'"A-z;[\^$/.|?*+(){}.])" };
    date = regex_replace(date, specialChars, "");

    // YYYY-MM-DD
    try {
        int first_pos = date.find("-");
        int sec_pos = date.find_last_of("-");

        if (first_pos == -1) throw exception{};
        if (sec_pos == -1) throw exception{};

        string years_str = date.substr(0, first_pos);
        if (years_str.length() < 4) throw exception{};

        string months_str = date.substr(first_pos+1, 2);
        if (years_str.length() < 2) throw exception{};

        string days_str = date.substr(sec_pos+1);
        if (days_str.length() < 2) throw exception{};

        try {
            int months = stoi(months_str);
            if (months < 1 || months > 12) throw exception{};

        } catch (...) {throw;}

        try {
            int days = stoi(days_str);
            if (days < 1 || days > 31) throw exception{};

        } catch (...) {throw;}

        try {
            int years = stoi(years_str);
            if (years < 0 || years > 9999) throw exception{};

        } catch (...) {throw;}
    } catch (...) {
        std::cout << "Invalid date" << "\n";
        flag = false;
    }

    result.date = date;
    result.flag = flag;

    return result;
}

bool HelperFuncs::calcDuration(Activity &act) {
    bool wrap = false;
    if ((act.time_start.find("PM") != -1) && (act.time_end.find("AM") != -1))
        wrap = true;

    try {
        if (wrap) {
            act.secs_duration = (12*3600) + ((12*3600) - act.secs_start);
            act.duration = secsToDuration(act.secs_duration);
            return true;
        } else {
            act.secs_duration = act.secs_end - act.secs_start;
            if (act.secs_duration < 0) throw std::exception{};
            act.duration = secsToDuration(act.secs_duration);
            return true;
        }
    } catch (...) {
        std::cout << "End time is earlier than start time." << std::endl;
    }
    return false;
}

string HelperFuncs::secsToTime(int secs) {
    // HH:MM AM/PM
    int hrs, mins = 0;
    string result, hrs_str, mins_str;

    if (secs >= (12*3600)) {
        // pm
        hrs = (secs / 3600);
        secs = secs - (hrs * 3600);
        mins = secs / 60;

        if (hrs == 12)
            hrs_str = std::to_string(hrs);
        else
            hrs_str = std::to_string(hrs-12);

        if (mins >= 0 && mins < 10)
            mins_str = "0" + std::to_string(mins);
        else
            mins_str = std::to_string(mins);
 
        result = hrs_str + ":" + mins_str + " PM";
    } else {
        // am
        hrs = (secs / 3600);
        secs = secs - (hrs * 3600);
        mins = secs / 60;

        if (hrs == 0)
            hrs_str = std::to_string(12);
        else
            hrs_str = std::to_string(hrs);

        if (mins >= 0 && mins < 10)
            mins_str = "0" + std::to_string(mins);
        else
            mins_str = std::to_string(mins);

        result = hrs_str + ":" + mins_str + " AM";
    }    
    return result;
}

string HelperFuncs::secsToDuration(int secs) {
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

Activity HelperFuncs::convertRowToAct(int count, char* data[]) {
    Activity act = {
        data[1],
        secsToTime(std::stoi(data[2])),
        secsToTime(std::stoi(data[3])),
        secsToDuration(std::stoi(data[4])),
        data[5],
        std::stoi(data[2]),
        std::stoi(data[3]),
        std::stoi(data[4]),
    };

    return act;
}