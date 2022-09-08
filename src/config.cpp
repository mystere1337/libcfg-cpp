#include <iostream>
#include <utility>
#include "config.h"

config::config(const std::vector<std::pair<std::string, std::any>>& settings, std::filesystem::path path, bool verbose) : m_path(std::move(path)), m_is_verbose(verbose) {
    load(settings);
    create_file();
}

void config::create_file() {
    std::ofstream file{ m_path };

    for (const auto& [key, value] : m_settings) {
        file << key << "=" << value << std::endl;
    }

    file.close();
}

void config::load(const std::vector<std::pair<std::string, std::any>>& settings) {
    for (const auto& [key, value] : settings) {
        std::string setting = get_setting_from_file(key);
        set_setting(key, setting != "unset" ? setting : value);
    }
}

std::string config::get_setting_from_file(const std::string& setting_name) {
    std::ifstream file(m_path);
    std::string line;
    std::string value = "unset";

    while (std::getline(file, line)) {
        std::regex pattern(R"(^\s*(.*?)\s*=\s*(.*?)\s*$)");
        std::smatch matches;

        if (std::regex_match(line, matches, pattern)) {
            if (matches[1] == setting_name) {
                value = matches[2].str();
                break;
            }
        }
    }

    if (m_is_verbose) {
        std::cout << setting_name << ": " << value << std::endl;
    }

    return value;
}

void config::set_setting(const std::string &setting_name, const std::any& value) {
    m_settings[setting_name] = any_to_string(value);
}

void config::set_verbose(bool verbose) {
    m_is_verbose = verbose;
}

std::string config::any_to_string(const std::any &value) {
    if (auto x = std::any_cast<int>(&value)) {
        return std::to_string(*x);
    }
    if (auto x = std::any_cast<float>(&value)) {
        return std::to_string(*x);
    }
    if (auto x = std::any_cast<double>(&value)) {
        return std::to_string(*x);
    }
    if (auto x = std::any_cast<bool>(&value)) {
        return std::to_string(*x);
    }
    if (auto x = std::any_cast<std::string>(&value)) {
        return (*x);
    }
    if (auto x = std::any_cast<const char*>(&value)) {
        return *x;
    }

    return "unsupported value";
}
