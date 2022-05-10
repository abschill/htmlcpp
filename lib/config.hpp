#include <string>
#include <iostream>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <djson/json.hpp>

using std::filesystem::path;
using std::filesystem::current_path;
using std::ifstream;
using std::vector;
using std::string;

struct htmlc_config {
    std::string pathRoot;
    std::string partials;
    std::string templates;
};

template <typename T, typename U>
struct Converter {
    T operator()(T const&) const;
    U operator()(U const&) const;
};

template <typename T>
struct Jsonify;

template <typename T>
    requires dj::Element<T>
struct Jsonify<T>: Converter<T, dj::json> {
    dj::json operator()(T const& t) const { return dj::json(t); }
    T operator()(dj::json const& json) const { return json.as<T>(); }
};  

template <typename T>
T fromJson(dj::json const& t) {
    return Jsonify<T>{}(t);
}

template<>
struct Jsonify<htmlc_config> {
    htmlc_config operator()(dj::json const& json) const {
        return {
            .pathRoot = json["pathRoot"],
            .partials = json["partials"],
            .templates = json["templates"]
        };
    }
};