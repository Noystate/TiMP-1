#pragma once
#include <vector>
#include <string>
#include <map>
#include <stdexcept>

class cipher_error : public std::invalid_argument {
public:
    explicit cipher_error(const std::string& what_arg) : std::invalid_argument(what_arg) {}
};

class RouteCipher {
private:
    int key;
    std::string numAlpha;
    std::map<char, int> alphaNum;
    
    // Валидация данных
    std::string getValidKey(const std::string& s);
    std::string getValidOpenText(const std::string& s);
    std::string getValidCipherText(const std::string& s);
    
    // Вспомогательные методы
    std::vector<std::vector<char>> createTable(const std::string& text);
    std::string readTableEncrypt(const std::vector<std::vector<char>>& table);
    std::string readTableDecrypt(const std::vector<std::vector<char>>& table);
    bool isEnglishLetter(char c);
    char toUpperEnglish(char c);
    void initializeAlphaNum();

public:
    RouteCipher() = delete;
    RouteCipher(const std::string& k);
    
    std::string encrypt(const std::string& text);
    std::string decrypt(const std::string& text);
    int getKey() const { return key; }
    void setKey(int k) { key = k; }
};
