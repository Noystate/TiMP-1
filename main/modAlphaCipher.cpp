#include "modAlphaCipher.h"
#include <locale>
#include <codecvt>
#include <algorithm>
#include <cwctype> // Добавлен для std::towupper

modAlphaCipher::modAlphaCipher(const std::wstring& skey)
{
    // установка локали
    std::locale::global(std::locale(""));
    // заполняем ассоциативный массив
    for (size_t i = 0; i < numAlpha.size(); i++) { // Исправлено: size_t
        alphaNum[numAlpha[i]] = i; // сопоставляем символ с его порядковым номером в алфавите
    }
    key = convert(skey); // преобразуем строковой ключ в числовой вектор и сохраняем его
}

// реализация метода шифрования
std::wstring modAlphaCipher::encrypt(const std::wstring& open_text)
{
    std::vector<int> work = convert(open_text);
    for (size_t i = 0; i < work.size(); i++) { // Исправлено: size_t
        work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}

// реализация метода дешифрования
std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text)
{
    std::vector<int> work = convert(cipher_text);
    for (size_t i = 0; i < work.size(); i++) { // Исправлено: size_t
        work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}

// реализация метода преобразования строки в вектор чисел
std::vector<int> modAlphaCipher::convert(const std::wstring& s)
{
    std::vector<int> result;
    for (auto c : s) {
        // Приводим символ к верхнему регистру для единообразия
        wchar_t upper_c = std::towupper(c); // Исправлено: wchar_t и std::towupper
        if (alphaNum.find(upper_c) != alphaNum.end()) {
            result.push_back(alphaNum[upper_c]); // Исправлено: alphaNum
        }
    }
    return result;
}

// реализация метода преобразования вектора чисел в строку
std::wstring modAlphaCipher::convert(const std::vector<int>& v)
{
    std::wstring result;
    for (auto i : v) {
        if (i >= 0 && i < static_cast<int>(numAlpha.size())) {
            result += numAlpha[i];
        }
    }
    return result;
}
