#pragma once
#include <string>
using std::string;

// ast to integrate with parser for the configured files

namespace htmlc_ast {
    const string assign = "=";
    const string open_scope = "<!--@";
    const string close_scope = "@htmlc-->";

    string to_directive(string directive, string key) {
        return open_scope + directive + assign + key + close_scope;
    }
}