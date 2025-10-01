#pragma once
#include <string>
#include <stdexcept>
#include <locale>
#include <vector>
#include <map>

// Класс-исключение для ошибок шифрования
class cipher_error : public std::invalid_argument {
public:
    explicit cipher_error(const std::string& what_arg) : 
        std::invalid_argument(what_arg) {}
    explicit cipher_error(const char* what_arg) : 
        std::invalid_argument(what_arg) {}
};

// Класс для реализации шифра Гронсфельда
class modAlphaCipher {
private:
    std::string numAlpha = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ "; // Алфавит с пробелом
    std::map<char, int> alphaNum; // Ассоциативный массив "символ-номер"
    std::vector<int> key; // Ключ в числовом виде
    
    // Методы преобразования
    std::vector<int> convert(const std::string& s);
    std::string convert(const std::vector<int>& v);
    
    // Методы валидации
    std::string getValidKey(const std::string& s);
    std::string getValidOpenText(const std::string& s);
    std::string getValidCipherText(const std::string& s);
    
public:
    modAlphaCipher() = delete; // Запрет конструктора без параметров
    
    // Конструктор с установкой ключа
    modAlphaCipher(const std::string& skey);
    
    // Метод зашифрования
    std::string encrypt(const std::string& open_text);
    
    // Метод расшифрования
    std::string decrypt(const std::string& cipher_text);
};
