#pragma once
#include <string>
#include <fmt/core.h>
#include "fmt/format.h"
using std::string;
// ast to integrate with parser for the configured files

namespace htmlc_parser {
    const string assign = "=";
    const string open_scope = "<!--@";
    const string close_scope = "@htmlc-->";
    string to_directive(string directive, string key) {
        return open_scope + directive + assign + key + close_scope;
    }
}