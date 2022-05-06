#include "config.hpp"
using std::filesystem::path;
using std::filesystem::current_path;
using std::ifstream;
using std::vector;

namespace fs = std::filesystem;

string path_to_string(const string& path) {
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
    dj::json conf;
    fs::path p = current_path();
    fs::path c_path = p / "hcl-config.json";
    string c_string = path_to_string(c_path);
    dj::json::result_t res = conf.read(c_string);

    if(!res) {
        throw std::invalid_argument("Config Not Defined");
    }
    htmlc_config config = fromJson<htmlc_config>(conf["config"]);
    std::cout << config.pathRoot << '\n';
}