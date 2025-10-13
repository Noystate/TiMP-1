#include "routeCipher.h"
#include <algorithm>
#include <cctype>
#include <iostream>

using namespace std;

// Конструктор
RouteCipher::RouteCipher(const std::string& k) : numAlpha("ABCDEFGHIJKLMNOPQRSTUVWXYZ") {
    initializeAlphaNum();
    string valid_key = getValidKey(k);
    key = stoi(valid_key);
}

// Инициализация ассоциативного массива
void RouteCipher::initializeAlphaNum() {
    for (size_t i = 0; i < numAlpha.size(); i++) {
        alphaNum[numAlpha[i]] = i;
    }
}

// Проверка на английскую букву
bool RouteCipher::isEnglishLetter(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

// Преобразование в верхний регистр
char RouteCipher::toUpperEnglish(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 32;
    }
    return c;
}

// Валидация ключа
string RouteCipher::getValidKey(const std::string& s) {
    if (s.empty()) {
        throw cipher_error("Пустой ключ");
    }
    
    // Проверяем что все символы - цифры
    for (char c : s) {
        if (!isdigit(c)) {
            throw cipher_error("Ключ должен быть положительным числом: " + s);
        }
    }
    
    int k = stoi(s);
    if (k <= 0) {
        throw cipher_error("Ключ должен быть положительным числом: " + s);
    }
    
    return s;
}

// Валидация открытого текста
string RouteCipher::getValidOpenText(const std::string& s) {
    if (s.empty()) {
        throw cipher_error("Пустой открытый текст");
    }
    
    string result;
    bool hasEnglishLetters = false;
    
    for (char c : s) {
        if (isEnglishLetter(c) || c == ' ') {
            if (isEnglishLetter(c)) {
                result += toUpperEnglish(c);
            } else {
                result += c;
            }
            hasEnglishLetters = true;
        }
    }
    
    if (!hasEnglishLetters) {
        throw cipher_error("Текст не содержит английских букв");
    }
    
    return result;
}

// Валидация зашифрованного текста
string RouteCipher::getValidCipherText(const std::string& s) {
    if (s.empty()) {
        throw cipher_error("Пустой зашифрованный текст");
    }
    
    for (char c : s) {
        if (!isEnglishLetter(c) && c != ' ') {
            throw cipher_error("Зашифрованный текст содержит недопустимые символы");
        }
    }
    
    return s;
}

// Создание таблицы
vector<vector<char>> RouteCipher::createTable(const std::string& text) {
    string valid_text = getValidOpenText(text);
    int length = valid_text.length();
    int rows = (length + key - 1) / key;
    
    vector<vector<char>> table(rows, vector<char>(key, ' '));
    
    int index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < key; j++) {
            if (index < length) {
                table[i][j] = valid_text[index++];
            }
        }
    }
    
    return table;
}

// Чтение таблицы для шифрования (сверху вниз, справа налево)
string RouteCipher::readTableEncrypt(const std::vector<std::vector<char>>& table) {
    string result;
    int rows = table.size();
    int cols = table[0].size();
    
    for (int j = cols - 1; j >= 0; j--) {
        for (int i = 0; i < rows; i++) {
            result += table[i][j];
        }
    }
    
    return result;
}

// Чтение таблицы для дешифрования (по строкам слева направо)
string RouteCipher::readTableDecrypt(const std::vector<std::vector<char>>& table) {
    string result;
    int rows = table.size();
    int cols = table[0].size();
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result += table[i][j];
        }
    }
    
    return result;
}

// Шифрование
string RouteCipher::encrypt(const std::string& text) {
    auto table = createTable(text);
    return readTableEncrypt(table);
}

// Дешифрование
string RouteCipher::decrypt(const std::string& text) {
    string valid_text = getValidCipherText(text);
    int length = valid_text.length();
    int rows = (length + key - 1) / key;
    
    vector<vector<char>> table(rows, vector<char>(key, ' '));
    
    // Заполнение таблицы из зашифрованного текста
    int index = 0;
    for (int j = key - 1; j >= 0; j--) {
        for (int i = 0; i < rows; i++) {
            if (index < length) {
                table[i][j] = valid_text[index++];
            }
        }
    }
    
    return readTableDecrypt(table);
}
