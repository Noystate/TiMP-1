#include "modAlphaCipher.h"
#include <cctype>
#include <algorithm>

// Конструктор
modAlphaCipher::modAlphaCipher(const std::string& skey) {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    std::locale::global(std::locale("ru_RU.UTF-8"));
    
    // Инициализация ассоциативного массива
    for (unsigned i = 0; i < numAlpha.size(); i++) {
        alphaNum[numAlpha[i]] = i;
    }
    
    // Валидация и установка ключа
    key = convert(getValidKey(skey));
}

// Метод валидации ключа
std::string modAlphaCipher::getValidKey(const std::string& s) {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    
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

// Метод валидации открытого текста
std::string modAlphaCipher::getValidOpenText(const std::string& s) {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    
    if (s.empty()) {
        throw cipher_error("Пустой открытый текст");
    }
    
    std::string tmp;
    for (auto c : s) {
        if (numAlpha.find(c) != std::string::npos) {
            if (std::islower(c)) {
                tmp.push_back(std::toupper(c));
            } else {
                tmp.push_back(c);
            }
        } else {
            // Игнорируем недопустимые символы
            continue;
        }
    }
    
    if (tmp.empty()) {
        throw cipher_error("Текст не содержит допустимых символов");
    }
    
    return tmp;
}

// Метод валидации зашифрованного текста
std::string modAlphaCipher::getValidCipherText(const std::string& s) {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    
    if (s.empty()) {
        throw cipher_error("Пустой зашифрованный текст");
    }
    
    for (auto c : s) {
        if (numAlpha.find(c) == std::string::npos) {
            throw cipher_error("Зашифрованный текст содержит недопустимые символы");
        }
    }
    
    return s;
}

// Преобразование строки в числовой вектор
std::vector<int> modAlphaCipher::convert(const std::string& s) {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    
    std::vector<int> result;
    for (auto c : s) {
        result.push_back(alphaNum[c]);
    }
    return result;
}

// Преобразование числового вектора в строку
std::string modAlphaCipher::convert(const std::vector<int>& v) {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    
    std::string result;
    for (auto i : v) {
        result.push_back(numAlpha[i]);
    }
    return result;
}

// Метод зашифрования
std::string modAlphaCipher::encrypt(const std::string& open_text) {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    
    std::string validText = getValidOpenText(open_text);
    std::vector<int> work = convert(validText);
    
    for (unsigned i = 0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % numAlpha.size();
    }
    
    return convert(work);
}

// Метод расшифрования
std::string modAlphaCipher::decrypt(const std::string& cipher_text) {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    
    std::string validText = getValidCipherText(cipher_text);
    std::vector<int> work = convert(validText);
    
    for (unsigned i = 0; i < work.size(); i++) {
        work[i] = (work[i] + numAlpha.size() - key[i % key.size()]) % numAlpha.size();
    }
    
    return convert(work);
}
