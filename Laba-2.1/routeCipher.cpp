#include "routeCipher.h"
#include <algorithm>
#include <cctype>
#include <iostream>

// Конструктор
RouteCipher::RouteCipher(const std::string& k) {
    std::string valid_key = getValidKey(k);
    key = std::stoi(valid_key);
}

// Валидация ключа
std::string RouteCipher::getValidKey(const std::string& s) {
    if (s.empty()) {
        throw cipher_error("Пустой ключ");
    }
    
    for (char c : s) {
        if (!std::isdigit(c)) {
            throw cipher_error("Ключ должен быть положительным числом");
        }
    }
    
    int k = std::stoi(s);
    if (k <= 0) {
        throw cipher_error("Ключ должен быть положительным числом");
    }
    
    return s;
}

// Проверка на русскую букву
bool RouteCipher::isRussianLetter(wchar_t c) {
    return (c >= L'А' && c <= L'Я') || 
           (c >= L'а' && c <= L'я') || 
           c == L'Ё' || c == L'ё';
}

// Преобразование в верхний регистр для русских букв
wchar_t RouteCipher::toUpperRussian(wchar_t c) {
    if (c >= L'а' && c <= L'я') {
        return c - L'а' + L'А';
    } else if (c == L'ё') {
        return L'Ё';
    }
    return c;
}

// Валидация текста
std::wstring RouteCipher::getValidText(const std::wstring& s) {
    if (s.empty()) {
        throw cipher_error("Пустой текст");
    }
    
    std::wstring result;
    for (wchar_t c : s) {
        if (isRussianLetter(c) || c == L' ') {
            if (isRussianLetter(c)) {
                result.push_back(toUpperRussian(c));
            } else {
                result.push_back(c); // Пробелы сохраняем
            }
        }
        // Не-буквенные символы (кроме пробелов) игнорируются
    }
    
    if (result.empty()) {
        throw cipher_error("Текст не содержит русских букв или пробелов");
    }
    
    return result;
}

// Создание таблицы
std::vector<std::vector<wchar_t>> RouteCipher::createTable(const std::wstring& text) {
    std::wstring valid_text = getValidText(text);
    int text_length = valid_text.length();
    
    int rows = (text_length + key - 1) / key;
    int cols = key;
    
    std::vector<std::vector<wchar_t>> table(rows, std::vector<wchar_t>(cols, L' '));
    
    int index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (index < text_length) {
                table[i][j] = valid_text[index++];
            }
        }
    }
    
    return table;
}

// Чтение таблицы для шифрования (сверху вниз, справа налево)
std::wstring RouteCipher::readTableEncrypt(const std::vector<std::vector<wchar_t>>& table) {
    std::wstring result;
    int rows = table.size();
    int cols = table[0].size();
    
    for (int j = cols - 1; j >= 0; j--) {
        for (int i = 0; i < rows; i++) {
            if (table[i][j] != L' ') {
                result.push_back(table[i][j]);
            }
        }
    }
    
    return result;
}

// Чтение таблицы для дешифрования (по строкам слева направо)
std::wstring RouteCipher::readTableDecrypt(const std::vector<std::vector<wchar_t>>& table) {
    std::wstring result;
    int rows = table.size();
    int cols = table[0].size();
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (table[i][j] != L' ') {
                result.push_back(table[i][j]);
            }
        }
    }
    
    return result;
}

// Шифрование
std::wstring RouteCipher::encrypt(const std::wstring& text) {
    auto table = createTable(text);
    return readTableEncrypt(table);
}

// Дешифрование
std::wstring RouteCipher::decrypt(const std::wstring& text) {
    std::wstring valid_text = getValidText(text);
    int text_length = valid_text.length();
    
    int rows = (text_length + key - 1) / key;
    int cols = key;
    
    std::vector<std::vector<wchar_t>> table(rows, std::vector<wchar_t>(cols, L' '));
    
    int index = 0;
    // Заполнение таблицы из зашифрованного текста
    for (int j = cols - 1; j >= 0; j--) {
        for (int i = 0; i < rows; i++) {
            if (index < text_length) {
                table[i][j] = valid_text[index++];
            }
        }
    }
    
    return readTableDecrypt(table);
}
