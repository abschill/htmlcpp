#include <iostream>
#include <string>

// helper function for quicker prints of short strings
void println(std::string msg) {
    std::cout << msg << '\n'; 
}

// parse a key=value arg from execution context
void parse_prog_arg(std::string keyval) {
    std::string key = keyval.substr(0, keyval.find("="));
    println("Key:");
    println(key);
    // add 1 to the size to offset the delim
    std::string val = keyval.substr(key.size() + 1, keyval.size());
    println("Value:");
    println(val);
}