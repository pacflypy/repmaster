#include "colors.hpp"
#include <iostream>

namespace RepoManager
{
    void cprint(std::string color, std::string text, std::string typ)
    {
        const char* color_code = nullptr;
        if (typ == "foreground") {
            if (color == "red") {
                color_code = FGRED;
            } else if (color == "green") {
                color_code = FGGRN;
            } else if (color == "yellow") {
                color_code = FGYEL;
            } else if (color == "blue") {
                color_code = FGBLU;
            } else if (color == "magenta") {
                color_code = FGMAG;
            } else if (color == "cyan") {
                color_code = FGCYN;
            } else if (color == "reset" || color == "white") {
                color_code = RESET;
            } else {
                throw std::invalid_argument("Invalid Color");
            }
            std::cout << color_code << text << RESET << std::endl;
        } else if (typ == "background") {
            if (color == "red") {
                color_code = BGRED;
            } else if (color == "green") {
                color_code = BGGRN;
            } else if (color == "yellow") {
                color_code = BGYEL;
            } else if (color == "blue") {
                color_code = BGBLU;
            } else if (color == "magenta") {
                color_code = BGMAG;
            } else if (color == "cyan") {
                color_code = BGCYN;
            } else if (color == "reset" || color == "white") {
                color_code = RESET;
            } else {
                throw std::invalid_argument("Invalid Color");
            }
            std::cout << color_code << text << RESET << std::endl;
        } else {
            std::cout << text << std::endl;
        }
    }
}