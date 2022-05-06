#include "HTMLC.in.h"
#include "config.cc"
#include "util.cc"
int main(int argc, char *argv[]) {
    if(argc > 1) {
        htmlc_config conf = find_config(argv[1]);
    }
    else {
        println("Enter the path of your htmlc config");
    }

    return 0;
}