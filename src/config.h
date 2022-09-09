#pragma once

#include <regex>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <any>
#include <variant>

class config {
    std::filesystem::path m_path{};
    std::map<std::string, std::string> m_settings{};

    static std::string any_to_string(const std::any& value);
    std::string get_setting_from_file(const std::string& setting_name);
    void load(const std::vector<std::pair<std::string, std::any>>& settings);
    void save(const std::filesystem::path& path);

public:
    explicit config(const std::vector<std::pair<std::string, std::any>>& settings, const std::filesystem::path& path = "./config.cfg");

    template <typename T> T get(const std::string &name);
    void set(const std::string &setting_name, const std::any& value);
    void save();
    void reload();
};

template<typename T>
T config::get(const std::string &name) {
     std::stringstream stream{m_settings[name]};
     T t;

     stream >> t;
     return t;
}

template <class Var, class = std::variant_alternative_t<0, Var>>
std::ostream& operator<<(std::ostream& os, Var const& v) {
    std::visit([&os](auto const& x) { os << x; }, v);
    return os;
}