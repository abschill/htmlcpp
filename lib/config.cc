#include <iostream>
#include <filesystem>
#include "HTMLC.in.h"
#include <iostream>
#include <fstream>
#include <dumb_json/json.hpp>
#include <string>
#include <filesystem>

using std::filesystem::path;
using std::filesystem::current_path;
using std::ifstream;
using std::string;

dj::json json;
namespace fs = std::filesystem;

string file_to_string(const string& path) {
    ifstream input_file(path);
    if(!input_file.is_open()) {
        std::cerr << "Could Not Open File -" << path << "'" << std::endl;
        exit(EXIT_FAILURE);
    }
    return string(std::istreambuf_iterator<char>(input_file), std::istreambuf_iterator<char>());
}

void find_config() {
    ifstream config_string;
    fs::path p = current_path();
    fs::path config_file = p / "hcl-config.json";

    string s = file_to_string(config_file);
    std::cout << "Config module (wip)\n";
    std::cout << s << '\n';
    if(json.read(s)) {
        dj::object_t ssr_opts = json["ssr_config"].as<dj::object_t>();
    }
    return;
}