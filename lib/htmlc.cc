#include "HTMLC.in.h"
#include "config.cc"
#include "util.cc"
int main(int argc, char *argv[]) {
    if(argc > 1) {
        htmlc_config conf = find_config(argv[1]);  
        println(conf.pathRoot);
        println(conf.partials);
        println(conf.templates);
    }
    else {
        println("Enter the path of your htmlc config, or submit inline arguments to parse as key value pairs");
    }

    return 0;
}