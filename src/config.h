#pragma once

#include <regex>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <any>
#include <variant>

class config {
public:
    typedef std::vector<std::pair<std::string, std::any>> setting_list;

    explicit config(const setting_list& settings, const std::filesystem::path& path = "./config.cfg");

    template <typename T> T get(const std::string &name);
    void set(const std::string &setting_name, const std::any& value);
    void save();
    void reload();

private:
    std::filesystem::path m_path{};
    std::map<std::string, std::string> m_settings{};

    static void trim(std::string &s);
    static std::string any_to_string(const std::any& value);
    std::string get_setting_from_file(const std::string& setting_name);
    void load(const setting_list& settings);
    void save(const std::filesystem::path& path);
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