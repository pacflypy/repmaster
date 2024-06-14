#include "debian.hpp"
#include "exception.hpp"
#include <fstream>
#include <sstream>
#include <vector>

void RepoManager::Control::read(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw PathNotFoundError("Failed to open file");
    }

    std::string line;
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, ':') && std::getline(iss, value)) {
            if (!value.empty() && value[0] == ' ') {
                value.erase(0, 1);
            }
            data[key] = value;
        } 
    }
    file.close();
}

bool RepoManager::Control::validate() const {
    const std::vector<std::string> requiredKeys = {"Package", "Version", "Section", "Priority", "Architecture", "Maintainer", "Description"};
    const std::vector<std::string> optionalKeys = {"Depends", "Recommends", "Suggests", "Conflicts", "Breaks", "Provides", "Replaces", "Installed-Size", "MD5sum", "SHA256", "Files"};

    for (const auto& key : requiredKeys) {
        if (data.find(key) == data.end()) {
            throw ControlFileError("Required Key Not Found: " + key);
        }
    }
    return true;
}

std::string RepoManager::Control::get(const std::string& key) const {
    auto it = data.find(key);
    if (it == data.end()) {
        throw ControlFileError("Key Not Found: " + key);
    }
    return it->second;
}