#ifndef DEBIAN_HPP
#define DEBIAN_HPP

#include <string>
#include <map>

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
}

#endif