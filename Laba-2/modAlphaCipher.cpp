#include "modAlphaCipher.h"
#include <algorithm>
#include <iostream>

// Конструктор с установкой локали
modAlphaCipher::modAlphaCipher(const std::wstring& skey) : loc("ru_RU.UTF-8")
{
    // Инициализация алфавита и ассоциативного массива
    // Теперь алфавит включает пробел как последний символ (индекс 33)
    for (unsigned i = 0; i < numAlpha.size(); i++) {
        alphaNum[numAlpha[i]] = i;
    }
    
    std::wstring valid_key = getValidKey(skey);
    key = convert(valid_key);
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

// Валидация ключа
std::wstring modAlphaCipher::getValidKey(const std::wstring& s)
{
    if (s.empty()) {
        throw cipher_error("Пустой ключ");
    }
    
    std::wstring tmp;
    for (auto c : s) {
        if (isRussianLetter(c) || isSpace(c)) {
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
    std::wstring tmp;
    for (auto c : s) {
        if (isRussianLetter(c) || isSpace(c)) {
            // Приводим к верхнему регистру
            if (c >= L'а' && c <= L'я') {
                tmp.push_back(c - L'а' + L'А');
            } else if (c == L'ё') {
                tmp.push_back(L'Ё');
            } else {
                tmp.push_back(c);
            }
        }
        // Игнорируем другие символы (цифры, знаки препинания и т.д.)
    }
    
    if (tmp.empty()) {
        throw cipher_error("Пустой открытый текст");
    }
    return tmp;
}

// Валидация зашифрованного текста
std::wstring modAlphaCipher::getValidCipherText(const std::wstring& s)
{
    if (s.empty()) {
        throw cipher_error("Пустой зашифрованный текст");
    }
    
    for (auto c : s) {
        if (!isRussianLetter(c) && !isSpace(c)) {
            throw cipher_error("Зашифрованный текст содержит недопустимые символы");
        }
        // Для зашифрованного текста требуем верхний регистр
        if (isRussianLetter(c) && !isRussianUpperCase(c)) {
            throw cipher_error("Зашифрованный текст должен быть в верхнем регистре");
        }
    }
    return s;
}

// Преобразование строки в вектор чисел
std::vector<int> modAlphaCipher::convert(const std::wstring& s)
{
    std::vector<int> result;
    for (auto c : s) {
        if (alphaNum.find(c) != alphaNum.end()) {
            result.push_back(alphaNum[c]);
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
        }
    }
    return result;
}

// Шифрование
std::wstring modAlphaCipher::encrypt(const std::wstring& open_text)
{
    std::wstring valid_text = getValidOpenText(open_text);
    std::vector<int> work = convert(valid_text);
    
    for (unsigned i = 0; i < work.size(); i++) {
        // Для пробела (индекс 33) применяем особую логику
        if (work[i] == 33) { // пробел
            // Пробел остается пробелом при шифровании
            continue;
        } else {
            work[i] = (work[i] + key[i % key.size()]) % (numAlpha.size() - 1); // -1 потому что пробел не участвует в сдвиге
        }
    }
    
    return convert(work);
}

// Дешифрование
std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text)
{
    std::wstring valid_text = getValidCipherText(cipher_text);
    std::vector<int> work = convert(valid_text);
    
    for (unsigned i = 0; i < work.size(); i++) {
        // Для пробела (индекс 33) применяем особую логику
        if (work[i] == 33) { // пробел
            // Пробел остается пробелом при дешифровании
            continue;
        } else {
            work[i] = (work[i] + (numAlpha.size() - 1) - key[i % key.size()]) % (numAlpha.size() - 1);
        }
    }
    
    return convert(work);
}
