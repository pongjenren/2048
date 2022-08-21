//homework 5 2048
//main.cpp

#include "curses.h"
#include <iostream>
#include "ui.h"
using namespace std;

int main()
{
    srand((int)time(NULL));
    bool terminate = 0;
    Ui ui;

    while (!terminate) {
        switch (ui.modeChooser()) {
        case 0:
            ui.startNew();
            terminate = 1;
            break;
        case 1:
            ui.loadOld();
            terminate = 1;
            break;
        case 2:
            ui.showGuide();
            terminate = 0;
            break;
        default:
            terminate = 1;
            break;
        }
    }


    endwin();

    return 0;
    
}