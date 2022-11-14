#include "kagari.h"

#include <iostream>
#include <string>

#define SOL_ALL_SAFETIES_ON 1
#include "sol/sol.hpp"

#if defined(_WIN32)
const char *kDirSep = "\\";
const char *kExt        = "dll";
#elif defined(__linux__)
const char *kDirSep = "/";
const char *kExt        = "so";
#else
#error "Not Supported"
#endif // OS

const char *kCraftMan = "Tatakinov";
const char *kCRLF = "\x0d\x0a";

static sol::state lua;
static sol::table module;

bool __load(std::string path) {
    bool ret    = false;
    lua.open_libraries(
        sol::lib::base,
        sol::lib::package,
        sol::lib::coroutine,
        sol::lib::string,
        sol::lib::os,
        sol::lib::table,
        sol::lib::math,
        sol::lib::io,
        sol::lib::debug
    );
    std::string package_path    = lua["package"]["path"];
    package_path    = path + "?.lua;"
        + path + "?" + kDirSep + "init.lua;"
        + path + "corelib" + kDirSep + "?.lua;"
        + path + "corelib" + kDirSep + "?" + kDirSep + "init.lua;"
        + path + "lib" + kDirSep + "?.lua;"
        + path + "lib" + kDirSep + "?" + kDirSep + "init.lua";
    std::string package_cpath    = lua["package"]["cpath"];
    package_cpath = path + "?." + kExt + ";"
        + path + "?" + kDirSep + "init." + kExt + ";"
        + path + "corelib" + kDirSep + "?." + kExt + ";"
        + path + "corelib" + kDirSep + "?" + kDirSep + "init." + kExt + ";"
        + path + "lib" + kDirSep + "?." + kExt + ";"
        + path + "lib" + kDirSep + "?" + kDirSep + "init." + kExt;
    lua["package"]["path"]    = package_path;
    lua["package"]["cpath"] = package_cpath;
    try {
        auto result = lua.safe_script_file(path + "index.lua");
        if (result.valid()) {
            module    = result;
        }
        else {
            sol::error err  = result;
            std::cout << "Error(load script file)" << err.what() << std::endl;
            return false;
        }
    }
    catch(std::exception &e) {
            std::cout << "Error(load script file): " << e.what() << std::endl;
            return false;
    }
    catch(...) {
            std::cout << "Error(load script file)" << std::endl;
            return false;
    }
    sol::protected_function pf    = module["load"];
    auto result = pf(path);
    if (result.valid()) {
        ret = result;
    }
    else {
        sol::error err    = result;
        std::cout << "Error(load): " << err.what() << std::endl;
    }
    return ret;
}

bool __unload() {
    bool ret    = false;
    sol::protected_function pf    = module["unload"];
    auto result = pf();
    if (result.valid()) {
        ret = result;
    }
    else {
        sol::error err    = result;
        std::cout << "Error(unload): " << err.what() << std::endl;
    }
    return ret;
}

std::string __request(std::string request) {
    using namespace std::literals::string_literals;
    std::string ret;
    sol::protected_function pf    = module["request"];
    auto result = pf(request);
    if (result.valid()) {
        ret = result;
    }
    else {
        sol::error err    = result;
        std::cout << "Error(request): " << err.what() << std::endl;
        ret = "SHIORI/3.0 500 Internal Server Error"s + kCRLF +
                    "Sender: " + kCraftMan + kCRLF +
                    "Charset: UTF-8" + kCRLF +
                    kCRLF;
    }
    return ret;
}
