## libcfg
A minimalistic and easy to set up configuration manager for C++ projects.

### How to use

```c++
#include "src/config.h" // Include header

int main() {
    // 1. Define a settings array containing all your settings
    std::map<std::string, setting_type_e> settings = {
            {"some_boolean", setting_type_e::bool_type}, // <setting_identifier>, <setting_type>
            {"some_integer", setting_type_e::int_type},
            {"some_floating_number", setting_type_e::float_type},
            {"some_string", setting_type_e::string_type},
        };
    
    // 2. Create a config instance, giving a path to the config file and the settings map
    auto* config = new class config("./path_to_file.cfg", settings);
    
    // 3. Get settings at runtime using the setting identifier
    if (config->get_setting<int>("some_integer") == 1337) {
        std::cout << config->get_setting<std::string>("some_string") << std::endl;
    }

    return 0;
}
```

### Example config file

```cfg
some_boolean=1
some_integer=1337
some_floating_number=3.14
some_string=hello
```

### Notes

- The configuration file will be automatically created the first time you start the program, and all values will be set to their defaults.
- Currently supported setting types are `float`, `int`, `bool` and `std::string`

## Coding style

https://lefticus.gitbooks.io/cpp-best-practices/content/ (except for types which are snake_case), put `.cpp` and `.hpp` files next to each other in ./src