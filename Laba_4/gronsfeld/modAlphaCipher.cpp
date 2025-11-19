/**
 * @file modAlphaCipher.cpp
 * @author Артёмка
 * @version 1.0
 * @date 2025
 * @brief Реализация методов класса modAlphaCipher
 */

#include "modAlphaCipher.h"
#include <vector>
#include <string>
#include <stdexcept>
#include <cctype>
#include <locale>

using namespace std;

class cipher_error : public invalid_argument {
public:
    explicit cipher_error (const string& what_arg) :
        invalid_argument(what_arg) {}
    explicit cipher_error (const char* what_arg) :
        invalid_argument(what_arg) {}
};

modAlphaCipher::modAlphaCipher(const std::string& skey) {
    for (auto c : skey) {
        if (!isdigit(c))
            throw cipher_error("Ключ должен содержать только цифры");
    }
    key = convert(getValidKey(skey));
}

std::string modAlphaCipher::encrypt(const std::string& open_text) {
    string s = getValidOpenText(open_text);
    vector<int> work = convert(s);
    for (unsigned i = 0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % 26;
    }
    return convert(work);
}

std::string modAlphaCipher::decrypt(const std::string& cipher_text) {
    string s = getValidCipherText(cipher_text);
    vector<int> work = convert(s);
    for (unsigned i = 0; i < work.size(); i++) {
        work[i] = (work[i] + 26 - key[i % key.size()]) % 26;
    }
    return convert(work);
}

std::vector<int> modAlphaCipher::convert(const std::string& s) {
    vector<int> result;
    for (auto c : s) {
        result.push_back(toupper(c) - 'A');
    }
    return result;
}

std::string modAlphaCipher::convert(const std::vector<int>& v) {
    string result;
    for (auto i : v) {
        result.push_back(i + 'A');
    }
    return result;
}

std::string modAlphaCipher::getValidKey(const std::string& s) {
    if (s.empty())
        throw cipher_error("Пустой ключ");
    string tmp;
    for (auto c : s) {
        if (isdigit(c))
            tmp.push_back(c);
    }
    if (tmp.empty())
        throw cipher_error("Ключ должен содержать цифры");
    return tmp;
}

std::string modAlphaCipher::getValidOpenText(const std::string& s) {
    if (s.empty())
        throw cipher_error("Пустой открытый текст");
    string tmp;
    for (auto c : s) {
        if (isalpha(c)) {
            if (islower(c))
                tmp.push_back(toupper(c));
            else
                tmp.push_back(c);
        }
    }
    if (tmp.empty())
        throw cipher_error("Открытый текст должен содержать буквы");
    return tmp;
}

std::string modAlphaCipher::getValidCipherText(const std::string& s) {
    if (s.empty())
        throw cipher_error("Пустой зашифрованный текст");
    for (auto c : s) {
        if (!isupper(c))
            throw cipher_error("Зашифрованный текст должен содержать только прописные буквы");
    }
    return s;
}
