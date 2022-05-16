#pragma once
#include <string>
#include <iostream>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include <tuple>
#include <djson/json.hpp>

using std::ifstream;
using std::string;

// bind method to call config from file with given generic
namespace htmlc {

    template <typename T>
    T fromJson(dj::json const& json) {
        return json.as<T>;
    }
}