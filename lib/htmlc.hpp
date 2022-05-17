#pragma once
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <tuple>
#include <djson/json.hpp>
#include "fmt/format.h"
#include <fmt/core.h>
#include <fmt/color.h>
#include "parser.cpp"
#include <regex.h>

namespace fs = std::filesystem;
using std::ifstream;
using std::string;
// bind method to call config from file with given generic
namespace htmlc {
    typedef struct {
        std::string chunk_name;
        std::string chunk_path;
        std::string chunk_raw;
        bool is_static;
    } chunk;

    typedef struct {
        std::vector<chunk> resolved_chunks;
        std::vector<chunk> resolved_pages;
    } chunkmap;

    struct config {
        std::string root{}; // root path relative to <cwd>
        std::string chunks{}; //partial root relative to <cwd>/<pathRoot>
        std::string pages{}; //template root relative to <cwd>/<pathRoot>
        bool dry; //whether or not to compile the HTML or just test for any errors in the compilation process
        bool silent_errors; //if true, try to push through any compilation errors without resolving the error.
    };
  
    template <typename T>
    T fromJson(dj::json const& json) {
        return json.as<T>;
    }
}

// internals for root lib namespace (logging, validation, etc)
namespace htmlc_i {

    string file_to_string(const string& path) {
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
}
