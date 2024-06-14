#include "styles.hpp"
#include <iostream>

namespace RepoManager {
    void sprint(std::string style, std::string text) {
        if (style == "bold") {
            std::cout << BOLD << text << RESET << std::endl;
        } else if (style == "italic") {
            std::cout << ITALIC << text << RESET << std::endl;
        } else if (style == "underline") {
            std::cout << UNDERLINE << text << RESET << std::endl;
        } else if (style == "blink") {
            std::cout << BLINK << text << RESET << std::endl;
        } else if (style == "blink2") {
            std::cout << BLINK2 << text << RESET << std::endl;
        } else if (style == "reverse") {
            std::cout << REVERSE << text << RESET << std::endl;
        } else if (style == "concealed") {
            std::cout << CONCEALED << text << RESET << std::endl;
        } else if (style == "crossed") {
            std::cout << CROSSED << text << RESET << std::endl;
        } else {
            std::cout << text << std::endl;
        }
    }
}