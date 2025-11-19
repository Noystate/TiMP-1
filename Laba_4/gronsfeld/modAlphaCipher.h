/** @file modAlphaCipher.h
 * @author Артёмка
 * @version 1.0
 * @date 2025
 * @copyright ИБСТ ПГУ
 * @warning Это не учебный пример
 * @brief Заголовочный файл для модуля Gronsfeld
 */

#pragma once
#include <string>
#include <vector>

/**
 * @brief Шифрование методом Гронсфельда
 * @details Ключ устанавливается в конструкторе. Для зашифровывания и 
 * расшифровывания предназначены методы encrypt и decrypt.
 * @warning Реализация только для английского языка
 */
class modAlphaCipher
{
private:
    std::vector<int> key; ///< ключ для шифрования
     
    std::vector<int> convert(const std::string& s);
    std::string convert(const std::vector<int>& v);
    std::string getValidKey(const std::string& s);
    std::string getValidOpenText(const std::string& s);
    std::string getValidCipherText(const std::string& s);

public:
    modAlphaCipher() = delete; ///< удаленный конструктор без параметров
    
    /**
     * @brief Конструктор для установки ключа
     * @param [in] skey Ключ шифрования в виде строки
     */
    modAlphaCipher(const std::string& skey);
    
    /**
     * @brief Зашифровывание открытого текста
     * @param [in] open_text Открытый текст. Не должен быть пустой строкой.
     * Строчные символы автоматически преобразуются к прописным.
     * Все не-буквы удаляются.
     * @return Зашифрованная строка
     * @throw cipher_error если текст пустой
     */
    std::string encrypt(const std::string& open_text);
    
    /**
     * @brief Расшифровывание зашифрованного текста
     * @param [in] cipher_text Зашифрованный текст. Не должен быть пустой строкой.
     * Должен содержать только прописные буквы английского алфавита.
     * @return Расшифрованная строка
     * @throw cipher_error если текст пустой или содержит недопустимые символы
     */
    std::string decrypt(const std::string& cipher_text);
};
