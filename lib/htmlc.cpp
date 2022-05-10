#include <HTMLC.h>
#include "htmlc.hpp"
#include <fmt/core.h>

namespace htmlc {
    template <typename T>
    T fromJson(dj::json const& json) {
        return json.as<T>;
    }
}

namespace htmlc {
    struct config {
        std::string pathRoot{};
        std::string partials{};
        std::string templates{};
    };

    string valid_config_path(string c_path) {
        if(fs::exists(c_path)) {
            return c_path;
        }
        else {
            throw std::invalid_argument("config path invalid");
        }
    }
    struct info {
        config u_config{};
    };

    template<>
    config fromJson<config>(dj::json const& config) {
        return {config["pathRoot"], config["partials"], config["templates"]};
    }

    template<>
    info fromJson<info>(dj::json const& info) {
        return {fromJson<config>(info["config"])};
    }
    string path_to_string(const string& path) {
        ifstream input_file(path);
        if(!input_file.is_open()) {
            throw std::invalid_argument("config path invalid");
        }
        string json_string = string(std::istreambuf_iterator<char>(input_file), std::istreambuf_iterator<char>());
        input_file.close();
        return json_string;
    }

    
    config find_config(string config_path) {
        fs::path p = valid_config_path(config_path);
        dj::json conf;
        fs::path c_path = p / "htmlc.json";
        string c_string = path_to_string(c_path);
        auto res = conf.read(c_string);
        if(!res) {
            throw std::invalid_argument("config not defined");
        }
        return htmlc::fromJson<config>(conf["config"]);
    }

    // parse a key=value arg from execution context
    tuple<string, string> parse_inline_arg(string keyval) {
        string key = keyval.substr(0, keyval.find("="));
        // add 1 to the size to offset the delim
        string val = keyval.substr(key.size() + 1, keyval.size());
        return make_tuple(key, val);
    }
}

int main(int argc, char *argv[]) {
    if(argc > 1) {
        htmlc::config conf = htmlc::find_config(argv[1]);  
        fmt::print("root: {}\npartials: {}\ntemplates: {}\n", conf.pathRoot, conf.partials, conf.templates);
    }
    else {
        fmt::print("Enter the path of your htmlc config, or submit inline arguments to parse as key value pairs");
    }

    return 0;
}