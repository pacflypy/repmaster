#ifndef STYLES_HPP
#define STYLES_HPP

#define RESET "\033[0m"
#define BOLD "\033[1m"
#define FAINT "\033[2m"
#define ITALIC "\033[3m"
#define UNDERLINE "\033[4m"
#define BLINK "\033[5m"
#define BLINK2 "\033[6m"
#define REVERSE "\033[7m"
#define CONCEALED "\033[8m"
#define CROSSED "\033[9m"

#include <string>

namespace RepoMaster
{
    void sprint(std::string style, std::string text);
}

#endif