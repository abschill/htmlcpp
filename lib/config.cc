#include <iostream>
#include <filesystem>
#include "HTMLC.in.h"


using std::filesystem::path;
using std::filesystem::current_path;

void find_config() {
    std::cout << "Config module (wip)\n";
    std::cout << "Current Path: " << current_path() << '\n';
    return;
}