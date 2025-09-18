#pragma once
#include <map>
#include <string>
#include <vector>
#include <stdexcept>

// Класс для реализации шифра табличной маршрутной перестановки
class modAlphaCipher
{
private:
    std::wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; // Локализация (исправлено: Щ вместо Ц, Ъ вместо Ы)
    std::map<wchar_t, int> alphaNum; // Ассоциативный массив: символ - его порядковый номер в алфавите (исправлено: <wchar_t, int>)
    std::vector<int> key; // Вектор ключ для шифрования/дешифрования
    std::vector<int> convert(const std::wstring& s); // Преобразование строки в вектор чисел
    std::wstring convert(const std::vector<int>& v); // Преобразование вектора чисел в строку

public:
    modAlphaCipher() = delete; // Удаление конструктора по умолчанию
    modAlphaCipher(const std::wstring& skey); // конструктор с параметром (исправлено: skey вместо skew)
    std::wstring encrypt(const std::wstring& open_text); // Метод для шифрования текста
    std::wstring decrypt(const std::wstring& cipher_text); // Метод для дешифрования текста
};
