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
    bool m_is_verbose = false;

    static std::string any_to_string(const std::any& value);
    std::string get_setting_from_file(const std::string& setting_name);
    void load(const std::vector<std::pair<std::string, std::any>>& settings);
    void set_setting(const std::string &setting_name, const std::any& value);
    void create_file();

public:
    explicit config(const std::vector<std::pair<std::string, std::any>>& settings, std::filesystem::path path = "./config.cfg", bool verbose = false);

    void set_verbose(bool verbose);
    [[nodiscard]] bool is_verbose() const { return m_is_verbose; }

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