#include "config.hpp"
namespace fs = std::filesystem;
const string path_to_string(const string& path) {
    ifstream input_file(path);
    if(!input_file.is_open()) {
        std::cerr << "could Not Open File -" << path << "'" << std::endl;
        exit(EXIT_FAILURE);
    }
    string json_string = string(std::istreambuf_iterator<char>(input_file), std::istreambuf_iterator<char>());
    input_file.close();
    return json_string;
}

const string valid_config_path(string c_path) {
    if(fs::exists(c_path)) {
        return c_path;
    }
    else {
        throw std::invalid_argument("config path invalid");
    }
}

const htmlc_config find_config(string config_path) {
    fs::path p = valid_config_path(config_path);
    dj::json conf;
    fs::path c_path = p / "hcl-config.json";
    string c_string = path_to_string(c_path);
    dj::json::result_t res = conf.read(c_string);
    if(!res) {
        throw std::invalid_argument("config not defined");
    }
    return fromJson<htmlc_config>(conf["config"]);
}