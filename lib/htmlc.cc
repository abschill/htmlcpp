#include "HTMLC.in.h"
#include "config.cc"
#include "util.cc"
#include <fmt/core.h>

int main(int argc, char *argv[]) {
    if(argc > 1) {
        htmlc_config conf = find_config(argv[1]);  
        fmt::print("root: {}\npartials: {}\ntemplates: {}\n", conf.pathRoot, conf.partials, conf.templates);
    }
    else {
        println("Enter the path of your htmlc config, or submit inline arguments to parse as key value pairs");
    }

    return 0;
}