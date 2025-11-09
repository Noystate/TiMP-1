#include "routeCipher.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <vector>

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
    
    for (char c : s) {
        if (!isdigit(c)) {
            throw cipher_error("Ключ должен быть положительным числом: " + s);
        }
    }
    
    int k = stoi(s);
    if (k <= 0) {
        throw cipher_error("Ключ должен быть положительным числом: " + s);
    }
    
    // ЗАПРЕТ ключа = 1
    if (k == 1) {
        throw cipher_error("Ключ не может быть равен 1");
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
                hasEnglishLetters = true;
            } else {
                result += c;
            }
        } else {
            throw cipher_error("Текст содержит недопустимые символы: " + string(1, c));
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

// Создание таблицы для шифрования
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

// Чтение таблицы для шифрования (спираль по часовой стрелке)
string RouteCipher::readTableEncrypt(const std::vector<std::vector<char>>& table) {
    string result;
    int rows = table.size();
    int cols = key;
    
    int top = 0, bottom = rows - 1, left = 0, right = cols - 1;
    
    while (top <= bottom && left <= right) {
        // Справа налево в верхней строке
        for (int j = right; j >= left; j--) {
            result += table[top][j];
        }
        top++;
        
        // Сверху вниз в левом столбце
        if (top <= bottom) {
            for (int i = top; i <= bottom; i++) {
                result += table[i][left];
            }
            left++;
        }
        
        // Слева направо в нижней строке
        if (left <= right && top <= bottom) {
            for (int j = left; j <= right; j++) {
                result += table[bottom][j];
            }
            bottom--;
        }
        
        // Снизу вверх в правом столбце
        if (top <= bottom && left <= right) {
            for (int i = bottom; i >= top; i--) {
                result += table[i][right];
            }
            right--;
        }
    }
    
    return result;
}

// Создание таблицы для дешифрования
vector<vector<char>> RouteCipher::createDecryptTable(const std::string& text) {
    string valid_text = getValidCipherText(text);
    int length = valid_text.length();
    int rows = (length + key - 1) / key;
    
    vector<vector<char>> table(rows, vector<char>(key, ' '));
    
    int top = 0, bottom = rows - 1, left = 0, right = key - 1;
    int index = 0;
    
    while (top <= bottom && left <= right && index < length) {
        // Заполняем справа налево в верхней строке
        for (int j = right; j >= left && index < length; j--) {
            table[top][j] = valid_text[index++];
        }
        top++;
        
        // Заполняем сверху вниз в левом столбце
        for (int i = top; i <= bottom && index < length; i++) {
            table[i][left] = valid_text[index++];
        }
        left++;
        
        // Заполняем слева направо в нижней строке
        if (top <= bottom) {
            for (int j = left; j <= right && index < length; j++) {
                table[bottom][j] = valid_text[index++];
            }
            bottom--;
        }
        
        // Заполняем снизу вверх в правом столбце
        if (left <= right) {
            for (int i = bottom; i >= top && index < length; i--) {
                table[i][right] = valid_text[index++];
            }
            right--;
        }
    }
    
    return table;
}

// Чтение таблицы для дешифрования (по строкам слева направо)
string RouteCipher::readTableDecrypt(const std::vector<std::vector<char>>& table) {
    string result;
    int rows = table.size();
    int cols = key;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result += table[i][j];
        }
    }
    
    // Удаляем лишние пробелы в конце (только если они были добавлены при заполнении)
    size_t last_non_space = result.find_last_not_of(' ');
    if (last_non_space != string::npos) {
        result = result.substr(0, last_non_space + 1);
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
    auto table = createDecryptTable(text);
    return readTableDecrypt(table);
}
