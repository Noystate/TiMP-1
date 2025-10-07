#include <iostream>
#include <locale>
#include <codecvt>
#include "modAlphaCipher.h"

// Функция для установки локали
void setRussianLocale() {
    try {
        std::locale::global(std::locale("ru_RU.UTF-8"));
        std::wcout.imbue(std::locale());
        std::wcin.imbue(std::locale());
        std::wcerr.imbue(std::locale());
    } catch (const std::exception& e) {
        std::wcout << L"Не удалось установить локаль ru_RU.UTF-8. Используется локаль по умолчанию." << std::endl;
    }
}

// Функция для отображения меню
void showMenu() {
    std::wcout << L"\n═══════════════════════════════════════════════" << std::endl;
    std::wcout << L"         ШИФР ГРОНСФЕЛЬДА - МЕНЮ" << std::endl;
    std::wcout << L"═══════════════════════════════════════════════" << std::endl;
    std::wcout << L"1 - Зашифровать текст" << std::endl;
    std::wcout << L"2 - Расшифровать текст" << std::endl;
    std::wcout << L"3 - Показать пример работы" << std::endl;
    std::wcout << L"4 - Информация о шифре" << std::endl;
    std::wcout << L"0 - Выход" << std::endl;
    std::wcout << L"═══════════════════════════════════════════════" << std::endl;
    std::wcout << L"Выберите действие: ";
}

// Функция для шифрования текста
void encryptText() {
    std::wstring key, text;
    
    std::wcout << L"\n── ЗАШИФРОВАНИЕ ТЕКСТА ──" << std::endl;
    std::wcout << L"Введите ключ (русские буквы): ";
    std::wcin.ignore();
    std::getline(std::wcin, key);
    
    try {
        modAlphaCipher cipher(key);
        
        std::wcout << L"Введите текст для шифрования: ";
        std::getline(std::wcin, text);
        
        std::wstring encrypted = cipher.encrypt(text);
        
        std::wcout << L"\n═══════════════════════════════════════════════" << std::endl;
        std::wcout << L"РЕЗУЛЬТАТ ШИФРОВАНИЯ:" << std::endl;
        std::wcout << L"Ключ: " << key << std::endl;
        std::wcout << L"Исходный текст: " << text << std::endl;
        std::wcout << L"Зашифрованный текст: " << encrypted << std::endl;
        std::wcout << L"═══════════════════════════════════════════════" << std::endl;
        
    } catch (const cipher_error& e) {
        std::wcout << L"❌ ОШИБКА: " << e.what() << std::endl;
    }
}

// Функция для расшифрования текста
void decryptText() {
    std::wstring key, text;
    
    std::wcout << L"\n── РАСШИФРОВАНИЕ ТЕКСТА ──" << std::endl;
    std::wcout << L"Введите ключ (русские буквы): ";
    std::wcin.ignore();
    std::getline(std::wcin, key);
    
    try {
        modAlphaCipher cipher(key);
        
        std::wcout << L"Введите текст для расшифрования: ";
        std::getline(std::wcin, text);
        
        std::wstring decrypted = cipher.decrypt(text);
        
        std::wcout << L"\n═══════════════════════════════════════════════" << std::endl;
        std::wcout << L"РЕЗУЛЬТАТ РАСШИФРОВАНИЯ:" << std::endl;
        std::wcout << L"Ключ: " << key << std::endl;
        std::wcout << L"Зашифрованный текст: " << text << std::endl;
        std::wcout << L"Расшифрованный текст: " << decrypted << std::endl;
        std::wcout << L"═══════════════════════════════════════════════" << std::endl;
        
    } catch (const cipher_error& e) {
        std::wcout << L"❌ ОШИБКА: " << e.what() << std::endl;
    }
}

// Функция для демонстрации примеров
void showExamples() {
    std::wcout << L"\n── ПРИМЕРЫ РАБОТЫ ШИФРА ──" << std::endl;
    
    // Пример 1
    try {
        modAlphaCipher cipher1(L"КЛЮЧ");
        std::wstring encrypted1 = cipher1.encrypt(L"ПРИВЕТМИР");
        std::wstring decrypted1 = cipher1.decrypt(encrypted1);
        
        std::wcout << L"\nПример 1:" << std::endl;
        std::wcout << L"Ключ: КЛЮЧ" << std::endl;
        std::wcout << L"Текст: ПРИВЕТМИР" << std::endl;
        std::wcout << L"Зашифровано: " << encrypted1 << std::endl;
        std::wcout << L"Расшифровано: " << decrypted1 << std::endl;
        std::wcout << L"✓ Корректность: " << (L"ПРИВЕТМИР" == decrypted1 ? L"ДА" : L"НЕТ") << std::endl;
    } catch (const cipher_error& e) {
        std::wcout << L"Ошибка в примере 1: " << e.what() << std::endl;
    }
    
    // Пример 2
    try {
        modAlphaCipher cipher2(L"СЕКРЕТ");
        std::wstring encrypted2 = cipher2.encrypt(L"ПРОГРАММИРОВАНИЕ");
        std::wstring decrypted2 = cipher2.decrypt(encrypted2);
        
        std::wcout << L"\nПример 2:" << std::endl;
        std::wcout << L"Ключ: СЕКРЕТ" << std::endl;
        std::wcout << L"Текст: ПРОГРАММИРОВАНИЕ" << std::endl;
        std::wcout << L"Зашифровано: " << encrypted2 << std::endl;
        std::wcout << L"Расшифровано: " << decrypted2 << std::endl;
        std::wcout << L"✓ Корректность: " << (L"ПРОГРАММИРОВАНИЕ" == decrypted2 ? L"ДА" : L"НЕТ") << std::endl;
    } catch (const cipher_error& e) {
        std::wcout << L"Ошибка в примере 2: " << e.what() << std::endl;
    }
    
    // Пример 3 с разными регистрами
    try {
        modAlphaCipher cipher3(L"пароль");
        std::wstring encrypted3 = cipher3.encrypt(L"Привет Мир!");
        std::wstring decrypted3 = cipher3.decrypt(encrypted3);
        
        std::wcout << L"\nПример 3 (разные регистры):" << std::endl;
        std::wcout << L"Ключ: пароль" << std::endl;
        std::wcout << L"Текст: Привет Мир!" << std::endl;
        std::wcout << L"Зашифровано: " << encrypted3 << std::endl;
        std::wcout << L"Расшифровано: " << decrypted3 << std::endl;
        std::wcout << L"✓ Корректность: " << (L"ПРИВЕТМИР" == decrypted3 ? L"ДА" : L"НЕТ") << std::endl;
    } catch (const cipher_error& e) {
        std::wcout << L"Ошибка в примере 3: " << e.what() << std::endl;
    }
}

// Функция для отображения информации о шифре
void showInfo() {
    std::wcout << L"\n── ИНФОРМАЦИЯ О ШИФРЕ ГРОНСФЕЛЬДА ──" << std::endl;
    std::wcout << L"Шифр Гронсфельда - это полиалфавитный шифр подстановки," << std::endl;
    std::wcout << L"упрощенная версия шифра Виженера." << std::endl;
    std::wcout << L"\nПринцип работы:" << std::endl;
    std::wcout << L"• Каждой букве алфавита сопоставляется число (А=0, Б=1, ..., Я=32)" << std::endl;
    std::wcout << L"• Буквы текста складываются с буквами ключа по модулю 33" << std::endl;
    std::wcout << L"• Ключ повторяется циклически до длины текста" << std::endl;
    std::wcout << L"\nОсобенности реализации:" << std::endl;
    std::wcout << L"• Работает с русским алфавитом (33 буквы включая Ё)" << std::endl;
    std::wcout << L"• Регистр автоматически приводится к верхнему" << std::endl;
    std::wcout << L"• Не-буквенные символы игнорируются" << std::endl;
    std::wcout << L"• Ключ должен содержать только русские буквы" << std::endl;
}

int main() {
    setRussianLocale();
    
    std::wcout << L"████████████████████████████████████████████████" << std::endl;
    std::wcout << L"█                                            █" << std::endl;
    std::wcout << L"█        ШИФРОВАЛЬЩИК ГРОНСФЕЛЬДА           █" << std::endl;
    std::wcout << L"█         для русского языка                █" << std::endl;
    std::wcout << L"█                                            █" << std::endl;
    std::wcout << L"████████████████████████████████████████████████" << std::endl;
    
    int choice;
    do {
        showMenu();
        std::wcin >> choice;
        
        switch (choice) {
            case 1:
                encryptText();
                break;
            case 2:
                decryptText();
                break;
            case 3:
                showExamples();
                break;
            case 4:
                showInfo();
                break;
            case 0:
                std::wcout << L"\nДо свидания! 👋" << std::endl;
                break;
            default:
                std::wcout << L"❌ Неверный выбор! Попробуйте снова." << std::endl;
        }
        
        if (choice != 0) {
            std::wcout << L"\nНажмите Enter для продолжения...";
            std::wcin.ignore();
            std::wcin.get();
        }
        
    } while (choice != 0);
    
    return 0;
}
