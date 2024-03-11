#ifndef   _KAGARI_H_
#define   _KAGARI_H_

#include <string>

#define SOL_ALL_SAFETIES_ON 1
#include "sol/sol.hpp"

class Shiori {
    private:
        sol::state lua_;
        sol::table module_;
    public:
        Shiori() {}
        ~Shiori() {}
        bool load(std::string path);
        bool unload();
        std::string request(std::string request);
};

#endif // _KAGARI_H_
