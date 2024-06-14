#ifndef COLORS_HPP
#define COLORS_HPP

#define RESET "\033[0m"
#define FGRED "\033[31m"
#define FGGRN "\033[32m"
#define FGYEL "\033[33m"
#define FGBLU "\033[34m"
#define FGMAG "\033[35m"
#define FGCYN "\033[36m"

#define BGRED "\033[41m"
#define BGGRN "\033[42m"
#define BGYEL "\033[43m"
#define BGBLU "\033[44m"
#define BGMAG "\033[45m"
#define BGCYN "\033[46m"

#include <string>

namespace RepoMaster
{
    void cprint(const char* color, const char* text, const char* typ);
}

#endif