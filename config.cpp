#include <iostream>
#include <utility>
#include "config.h"

config::config(const std::map<std::string, setting_type_e>& settings) : config("./config.cfg", settings) {

}

config::config(const std::filesystem::path& path, const std::map<std::string, setting_type_e>& settings) {
    _path = path;

    load(settings);
    create();
}

void config::create() {
    std::ofstream file{ _path };

    for (const auto& [key, value] : _settings) {
        file << key << "=" << value << std::endl;
    }

    file.close();
}

void config::load(const std::map<std::string, setting_type_e>& settings) {
    for (const auto& [key, type] : settings) {
        switch (type) {
            case float_type:
                set_setting(key, get_setting_from_file<float>(key));
                break;
            case int_type:
                set_setting(key, get_setting_from_file<int>(key));
                break;
            case bool_type:
                set_setting(key, get_setting_from_file<bool>(key));
                break;
            case string_type:
                set_setting(key, get_setting_from_file<std::string>(key));
                break;
        }
    }
}

void config::set_setting(const std::string &setting_name, int value) {
    _settings[setting_name] = value;
}

void config::set_setting(const std::string &setting_name, float value) {
    _settings[setting_name] = value;
}

void config::set_setting(const std::string &setting_name, bool value) {
    _settings[setting_name] = value;
}

void config::set_setting(const std::string &setting_name, std::string value) {
    _settings[setting_name] = std::move(value);
}