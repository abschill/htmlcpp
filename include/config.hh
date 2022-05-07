#pragma once
#include <string>
#include <version>
#include <string_view>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <format>
#include <dumb_json/json.hpp>

namespace htmlc {
    struct config {
        std::string pathRoot, partials, templates;
    };

    template <typename T, typename U>
    struct Converter {
        T operator()(T const&) const;
        U operator()(U const&) const;
    };

    template <typename T>
    struct Jsonify;

    template <typename T>
        requires dj::json::is_settable<T>
    struct Jsonify<T>: Converter<T, dj::json> {
        dj::json operator()(T const& t) const { return dj::json(t); }
        T operator()(dj::json const& json) const { return json.as<T>(); }
    };  

    template <typename T>
    T fromJson(dj::json const& t) {
        return Jsonify<T>{}(t);
    }

    template<>
    struct Jsonify<config> {
        config operator()(dj::json const& json) const {
            return {
                .pathRoot = json["pathRoot"].as<std::string>(),
                .partials = json["partials"].as<std::string>(),
                .templates = json["templates"].as<std::string>()
            };
        }
    };

    std::string read_file_from_path(const std::filesystem::path& p);
    void check_path(std::string_view c_path);
    config find_config(const std::string& config_path);
}