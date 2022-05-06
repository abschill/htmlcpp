#include <iostream>
#include "HTMLC.in.h"
#include "config.cc"
#include "util.cc"

int main(int argc, char *argv[]) {
    if(argc > 1) {
        for(int i = 1; i < argc; i++) {
            parse_prog_arg(argv[1]);
        }
    }

    print_placeholder();
    return 0;
}