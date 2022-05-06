#include "HTMLC.in.h"
#include "config.cc"
#include "util.cc"
int main(int argc, char *argv[]) {
    if(argc > 1) {
        for(int i = 1; i != argc; i++) {
            print_arg(parse_inline_arg(argv[i]));
        }
    }

    find_config();
    return 0;
}