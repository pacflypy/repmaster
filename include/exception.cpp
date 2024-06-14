#include "exception.hpp"

ControlFileError::ControlFileError(const std::string& message) : std::runtime_error("Control File Error: " + message) {}

ReleaseFileError::ReleaseFileError(const std::string& message) : std::runtime_error("Release File Error: " + message) {}

DebianPackageInvalidError::DebianPackageInvalidError(const std::string& message) : std::runtime_error("Debian Package Invalid: " + message) {}

PathNotFoundError::PathNotFoundError(const std::string& message) : std::runtime_error("Path Not Found: " + message) {}