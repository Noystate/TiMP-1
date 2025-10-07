#include "modAlphaCipher.h"
#include <algorithm>
#include <iostream>

// Конструктор с установкой локали
modAlphaCipher::modAlphaCipher(const std::wstring& skey) : loc("ru_RU.UTF-8")
{
    // Инициализация алфавита и ассоциативного массива
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

// Валидация ключа
std::wstring modAlphaCipher::getValidKey(const std::wstring& s)
{
    if (s.empty()) {
        throw cipher_error("Пустой ключ");
    }
    
    std::wstring tmp(s);
    for (auto& c : tmp) {
        if (!isRussianLetter(c)) {
            throw cipher_error("Ключ содержит недопустимые символы");
        }
        // Приводим к верхнему регистру
        if (c >= L'а' && c <= L'я') {
            c = c - L'а' + L'А';
        } else if (c == L'ё') {
            c = L'Ё';
        }
    }
    return tmp;
}

// Валидация открытого текста
std::wstring modAlphaCipher::getValidOpenText(const std::wstring& s)
{
    std::wstring tmp;
    for (auto c : s) {
        if (isRussianLetter(c)) {
            // Приводим к верхнему регистру
            if (c >= L'а' && c <= L'я') {
                tmp.push_back(c - L'а' + L'А');
            } else if (c == L'ё') {
                tmp.push_back(L'Ё');
            } else {
                tmp.push_back(c);
            }
        }
        // Игнорируем не-буквы
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
        if (!isRussianLetter(c) || !isRussianUpperCase(c)) {
            throw cipher_error("Зашифрованный текст содержит недопустимые символы");
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
        work[i] = (work[i] + key[i % key.size()]) % numAlpha.size();
    }
    
    return convert(work);
}

// Дешифрование
std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text)
{
    std::wstring valid_text = getValidCipherText(cipher_text);
    std::vector<int> work = convert(valid_text);
    
    for (unsigned i = 0; i < work.size(); i++) {
        work[i] = (work[i] + numAlpha.size() - key[i % key.size()]) % numAlpha.size();
    }
    
    return convert(work);
}
