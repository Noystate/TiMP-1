#pragma once
#include <vector>
#include <string>
#include <stdexcept>
#include <locale>
#include <codecvt>

class cipher_error : public std::invalid_argument {
public:
    explicit cipher_error(const std::string& what_arg) : std::invalid_argument(what_arg) {}
};

class RouteCipher {
private:
    int key;
    
    std::string getValidKey(const std::string& s);
    std::wstring getValidText(const std::wstring& s);
    std::vector<std::vector<wchar_t>> createTable(const std::wstring& text);
    std::wstring readTableEncrypt(const std::vector<std::vector<wchar_t>>& table);
    std::wstring readTableDecrypt(const std::vector<std::vector<wchar_t>>& table);
    bool isRussianLetter(wchar_t c);
    wchar_t toUpperRussian(wchar_t c);
    
public:
    RouteCipher() = delete;
    RouteCipher(const std::string& k);
    
    std::wstring encrypt(const std::wstring& text);
    std::wstring decrypt(const std::wstring& text);
    int getKey() const { return key; }
};
