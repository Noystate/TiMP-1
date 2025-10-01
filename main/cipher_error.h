#pragma once
#include <stdexcept>
#include <string>
#include <locale>

class cipher_error : public std::invalid_argument {
public:
    explicit cipher_error(const std::string& what_arg) : 
        std::invalid_argument(what_arg) {
        std::setlocale(LC_ALL, "ru_RU.UTF-8");
    }
    explicit cipher_error(const char* what_arg) : 
        std::invalid_argument(what_arg) {
        std::setlocale(LC_ALL, "ru_RU.UTF-8");
    }
};
