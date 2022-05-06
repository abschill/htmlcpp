#include <iostream>
#include <filesystem>
#include "HTMLC.in.h"
#include <dumb_json/json.hpp>

using std::filesystem::path;
using std::filesystem::current_path;

void find_config() {
    path p = current_path();
    std::cout << "Config module (wip)\n";
    std::cout << "Current Path: " << p << '\n';
    return;
}