/** @file routecipher.h
 * @author Ваше Артёмка
 * @version 1.0
 * @date 2025
 * @copyright ПГУ
 * @warning Это учебный пример
 * @brief Заголовочный файл для модуля Table Route Cipher
 */

#pragma once
#include <string>
#include <vector>

/**
 * @brief Шифрование методом табличной маршрутной перестановки
 * @details Ключ устанавливается в конструкторе. Для зашифровывания и 
 * расшифровывания предназначены методы encrypt и decrypt.
 * @warning Реализация для английского языка и цифр
 */
class RouteCipher {
private:
    int key; ///< ключ - количество столбцов в таблице
public:
    RouteCipher() = delete; ///< удаленный конструктор без параметров
    
    /**
     * @brief Конструктор для установки ключа
     * @param [in] skey Ключ шифрования (количество столбцов)
     * @throw std::invalid_argument если ключ не положительное число
     */
    RouteCipher(int skey);
    
    /**
     * @brief Зашифровывание
     * @param [in] text Открытый текст. Не должен быть пустой строкой.
     * Строчные символы автоматически преобразуются к прописным.
     * Все пробелы удаляются
     * @return Зашифрованная строка
     * @throw std::invalid_argument если текст пустой
     */
    std::string encrypt(const std::string& text);
    
    /**
     * @brief Расшифровывание
     * @param [in] text Зашифрованный текст. Не должен быть пустой строкой.
     * Строчные символы автоматически преобразуются к прописным.
     * Все пробелы удаляются
     * @return Расшифрованная строка  
     * @throw std::invalid_argument если текст пустой
     */
    std::string decrypt(const std::string& text);
    
    /**
     * @brief Получение текущего ключа
     * @return Текущее значение ключа
     */
    int getKey() const { return key; }
    
    /**
     * @brief Установка нового ключа
     * @param [in] newKey Новое значение ключа
     * @throw std::invalid_argument если ключ не положительное число
     */
    void setKey(int newKey) { key = newKey; }
};
