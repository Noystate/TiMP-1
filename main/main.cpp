#include "modAlphaCipher.h"
#include <iostream>
#include <locale>
#include <codecvt>
#include <string>
#include <cwctype> // Добавлен для iswalpha

// Конвертация std::string в std::wstring (для работы с Unicode)
std::wstring string_to_wstring(const std::string& str)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter; // Исправлено: codecvt_utf8
    return converter.from_bytes(str);
}

// Конвертация std::wstring в std::string
std::string wstring_to_string(const std::wstring& wstr)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter; // Исправлено: codecvt_utf8
    return converter.to_bytes(wstr);
}

// Проверка валидности текста (только буквы)
bool isValid(const std::wstring& s)
{
    for (auto c : s) {
        if (!iswalpha(c)) {
            return false;
        }
    }
    return true;
}

int main()
{
    // Установка локали для работы с русскими символами
    setlocale(LC_ALL, "RU");
    std::locale::global(std::locale(""));
    std::wcout.imbue(std::locale());
    std::wcin.imbue(std::locale()); // Исправлено: wcin вместо win

    std::string key_str;
    std::string text_str;
    unsigned op;

    std::cout << "Шифр готов. Введите ключ: ";
    std::cin >> key_str;

    std::wstring key = string_to_wstring(key_str); // Исправлено: string_to_wstring
    if (!isValid(key)) {
        std::cerr << "Ключ недействителен\n";
        return 1;
    }
    
    std::cout << "Ключ загружен\n";
    modAlphaCipher cipher(key);

    // Основной цикл программы
    do {
        std::cout << "Шифр готов. Операция ввода (0-выход, 1-шифрование, 2-расшифровка): ";
        std::cin >> op;

        if (op > 2) {
            std::cout << "Незаконная операция\n";
        } else if (op > 0) {
            std::cout << "Шифр готов. Введите текст: ";
            std::cin.ignore();
            std::getline(std::cin, text_str);

            std::wstring text = string_to_wstring(text_str);
            if (isValid(text)) {
                if (op == 1) {
                    std::wstring encrypted = cipher.encrypt(text);
                    std::cout << "Зашифрованный текст: " << wstring_to_string(encrypted) << std::endl;
                } else {
                    std::wstring decrypted = cipher.decrypt(text);
                    std::cout << "Расшифрованный текст: " << wstring_to_string(decrypted) << std::endl;
                }
            } else {
                std::cout << "Операция прервана: неверный текст\n";
            }
        }
    } while (op != 0);

    return 0;
}
