#pragma once
#include <string>

struct Activity {
    std::string name;
    std::string time_start;
    std::string time_end;
    std::string duration;
    std::string date;
    int secs_start;
    int secs_end;
    int secs_duration;
};

struct DBActivity : Activity {
    std::string name;
    std::string time_start;
    std::string time_end;
    std::string duration;
    std::string date;
};