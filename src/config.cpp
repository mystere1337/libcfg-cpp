#include <iostream>
#include <utility>
#include "config.h"

config::config(const std::vector<std::pair<std::string, std::any>>& settings, const std::filesystem::path& path) : m_path(path) {
    load(settings);
    save(path);
}

void config::save(const std::filesystem::path& path) {
    std::ofstream file{ path };

    for (const auto& [key, value] : m_settings) {
        file << key << "=" << value << std::endl;
    }

    file.close();
}

void config::load(const std::vector<std::pair<std::string, std::any>>& settings) {
    for (const auto& [key, value] : settings) {
        std::string setting = get_setting_from_file(key);
        set(key, setting != "unset" ? setting : value);
    }
}

std::string config::get_setting_from_file(const std::string& setting_name) {
    std::ifstream file(m_path);
    std::string line;
    std::string value{"unset"};
    std::string key;

    while (std::getline(file, line)) {
        key = line.substr(0, line.find('='));
        trim(key);

        if (key == setting_name) {
            value = line.substr(line.find('=') + 1);
            trim(value);
        }
    }

    return value;
}

void config::set(const std::string &setting_name, const std::any& value) {
    m_settings[setting_name] = any_to_string(value);
}

void config::save() {
    save(m_path);
}

void config::reload() {
    for (const auto& [key, value] : m_settings) {
        std::string setting = get_setting_from_file(key);
        set(key, setting != "unset" ? setting : value);
    }
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

void config::trim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}
