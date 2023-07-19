#pragma once
#include <Activity.h>
#include <string>

namespace HelperFuncs {
    struct Time {
        std::string time;
        bool flag;
        int secs;
    };
    struct Name {
        std::string name;
        bool flag;
    };
    struct Date {
        std::string date;
        bool flag;
    };

    // DM
    Name parseNameInput(std::string name, int length);
    Time parseTimeInput(std::string time);
    Date parseDateInput(std::string date);
    bool calcDuration(Activity &act);
    
    std::string secsToTime(int secs);
    std::string secsToDuration(int secs);

    // DB
    std::string convertCharToString(const u_char* s);
    Activity convertRowToAct(int count, char* data[]);
};