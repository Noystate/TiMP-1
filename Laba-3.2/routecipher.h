#pragma once
#include <string>
#include <vector>

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
