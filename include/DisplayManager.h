#pragma once
#include <Activity.h>

class DisplayManager {
    private:
        std::string line = "-------------------------------------";
        std::string vert = "\033[35m|\033[0m";
        std::string reset = "\033[0m";
        int spaces = line.length()-2;
        void drawHorLine();
        void drawVertLine();
        void drawMultiLine(int n);
        void drawTop(int n);
        void drawBot(int n);
        void drawEven(int offset, std::string input, std::string color);
        void drawOdd(int offset, std::string input, std::string color);
        void drawInput(std::string input, std::string color);
        void displayAct(Activity &act);

    public:
        void drawActTable(Activity &act);
        void drawMenu();
        void congrats();

        // user input
        Activity takeInput();
        std::string getName();
        int getInt(std::string prompt);

};