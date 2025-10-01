#pragma once
#include <string>
#include <stdexcept>
#include <locale>
#include <vector>

// Класс-исключение для ошибок шифрования
class cipher_error : public std::invalid_argument {
public:
    explicit cipher_error(const std::string& what_arg) : 
        std::invalid_argument(what_arg) {}
    explicit cipher_error(const char* what_arg) : 
        std::invalid_argument(what_arg) {}
};

// Класс для реализации шифра табличной маршрутной перестановки
class TableCipher {
private:
    unsigned key; // Количество столбцов таблицы
    const std::string validChars = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ "; // Допустимые символы
    
    // Методы валидации
    std::string getValidKey(const std::string& s);
    std::string getValidText(const std::string& s);
    
public:
    TableCipher() = delete;
    
    // Конструктор
    TableCipher(const std::string& skey);
    
    // Методы шифрования/расшифрования
    std::string encrypt(const std::string& open_text);
    std::string decrypt(const std::string& cipher_text);
    
    // Геттер для ключа
    unsigned getKey() const { return key; }
};
