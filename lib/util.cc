#include <iostream>
#include <string>
#include <tuple>
// #include <format>

using std::string;
using std::cout;
using std::tuple;
using std::make_tuple;
using std::get;

// helper function for quicker prints of short strings
void println(string msg) {
    cout << msg << '\n'; 
}

void print_arg(tuple<string, string> t) {
    println("Key:");
    println(get<0>(t));
    println("Value:");
    println(get<1>(t));
    println("");
}

// parse a key=value arg from execution context
tuple<string, string> parse_inline_arg(string keyval) {
    string key = keyval.substr(0, keyval.find("="));
    // add 1 to the size to offset the delim
    string val = keyval.substr(key.size() + 1, keyval.size());
    return make_tuple(key, val);
}