#pragma once
#include <Activity.h>

class DisplayManager {
    private:
        std::string line = "---------------------------";
        int spaces = line.length()-2;
        void drawHorLine();
        void drawVertLine();
        void drawMultiLine(int n);
        void drawTop(int n);
        void drawBot(int n);
        void drawEven(int offset, std::string input);
        void drawOdd(int offset, std::string input);
        void drawInput(std::string input);
        void displayAct(Activity &act);
    public:
        void drawTable(Activity &act);
        void congrats();
        Activity takeInput();
};