#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <stdexcept>
#include <string>

class ControlFileError : public std::runtime_error {
    public:
        explicit ControlFileError(const std::string& message);
};

class ReleaseFileError : public std::runtime_error {
    public:
        explicit ReleaseFileError(const std::string& message);
};

class DebianPackageInvalidError : public std::runtime_error {
    public:
        explicit DebianPackageInvalidError(const std::string& message);
};

class PathNotFoundError : public std::runtime_error {
    public:
        explicit PathNotFoundError(const std::string& message);
};

#endif