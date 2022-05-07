#include "config.hh"

namespace fs = std::filesystem;

namespace htmlc {

    std::string read_file_from_path(const fs::path& p) {
        std::ifstream input_file{ p.string() };
        if(!input_file.is_open()) {
            std::cerr << std::format("File \"{}\" not found.\n", p.filename().string());
            std::exit(EXIT_FAILURE);
        }
        return { std::istreambuf_iterator<char>(input_file), std::istreambuf_iterator<char>() };
    }

    void check_path(std::string_view path) {
        if(!fs::exists(path))
            throw std::invalid_argument("config path invalid");
    }

    config find_config(const std::string& config_path) {
        check_path(config_path);
        fs::path config_json_path { config_path + "/htmlc.json"};
        dj::json config_json;
        if(!config_json.read(read_file_from_path(config_json_path))) {
            throw std::runtime_error{ "config not defined" };
        }
        return fromJson<config>(config_json["config"]);
    }
}