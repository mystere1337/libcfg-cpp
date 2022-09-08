#include <iostream>
#include <utility>
#include "config.h"

config::config(const std::vector<std::string>& settings, std::filesystem::path path, bool verbose) : m_path(std::move(path)), m_is_verbose(verbose) {
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

void config::load(const std::vector<std::string>& settings) {
    for (const auto& setting : settings) {
        set_setting(setting, get_setting_from_file(setting));
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

void config::set_setting(const std::string &setting_name, std::string value) {
    m_settings[setting_name] = std::move(value);
}

void config::set_verbose(bool verbose) {
    m_is_verbose = verbose;
}
