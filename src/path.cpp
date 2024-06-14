#include "path.hpp"
#include <cstdlib>
#include <string>
#include <stdexcept>  // Für std::runtime_error

namespace RepoManager
{
    std::string GetHome()
    {
        const char* home_cstr = getenv("HOME");
        if (home_cstr) {
            return std::string(home_cstr);
        } else {
            throw std::runtime_error("HOME environment variable is not set");
        }
    }
    std::string GetPrefix()
    {
        const char* prefix_cstr = getenv("PREFIX");
        if (prefix_cstr) {
            return std::string(prefix_cstr);
        } else {
            return std::string("/usr/local");
        }
    }
}