#ifndef PATH_HPP
#define PATH_HPP

#include <string>

namespace RepoManager
{
    std::string GetHome();
    std::string GetPrefix();
    std::string RepoManagerRoot();
    std::string GetConfig(std::string repo_name);
    std::string GetUser();
    std::string GetProject(std::string repo_name);
    std::string GetSample(std::string prefix);
    std::string GetDist(std::string project, std::string distribution, std::string component, std::string architecture);
    std::string GetPool(std::string project, std::string component, std::string deb_name);
}

#endif