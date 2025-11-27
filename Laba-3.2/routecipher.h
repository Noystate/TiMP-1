#pragma once
#include <string>
#include <stdexcept>

class cipher_error : public std::invalid_argument {
public:
    explicit cipher_error(const std::string& what_arg) : std::invalid_argument(what_arg) {}
    explicit cipher_error(const char* what_arg) : std::invalid_argument(what_arg) {}
};

class RouteCipher {
private:
    int key;
public:
    RouteCipher() = delete;
    RouteCipher(int skey);
    std::string encrypt(const std::string& text);
    std::string decrypt(const std::string& text);
    int getKey() const { return key; }
    void setKey(int newKey) { key = newKey; }
};
