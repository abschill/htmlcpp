#include <HTMLC.h>
#include "config.cpp"

int main(int argc, char *argv[]) {
    if(argc > 1) {
        htmlc_config::Config conf = htmlc_config::find_config(argv[1]);
        string config_err = htmlc_config::validate_config(conf);

        if(config_err != "") {
            fmt::print("error: {}\n exit code: 1\n", config_err);
            return 1;
        }

        htmlc_config::print_config(conf);
	/**
	 * Todo: we have the following information at this stage:
	 * 1. map of the chunks relative to the submitted configuration
	 * 2. struct properties that tell us if a given chunk requires the render engine to pass over it
	 * 3. the content of each raw chunk along with its path relative to the defined configuration roots
	 * We will need to implement the following:
	 * 1. tokenization stage for each non-static chunk that was resolved.
	 * 2. generic struct mappings for arbitrary user input into chunk input configuration attribute
	 **/
        fmt::print("{}\n", htmlc_config::get_chunkmap(conf).resolved_pages[0].is_static);
    }
    else {
        fmt::print("Enter the path of your htmlc config, or submit inline arguments to parse as key value pairs\nexit code: 1\n");
        return 1;
    }

    return 0;
}
