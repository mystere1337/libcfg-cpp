# libcfg
A minimalistic and easy to set up configuration manager for C++ projects.

## How to use

### main.cpp
```c++
#include <iostream>
#include "../src/config.h"

int main() {
    // Define a pair of std::string and std::any vector containing all your settings
    std::vector<std::pair<std::string, std::any>> settings = {
            {"int", 1337},
            {"float", 3.14},
            {"string", "hello"},
            {"bool", true},
            {"double", 3.14}
    };

    // Create a config instance, giving a path to the config file and the settings map
    auto* config = new class config(settings, "./config.cfg", true);

    // Change settings at runtime
    config->set("double", 10.4);

    // Get settings at runtime using the setting identifier
    std::cout << config->get<int>("int") << std::endl;
    std::cout << config->get<float>("float") << std::endl;
    std::cout << config->get<std::string>("string") << std::endl;
    std::cout << config->get<bool>("bool") << std::endl;
    std::cout << config->get<double>("double") << std::endl;

    // Save modified settings to file
    config->save();

    // Reloading a config will replace unsaved values
    config->reload();
}
```
### config.cfg
```cfg
int=1337
float=3.14
string=hello
double=10.4
bool=1
```

## Notes

- The configuration file will be created the first time you start the program and values will be set to their defaults.
- Currently supported setting types are listed [here](https://en.cppreference.com/w/cpp/io/basic_ostream/operator_ltlt)
- boolean values need to be written as `0` or `1`

## Coding style

https://lefticus.gitbooks.io/cpp-best-practices/content/ (except for types which are snake_case), put `.cpp` and `.hpp` files next to each other in ./src