#include "modAlphaCipher.h"
#include <algorithm>
#include <iostream>
#include <map>

// Конструктор
modAlphaCipher::modAlphaCipher(const std::wstring& skey) : loc("ru_RU.UTF-8")
{
    // Инициализация алфавита (33 русские буквы + пробел)
    numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ ";
    
    // Инициализация ассоциативного массива
    for (unsigned i = 0; i < numAlpha.size(); i++) {
        alphaNum[numAlpha[i]] = i;
    }
    
    std::wstring valid_key = getValidKey(skey);
    key = convert(valid_key);
    
    // Проверка на слабый ключ (после валидации)
    checkWeakKey(valid_key);
}

// Проверка на русскую букву
bool modAlphaCipher::isRussianLetter(wchar_t c) {
    return (c >= L'А' && c <= L'Я') || (c >= L'а' && c <= L'я') || c == L'Ё' || c == L'ё';
}

// Проверка на русскую заглавную букву
bool modAlphaCipher::isRussianUpperCase(wchar_t c) {
    return (c >= L'А' && c <= L'Я') || c == L'Ё';
}

// Проверка на пробел
bool modAlphaCipher::isSpace(wchar_t c) {
    return c == L' ';
}

// Проверка на слабый ключ - УПРОЩЕННАЯ ВЕРСИЯ
void modAlphaCipher::checkWeakKey(const std::wstring& key) {
    if (key.size() <= 1) return; // Ключ из одного символа допустим
    
    // Проверяем, что ключ не состоит из одинаковых символов
    bool allSame = true;
    for (size_t i = 1; i < key.size(); i++) {
        if (key[i] != key[0]) {
            allSame = false;
            break;
        }
    }
    
    if (allSame) {
        throw cipher_error("Слабый ключ");
    }
}

// Валидация ключа
std::wstring modAlphaCipher::getValidKey(const std::wstring& s)
{
    if (s.empty()) {
        throw cipher_error("Пустой ключ");
    }
    
    std::wstring tmp;
    for (auto c : s) {
        // РАЗРЕШАЕМ ТОЛЬКО РУССКИЕ БУКВЫ (без пробелов)
        if (isRussianLetter(c)) {
            // Приводим к верхнему регистру
            if (c >= L'а' && c <= L'я') {
                tmp.push_back(c - L'а' + L'А');
            } else if (c == L'ё') {
                tmp.push_back(L'Ё');
            } else {
                tmp.push_back(c);
            }
        } else {
            throw cipher_error("Ключ содержит недопустимые символы");
        }
    }
    
    if (tmp.empty()) {
        throw cipher_error("Пустой ключ после валидации");
    }
    
    return tmp;
}

// Валидация открытого текста
std::wstring modAlphaCipher::getValidOpenText(const std::wstring& s)
{
    if (s.empty()) {
        throw cipher_error("Пустой открытый текст");
    }
    
    std::wstring tmp;
    bool hasValidChars = false;
    
    for (auto c : s) {
        // Разрешаем русские буквы и пробелы
        if (isRussianLetter(c) || isSpace(c)) {
            // Приводим к верхнему регистру
            if (c >= L'а' && c <= L'я') {
                tmp.push_back(c - L'а' + L'А');
            } else if (c == L'ё') {
                tmp.push_back(L'Ё');
            } else {
                tmp.push_back(c);
            }
            hasValidChars = true;
        }
        // Игнорируем другие символы (цифры, знаки препинания и т.д.)
    }
    
    if (!hasValidChars) {
        throw cipher_error("Текст не содержит допустимых символов");
    }
    
    return tmp;
}

// Валидация зашифрованного текста
std::wstring modAlphaCipher::getValidCipherText(const std::wstring& s)
{
    if (s.empty()) {
        throw cipher_error("Пустой зашифрованный текст");
    }
    
    bool hasValidChars = false;
    for (auto c : s) {
        if (isRussianLetter(c) || isSpace(c)) {
            hasValidChars = true;
        }
        
        if (!isRussianLetter(c) && !isSpace(c)) {
            throw cipher_error("Зашифрованный текст содержит недопустимые символы");
        }
        // Для зашифрованного текста требуем верхний регистр
        if (isRussianLetter(c) && !isRussianUpperCase(c)) {
            throw cipher_error("Зашифрованный текст должен быть в верхнем регистре");
        }
    }
    
    if (!hasValidChars) {
        throw cipher_error("Зашифрованный текст не содержит допустимых символов");
    }
    
    return s;
}

// Преобразование строки в вектор чисел
std::vector<int> modAlphaCipher::convert(const std::wstring& s)
{
    std::vector<int> result;
    for (auto c : s) {
        auto it = alphaNum.find(c);
        if (it != alphaNum.end()) {
            result.push_back(it->second);
        } else {
            // Если символ не найден в алфавите, это ошибка
            throw cipher_error("Символ не найден в алфавите: " + std::string(1, static_cast<char>(c)));
        }
    }
    return result;
}

// Преобразование вектора чисел в строку
std::wstring modAlphaCipher::convert(const std::vector<int>& v)
{
    std::wstring result;
    for (auto i : v) {
        if (i >= 0 && i < static_cast<int>(numAlpha.size())) {
            result.push_back(numAlpha[i]);
        } else {
            throw cipher_error("Неверный индекс символа: " + std::to_string(i));
        }
    }
    return result;
}

// Шифрование
std::wstring modAlphaCipher::encrypt(const std::wstring& open_text)
{
    std::wstring valid_text = getValidOpenText(open_text);
    std::vector<int> work = convert(valid_text);
    int alphabetSize = numAlpha.size();
    int lettersCount = alphabetSize - 1; // количество букв (без пробела)
    
    for (unsigned i = 0; i < work.size(); i++) {
        // Для пробела (индекс 33) применяем особую логику
        if (work[i] == 33) { // пробел
            // Пробел остается пробелом при шифровании
            continue;
        } else {
            // Для букв применяем шифрование
            work[i] = (work[i] + key[i % key.size()]) % lettersCount;
        }
    }
    
    return convert(work);
}

// Дешифрование
std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text)
{
    std::wstring valid_text = getValidCipherText(cipher_text);
    std::vector<int> work = convert(valid_text);
    int alphabetSize = numAlpha.size();
    int lettersCount = alphabetSize - 1; // количество букв (без пробела)
    
    for (unsigned i = 0; i < work.size(); i++) {
        // Для пробела (индекс 33) применяем особую логику
        if (work[i] == 33) { // пробел
            // Пробел остается пробелом при дешифровании
            continue;
        } else {
            // Для букв применяем дешифрование
            work[i] = (work[i] + lettersCount - key[i % key.size()]) % lettersCount;
        }
    }
    
    return convert(work);
}
