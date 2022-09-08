#include <iostream>
#include "../src/config.h"

int main() {
    // 1. Define a settings vector containing all your settings
    std::vector<std::string> settings = {
            "int",
            "float",
            "string",
            "bool",
            "double"
        };

    // 2. Create a config instance, giving a path to the config file and the settings map
    auto* config = new class config(settings, "./config.cfg", true);

    // 3. Get settings at runtime using the setting identifier
    std::cout << config->get<int>("int") << std::endl;
    std::cout << config->get<float>("float") << std::endl;
    std::cout << config->get<std::string>("string") << std::endl;
    std::cout << config->get<bool>("bool") << std::endl;
    std::cout << config->get<double>("double") << std::endl;

    return 0;
}
