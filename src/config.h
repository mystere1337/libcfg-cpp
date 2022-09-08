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

    std::string get_setting_from_file(const std::string& setting_name);
    void load(const std::vector<std::string>& settings);
    void set_setting(const std::string &setting_name, std::string value);
    void create_file();
public:
    explicit config(const std::vector<std::string>& settings);
    explicit config(const std::filesystem::path& path, const std::vector<std::string>& settings);

    template <typename T> T get(const std::string &name);
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