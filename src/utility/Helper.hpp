//
// Created by Dominik on 1/16/2021.
//

#ifndef AGEOFWAR_HELPER_HPP
#define AGEOFWAR_HELPER_HPP

#include <string>
#include <iostream>
#include <chrono>
#include <thread>
//Codes from https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
//        and https://stackoverflow.com/a/35190285/13251554

//Colors
#define BLACK 30
#define RED 31
#define GREEN 32
#define YELLOW 33
#define BLUE 34
#define MAGENTA 35
#define CYAN 36
#define WHITE 37
#define BRIGHTBLACK 90
#define BRIGHTRED 91
#define BRIGHTGREEN 92
#define BRIGHTYELLOW 93
#define BRIGHTBLUE 94
#define BRIGHTMAGENTA 95
#define BRIGHTCYAN 96
#define BRIGHTWHITE 97

//Utility
#define RESET 0
#define BOLD 1
#define BOLDOFF 21
#define UNDERLINE 4
#define UNDERLINEOFF 24
#define BLINK 5
#define BLINKOFF 25


class Helper {
public:
    static std::string getColorString(int colorCode) {
        std::string output = "\033[";
        output += std::to_string(colorCode);
        output += "m";
        return output;
    }

    static void setColor(int colorCode){
        std::cout << getColorString(colorCode);
    }

    static std::string getBGString(int colorCode){
        return getColorString(colorCode + 10);
    }

    static void setBG(int colorCode){
        std::cout << getBGString(colorCode);
    }

    static void eraseLine(){
        std::cout << "\33[2K";
    }

    static void clearScreen(){
        std::cout << "\033[2j";
    }

    static void moveCursorUp(){
        std::cout << "\033[A";
    }

    static void erasePreviousLine(){
        moveCursorUp();
        eraseLine();
    }

    static void moveToLineStart(){
        std::cout << "\r";
    }

    static void moveToScreenStart(){
        std::cout << "\033[1;1H";
    }

    static void Sleep(int miliseconds){
        std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds));
    }
};


#endif //AGEOFWAR_HELPER_HPP
