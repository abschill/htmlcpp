#pragma once
#include "config.hpp"
namespace htmlc_config {

    template<>
    Config fromJson<Config>(dj::json const& config) {
        return {config["root"], config["chunks"], config["pages"]};
    }
	string file_to_string(string path) {
        ifstream input_file(path);
        if(!input_file.is_open()) {
            throw std::invalid_argument("config path invalid");
        }
        string json_string = string(std::istreambuf_iterator<char>(input_file), std::istreambuf_iterator<char>());
        input_file.close();
        return json_string;
    }

    fs::path append_paths(string p0, string p1) {
        return fmt::format("{}/{}", p0, p1);
    }
    // print key with correct format color
    void print_config_key(string val) {
        fmt::print(fg(fmt::color::gold), "\t{}: ", val);
    }

    // print value with correct format color and suffix for stdout
    void print_config_val(string val) {
        fmt::print(fg(fmt::color::alice_blue), "{};\n", val);
    }

    // abstract each entry into one line for printing
    void print_config_entry(string key, string val) {
        print_config_key(key);
        print_config_val(val);
    }

    string valid_cpath(string c_path) {
        return fs::exists(c_path) ? c_path:
        throw std::invalid_argument("config path invalid");
    }

    bool target_isvalid(string c_path) {
        bool is_html = (bool)(c_path.find(".html", 0) != -1);
        bool is_htmlc = (bool)(c_path.find(".htmlc", 0) != -1);
        return (is_html || is_htmlc);
    }
    Config find_config(string config_path) {
        fs::path p = valid_cpath(config_path);
        dj::json conf;
        fs::path c_path = p / "htmlc.json";
        string c_string = file_to_string(c_path);
        auto res = conf.read(c_string);
        return res ? htmlc_config::fromJson<Config>(conf["config"]):
        throw std::invalid_argument("htmlc.json not defined");
    }

    void print_config(htmlc_config::Config conf) {
        fmt::print(fg(fmt::color::green),"resolved config: \n");
        fmt::print("{{\n");
        print_config_entry("root", conf.root);
        print_config_entry("chunks", conf.chunks);
        print_config_entry("pages", conf.pages);
        print_config_entry("dry", conf.dry ? "true" : "false");
        print_config_entry("silent_errors", conf.silent_errors ? "true" : "false");
        fmt::print("}}\n");
    }

    // return a string with any error from validating the config, so if there is an issue the top level process can format the string in the error msg
    string validate_config(htmlc_config::Config conf) {
        if(conf.silent_errors) {
            return "";
        }

        if(!fs::exists(conf.root)) {
            return "path root";
        }

        if(!fs::exists(append_paths(conf.root, conf.chunks))) {
            return "<pathRoot>/partials";
        }

        if(!fs::exists(append_paths(conf.root, conf.pages))) {
            return "<pathRoot>/templates";
        }

        return "";
    }

    htmlc_config::Chunkmap get_chunkmap(htmlc_config::Config conf) {
        std::vector<htmlc_config::Chunk> resolved_chunks = {};
        std::vector<htmlc_config::Chunk> resolved_pages = {};
        std::string root = conf.root;
        std::string chunks = root + "/" + conf.chunks;
        std::string pages = root + "/" + conf.pages;

        for (const auto & entry : fs::directory_iterator(chunks)) {
            string c_path = entry.path();
            bool is_valid = target_isvalid(c_path);
            if(is_valid) {
                string f_contents = file_to_string(c_path);
                resolved_chunks.push_back(htmlc_config::Chunk{
                    .chunk_name = c_path,
                    .chunk_path = c_path,
                    .chunk_raw = f_contents,
                    .is_static = htmlc_parser::is_static(f_contents)
                });
            }
        }
        for (const auto & entry : fs::directory_iterator(pages)) {
            string c_path = entry.path();
            bool is_valid = target_isvalid(c_path);
            if(is_valid) {
                string f_contents = file_to_string(c_path);
                resolved_pages.push_back(htmlc_config::Chunk{
                    .chunk_name = c_path,
                    .chunk_path = c_path,
                    .chunk_raw = f_contents,
                    .is_static = htmlc_parser::is_static(f_contents)
                });
            }
        }
        return htmlc_config::Chunkmap{ resolved_chunks, resolved_pages };
    };

    void print_chunkmap(htmlc_config::Config conf) {
        std::string root = conf.root;
        std::string chunks = root + "/" + conf.chunks;
        std::string pages = root + "/" + conf.pages;

        for (const auto & entry : fs::directory_iterator(chunks)) {
            string c_path = entry.path();
            bool is_valid = target_isvalid(c_path);
            if(is_valid) fmt::print(fg(fmt::color::sea_green), "Chunk:\n{}\n", c_path);
        }
        for (const auto & entry : fs::directory_iterator(pages)) {
            string c_path = entry.path();
            bool is_valid = target_isvalid(c_path);
            if(is_valid) {
                fmt::print(fg(fmt::color::sea_green), "Page: \n{}\n", c_path);
                fmt::print("Content: \n{}\n", file_to_string(c_path));
            }
        }
    }
}
