#ifndef DEBIAN_HPP
#define DEBIAN_HPP

#include <string>
#include <map>
#include <filesystem>


namespace RepoManager
{
    class Control
    {
        private:
            std::map<std::string, std::string> data;
        
        public:
            void read(const std::string& filepath); /* For read the control file data */
            bool validate() const; /* For Validate the Control Fiel content */
            std::string get(const std::string& key) const; /* For get the Value from a Key*/
    };
    class Release
    {
        private:
            std::map<std::string, std::string> data;
            std::string filepath;
        public:
            Release(const std::string& path);

            void NewRelease();
            void append(const std::string& key, const std::string& value);
            void remove(const std::string& key);
            void sign(const std::string& PrivateKeyPath);
            std::string get(const std::string& key) const;
            void save();
    };
    class DebPackage
    {
        private:
            std::string filepath;
            std::filesystem::path tempDir;
            std::filesystem::path control;
        public:
            DebPackage(const std::string& deb_path); /* Konstruktor */
            ~DebPackage(); /* Destruktor */

            void open();
            void check();
            void read();
            void ValidateControl();
            std::string GetControlData(const std::string& key) const;
            void close();
    };
}

#endif