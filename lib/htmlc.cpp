#include <HTMLC.h>
#include "htmlc.hpp"

// root namespace
namespace htmlc {

    struct info {
        config u_config{};
    };

    template<>
    config fromJson<config>(dj::json const& config) {
        return {config["root"], config["chunks"], config["pages"]};
    }

    template<>
    info fromJson<info>(dj::json const& info) {
        return {fromJson<config>(info["config"])};
    }

    config find_config(string config_path) {
        fs::path p = internals::valid_cpath(config_path);
        dj::json conf;
        fs::path c_path = p / "htmlc.json";
        string c_string = internals::file_to_string(c_path);
        auto res = conf.read(c_string);
        return res ? htmlc::fromJson<config>(conf["config"]):
        throw std::invalid_argument("htmlc.json not defined");
    }

    void print_config(htmlc::config conf) {
        fmt::print(fg(fmt::color::green),"resolved config: \n");
        fmt::print("{{\n");
        internals::print_config_entry("root", conf.root);
        internals::print_config_entry("chunks", conf.chunks);
        internals::print_config_entry("pages", conf.pages);
        internals::print_config_entry("dry", conf.dry ? "true" : "false");
        internals::print_config_entry("silent_errors", conf.silent_errors ? "true" : "false");
        fmt::print("}}\n");
    }

    // return a string with any error from validating the config, so if there is an issue the top level process can format the string in the error msg
    string validate_config(htmlc::config conf) {
        if(conf.silent_errors) {
            return "";
        }

        if(!fs::exists(conf.root)) {
            return "path root";
        }

        if(!fs::exists(internals::append_paths(conf.root, conf.chunks))) {
            return "<pathRoot>/partials";
        }

        if(!fs::exists(internals::append_paths(conf.root, conf.pages))) {
            return "<pathRoot>/templates";
        }

        return "";
    }

    void print_chunkmap(htmlc::config conf) {
        std::string root = conf.root;
        std::string chunks = root + "/" + conf.chunks;
        std::string pages = root + "/" + conf.pages;

        for (const auto & entry : fs::directory_iterator(chunks)) {
            string c_path = entry.path();
            bool is_valid = internals::target_isvalid(c_path);
            if(is_valid) fmt::print(fg(fmt::color::sea_green), "Chunk:\n{}\n", c_path);
        }
        for (const auto & entry : fs::directory_iterator(pages)) {
            string c_path = entry.path();
            bool is_valid = internals::target_isvalid(c_path);
            if(is_valid) fmt::print(fg(fmt::color::sea_green), "Page: \n{}\n", c_path);
        }
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
        htmlc::print_chunkmap(conf);
    }
    else {
        fmt::print("Enter the path of your htmlc config, or submit inline arguments to parse as key value pairs\nexit code: 1\n");
        return 1;
    }

    return 0;
}