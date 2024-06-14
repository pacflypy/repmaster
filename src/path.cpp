#include "path.hpp"
#include <cstdlib>
#include <string>
#include <stdexcept>  // Für std::runtime_error
#include <filesystem>

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
    std::string RepoManagerRoot()
    {
        std::filesystem::path prefix = GetPrefix();
        std::filesystem::path etc = "etc/repo-manager/root";
        std::filesystem::path repo_manager_root = prefix / etc;
        return repo_manager_root.string();
    }
    std::string GetConfig(std::string repo_name)
    {
        std::filesystem::path repo_manager_root = RepoManagerRoot();
        std::filesystem::path repo = repo_name + ".conf";
        std::filesystem::path config = repo_manager_root / repo;
        return config.string();
    }
    std::string GetUser()
    {
        const char* user_cstr = getenv("USER");
        if (user_cstr) {
            return std::string(user_cstr);
        } else {
            return std::string("root");
        }
    }
    std::string GetProject(std::string repo_name)
    {
        std::filesystem::path root = RepoManagerRoot();
        std::filesystem::path repo = repo_name;
        std::filesystem::path project = root / repo;
        return project.string();
    }
    std::string GetSample(std::string prefix)
    {
        std::filesystem::path prefix = prefix;
        std::filesystem::path path_to = "etc/repo-manager/sample";
        std::filesystem::path sample = prefix / path_to;
        return sample.string();
    }
    std::string GetDist(std::string project, std::string distribution, std::string component, std::string architecture)
    {
        std::filesystem::path project = GetProject(project);
        std::filesystem::path dist = std::string("dists");
        std::filesystem::path arch = std::string("binary-") + architecture;
        std::filesystem::path full_path = project / dist / distribution / component / arch;
        return full_path.string();
    }
}