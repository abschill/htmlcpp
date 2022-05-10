#include "HTMLC.in.h"
#include "config.cpp"
#include "util.cpp"
#include <fmt/core.h>

int main(int argc, char *argv[]) {
    if(argc > 1) {
        htmlc_config conf = find_config(argv[1]);  
        fmt::print("root: {}\npartials: {}\ntemplates: {}\n", conf.pathRoot, conf.partials, conf.templates);
    }
    else {
        fmt::print("Enter the path of your htmlc config, or submit inline arguments to parse as key value pairs");
    }

    return 0;
}