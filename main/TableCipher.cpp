#include "TableCipher.h"
#include <cctype>
#include <algorithm>

// Валидация ключа
std::string TableCipher::getValidKey(const std::string& s) {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    
    if (s.empty()) {
        throw cipher_error("Пустой ключ");
    }
    
    std::string tmp;
    for (auto c : s) {
        if (std::isdigit(c)) {
            tmp.push_back(c);
        }
    }
    
    if (tmp.empty()) {
        throw cipher_error("Ключ должен содержать цифры");
    }
    
    return tmp;
}

// Валидация текста
std::string TableCipher::getValidText(const std::string& s) {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    
    if (s.empty()) {
        throw cipher_error("Пустой текст");
    }
    
    std::string tmp;
    for (auto c : s) {
        if (validChars.find(c) != std::string::npos) {
            if (std::islower(c)) {
                tmp.push_back(std::toupper(c));
            } else {
                tmp.push_back(c);
            }
        }
    }
    
    if (tmp.empty()) {
        throw cipher_error("Текст не содержит допустимых символов");
    }
    
    return tmp;
}

// Конструктор
TableCipher::TableCipher(const std::string& skey) {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    std::locale::global(std::locale("ru_RU.UTF-8"));
    
    std::string validKey = getValidKey(skey);
    
    try {
        key = std::stoi(validKey);
    } catch (const std::exception& e) {
        throw cipher_error("Неверный формат ключа: " + validKey);
    }
    
    if (key == 0) {
        throw cipher_error("Ключ не может быть нулевым");
    }
    
    if (key > 100) {
        throw cipher_error("Слишком большой ключ");
    }
}

// Шифрование
std::string TableCipher::encrypt(const std::string& open_text) {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    
    std::string validText = getValidText(open_text);
    unsigned rows = (validText.length() + key - 1) / key;
    
    // Создание и заполнение таблицы
    std::vector<std::vector<char>> table(rows, std::vector<char>(key, ' '));
    for (unsigned i = 0; i < validText.length(); ++i) {
        table[i / key][i % key] = validText[i];
    }
    
    // Чтение по столбцам справа налево
    std::string cipher_text;
    for (unsigned col = key; col > 0; --col) {
        for (unsigned row = 0; row < rows; ++row) {
            if (table[row][col-1] != ' ') {
                cipher_text += table[row][col-1];
            }
        }
    }
    
    return cipher_text;
}

// Расшифрование
std::string TableCipher::decrypt(const std::string& cipher_text) {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    
    std::string validText = getValidText(cipher_text);
    unsigned rows = (validText.length() + key - 1) / key;
    
    if (rows == 0) {
        throw cipher_error("Невозможно создать таблицу для расшифрования");
    }
    
    // Заполнение таблицы по столбцам справа налево
    std::vector<std::vector<char>> table(rows, std::vector<char>(key, ' '));
    unsigned index = 0;
    for (unsigned col = key; col > 0; --col) {
        for (unsigned row = 0; row < rows; ++row) {
            if (index < validText.length()) {
                table[row][col-1] = validText[index++];
            }
        }
    }
    
    // Чтение по строкам слева направо
    std::string open_text;
    for (unsigned row = 0; row < rows; ++row) {
        for (unsigned col = 0; col < key; ++col) {
            if (table[row][col] != ' ') {
                open_text += table[row][col];
            }
        }
    }
    
    return open_text;
}
