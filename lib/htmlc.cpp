#include <HTMLC.h>
#include "fmt/format.h"
#include "htmlc.hpp"
#include <fmt/core.h>
#include <filesystem>

using std::tuple;
using std::make_tuple;

namespace fs = std::filesystem;

// bind method to call config from file with given generic
namespace htmlc {

    template <typename T>
    T fromJson(dj::json const& json) {
        return json.as<T>;
    }
}

// root namespace to implement 
namespace htmlc {

    struct config {
        std::string pathRoot{}; // root path relative to <cwd>
        std::string partials{}; //partial root relative to <cwd>/<pathRoot>
        std::string templates{}; //template root relative to <cwd>/<pathRoot>
        bool dry;
        bool silent_errors;
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
            throw std::invalid_argument("htmlc.json not defined");
        }
        return htmlc::fromJson<config>(conf["config"]);
    }

    void print_config(htmlc::config conf) {
        fmt::print("root: {}\npartials: {}\ntemplates: {}\ndry: {}\nsilent_errors: {}\n", 
        conf.pathRoot, conf.partials, conf.templates, conf.dry, conf.silent_errors);
    }

    fs::path append_paths(string p0, string p1) {
        return fmt::format("{}/{}", p0, p1);
    }

    string validate_config(htmlc::config conf) {
        // todo - add checks after the silence to see if its actually valid or not 
        // for now this is just seeing if they turn off errors as the only condition
        if(conf.silent_errors) {
            return "";
        }
        
        if(!fs::exists(conf.pathRoot)) {
            return "path root";
        }

        if(!fs::exists(htmlc::append_paths(conf.pathRoot, conf.partials))) {
            return "<pathRoot>/partials";
        }

        if(!fs::exists(htmlc::append_paths(conf.pathRoot, conf.templates))) {
            return "<pathRoot>/templates";
        }

        return "";
    }
}

int main(int argc, char *argv[]) {
    if(argc > 1) {
        htmlc::config conf = htmlc::find_config(argv[1]);  
        htmlc::print_config(conf);
        string config_err = htmlc::validate_config(conf);

        if(config_err != "") {
            fmt::print("error: {}\n exit code: 1\n", config_err);
            return 1;
        }
    }
    else {
        fmt::print("Enter the path of your htmlc config, or submit inline arguments to parse as key value pairs\nexit code: 1\n");
        return 1;
    }

    return 0;
}