#include "colors.hpp"
#include <iostream>

namespace RepoManager
{
    void cprint(const char* color, const char* text, const char* typ)
    {
        /* Hier muessen wir nun die Farben aus der colors.h verwende und diesen anhand des types sortieren
        Dabei sind als typ lediglich foreground und background erlaubt
        Der rest wird dann bezogen und angegeben
        */
       if (typ == "foreground") {
        if (color == "red") {
            const char* color = FGRED;
        } else if (color == "green") {
            const char* color = FGGRN;
        } else if (color == "yellow") {
            const char* color = FGYEL;
        } else if (color == "blue") {
            const char* color = FGBLU;
        } else if (color == "magenta") {
            const char* color = FGMAG;
        } else if (color == "cyan") {
            const char* color = FGCYN;
        } else if (color == "reset" || color == "white") {
            const char* color = RESET;
        } else {
            throw std::invalid_argument("Invalid Color");
        }
        std::cout << color << text << RESET << std::endl;
        } else if (typ == "background") {
            if (color == "red") {
                const char* color = BGRED;
            } else if (color == "green") {
                const char* color = BGGRN;
            } else if (color == "yellow") {
                const char* color = BGYEL;
            } else if (color == "blue") {
                const char* color = BGBLU;
            } else if (color == "magenta") {
                const char* color = BGMAG;
            } else if (color == "cyan") {
                const char* color = BGCYN;
            } else if (color == "reset" || color == "white") {
                const char* color = RESET;
            } else {
                throw std::invalid_argument("Invalid Color");
            }
            std::cout << color << text << RESET << std::endl;
        } else {
            std::cout << text << std::endl;
        }
    }
}