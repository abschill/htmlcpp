#include <iostream>
#include <string>
#include <tuple>
using std::string;
using std::tuple;
using std::make_tuple;

// parse a key=value arg from execution context
tuple<string, string> parse_inline_arg(string keyval) {
    string key = keyval.substr(0, keyval.find("="));
    // add 1 to the size to offset the delim
    string val = keyval.substr(key.size() + 1, keyval.size());
    return make_tuple(key, val);
}