#include <iostream>
#include "../src/config.h"

int main() {
    // Define a pair of std::string and std::any vector containing all your settings
    config::setting_list settings = {
            {"int", 1337},
            {"float", 3.14},
            {"string", "hello"},
            {"bool", true},
            {"double", 3.14}
    };

    // Create a config instance, giving a path to the config file and the settings vector
    config config(settings, "./config.cfg");

    // Change settings at runtime
    config.set("double", 10.4);

    // Or add new settings (note that we're using the same method)
    config.set("new", "example");

    // Save modified settings to file
    config.save();

    // Reloading a config will replace unsaved values
    config.reload();

    // Get settings at runtime using the setting identifier
    std::cout << config.get<int>("int") << std::endl;
    std::cout << config.get<float>("float") << std::endl;
    std::cout << config.get<std::string>("string") << std::endl;
    std::cout << config.get<bool>("bool") << std::endl;
    std::cout << config.get<double>("double") << std::endl;

    return 0;
}
