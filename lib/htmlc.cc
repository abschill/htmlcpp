#include "HTMLC.in.h"
#include "config.cc"
#include "util.cc"
int main(int argc, char *argv[]) {
    if(argc > 1) {
        htmlc_config conf = find_config(argv[1]);
        //seg here not sure why lol
        // if(valid_path(conf.pathRoot)) {
        //     println("base path found");
        // }
        // else {
        //     println("base path not found");
        // }
    }
    else {
        println("Enter the path of your htmlc config");
    }

    return 0;
}