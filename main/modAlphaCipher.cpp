#include "modAlphaCipher.h"
#include <cctype>
#include <algorithm>

// Конструктор
modAlphaCipher::modAlphaCipher(const std::string& skey) {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    std::locale::global(std::locale("ru_RU.UTF-8"));
    
    for (unsigned i = 0; i < numAlpha.size(); i++) {
        alphaNum[numAlpha[i]] = i;
    }
    key = convert(getValidKey(skey));
}

// Метод валидации ключа
std::string modAlphaCipher::getValidKey(const std::string& s) {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    if (s.empty()) {
        throw cipher_error("Пустой ключ");
    }
    
    std::string tmp;
    for (auto c : s) {
        if (numAlpha.find(c) != std::string::npos) {
            if (std::islower(c)) {
                tmp.push_back(std::toupper(c));
            } else {
                tmp.push_back(c);
            }
        }
    }
    
    if (tmp.empty()) {
        throw cipher_error("Ключ не содержит допустимых символов");
    }
    
    return tmp;
}

// Остальные методы остаются без изменений, но добавьте setlocale в encrypt и decrypt:
std::string modAlphaCipher::encrypt(const std::string& open_text) {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    // ... остальной код
}

std::string modAlphaCipher::decrypt(const std::string& cipher_text) {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    // ... остальной код
}
