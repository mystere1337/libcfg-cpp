#pragma once

#include <regex>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <any>
#include <variant>

enum setting_type_e {
    float_type,
    int_type,
    bool_type,
    string_type
};

class config {
    std::filesystem::path _path;
    std::map<std::string, std::variant<int, float, bool, std::string>> _settings;

    template <typename T> T get_setting_from_file(const std::string& name);
    void create();
    void load(const std::map<std::string, setting_type_e>& settings);
    void set_setting(const std::string &setting_name, int value);
    void set_setting(const std::string &setting_name, float value);
    void set_setting(const std::string &setting_name, bool value);
    void set_setting(const std::string &setting_name, std::string value);
public:
    explicit config(const std::map<std::string, setting_type_e>& settings);
    explicit config(const std::filesystem::path& path, const std::map<std::string, setting_type_e>& settings);

    template <typename T> T get_setting(const std::string &name);
};

template <typename T>
T config::get_setting_from_file(const std::string& name) {
    std::ifstream file(_path);
    std::string line;
    T value = {};

    while (std::getline(file, line)) {
        std::regex pattern("^(.*?)=(.*?)$");
        std::smatch matches;
        std::stringstream ss;

        if (std::regex_match(line, matches, pattern)) {
            if (matches[1] == name) {
                ss << matches[2];
                ss >> value;
                break;
            }
        }
    }

    std::cout << name << ": " << value << std::endl;

    return value;
}

template<typename T>
T config::get_setting(const std::string &name) {
    return std::get<T>(_settings[name]);
}

template <class Var, class = std::variant_alternative_t<0, Var>>
std::ostream& operator<<(std::ostream& os, Var const& v) {
    std::visit([&os](auto const& x) { os << x; }, v);
    return os;
}