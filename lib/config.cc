#include <iostream>
#include <filesystem>
#include "HTMLC.in.h"
#include <iostream>
#include <fstream>
#include <dumb_json/json.hpp>
#include <filesystem>
#include "config.hpp"
using std::filesystem::path;
using std::filesystem::current_path;
using std::ifstream;
dj::json json;
namespace fs = std::filesystem;

string file_to_string(const string& path) {
    ifstream input_file(path);
    if(!input_file.is_open()) {
        std::cerr << "Could Not Open File -" << path << "'" << std::endl;
        exit(EXIT_FAILURE);
    }
    string json_string = string(std::istreambuf_iterator<char>(input_file), std::istreambuf_iterator<char>());
    input_file.close();
    return json_string;
}

void find_config(string config_path) {
    //todo - config path setup
    fs::path p = current_path();
    fs::path config_file = p / "hcl-config.json";
    string json_string = file_to_string(config_file);
    dj::json::result_t res = json.read(json_string);

    if(!res) {
        throw std::invalid_argument("Config Not Defined");
    }

    htmlc_config ssr_options = json["config"].as<htmlc_config>();
    std::cout << ssr_options.pathRoot << '\n';
}