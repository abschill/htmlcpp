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
namespace htmlc_config {
    typedef struct {
        string chunk_name;
        string chunk_path;
        string chunk_raw;
        bool is_static;
    } Chunk;

    typedef struct {
        std::vector<Chunk> resolved_chunks;
        std::vector<Chunk> resolved_pages;
    } Chunkmap;

    struct OutputOptions {
        string dir;
    };

    struct Config {
        string root{}; // root path relative to <cwd>
        string chunks{}; //partial root relative to <cwd>/<pathRoot>
        string pages{}; //template root relative to <cwd>/<pathRoot>
        bool dry; //whether or not to compile the HTML or just test for any errors in the compilation process
        bool silent_errors; //if true, try to push through any compilation errors without resolving the error.
    };

    struct HTMLCFileData {
        Config config{};
        OutputOptions output{};
    };

    template <typename T>
    T fromJson(dj::json const& json) {
        return json.as<T>;
    }
}
