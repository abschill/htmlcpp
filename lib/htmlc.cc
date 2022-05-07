#include <format>
#include "htmlc.hh"
#include "config.hh"

std::pair<std::string, std::string> parse_inline_arg(const std::string& keyval) {
    auto key = keyval.substr(0, keyval.find("="));
    // add 1 to the size to offset the delim
    auto val = keyval.substr(key.size() + 1, keyval.size());
    return std::make_pair(key, val);
}

int main(int argc, char *argv[]) {
    std::cout << std::format("HTMLC v{}.{}\n\n", HTMLC_VERSION_MAJOR, HTMLC_VERSION_MINOR);
    if(argc > 1) {
        auto conf = htmlc::find_config(std::string{ argv[1] });
        std::cout << std::format("{}\n{}\n{}\n", conf.pathRoot, conf.partials, conf.templates);
    }
    else {
        std::cout << "Enter the path of your htmlc config.\n";//or submit inline arguments to parse as key value pairs";
    }

    return 0;
}
