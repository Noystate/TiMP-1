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
    std::wcout << L"     ШИФР ГРОНСФЕЛЬДА (С ПРОБЕЛАМИ) - МЕНЮ" << std::endl;
    std::wcout << L"═══════════════════════════════════════════════" << std::endl;
    std::wcout << L"1 - Зашифровать текст" << std::endl;
    std::wcout << L"2 - Расшифровать текст" << std::endl;
    std::wcout << L"3 - Показать пример работы с пробелами" << std::endl;
    std::wcout << L"4 - Информация о шифре" << std::endl;
  //std::wcout << L"5 - Тестирование исключений" << std::endl;
    std::wcout << L"0 - Выход" << std::endl;
    std::wcout << L"═══════════════════════════════════════════════" << std::endl;
    std::wcout << L"Выберите действие: ";
}

// Функция для шифрования текста
void encryptText() {
    std::wstring key, text;
    
    std::wcout << L"\n── ЗАШИФРОВАНИЕ ТЕКСТА ──" << std::endl;
    std::wcout << L"Введите ключ (русские буквы и пробелы): ";
    std::wcin.ignore();
    std::getline(std::wcin, key);
    
    try {
        modAlphaCipher cipher(key);
        
        std::wcout << L"Введите текст для шифрования: ";
        std::getline(std::wcin, text);
        
        std::wstring encrypted = cipher.encrypt(text);
        
        std::wcout << L"\n═══════════════════════════════════════════════" << std::endl;
        std::wcout << L"РЕЗУЛЬТАТ ШИФРОВАНИЯ:" << std::endl;
        std::wcout << L"Ключ: '" << key << L"'" << std::endl;
        std::wcout << L"Исходный текст: '" << text << L"'" << std::endl;
        std::wcout << L"Зашифрованный текст: '" << encrypted << L"'" << std::endl;
        std::wcout << L"═══════════════════════════════════════════════" << std::endl;
        
    } catch (const cipher_error& e) {
        std::wcout << L"❌ ОШИБКА: " << e.what() << std::endl;
    }
}

// Функция для расшифрования текста
void decryptText() {
    std::wstring key, text;
    
    std::wcout << L"\n── РАСШИФРОВАНИЕ ТЕКСТА ──" << std::endl;
    std::wcout << L"Введите ключ (русские буквы и пробелы): ";
    std::wcin.ignore();
    std::getline(std::wcin, key);
    
    try {
        modAlphaCipher cipher(key);
        
        std::wcout << L"Введите текст для расшифрования: ";
        std::getline(std::wcin, text);
        
        std::wstring decrypted = cipher.decrypt(text);
        
        std::wcout << L"\n═══════════════════════════════════════════════" << std::endl;
        std::wcout << L"РЕЗУЛЬТАТ РАСШИФРОВАНИЯ:" << std::endl;
        std::wcout << L"Ключ: '" << key << L"'" << std::endl;
        std::wcout << L"Зашифрованный текст: '" << text << L"'" << std::endl;
        std::wcout << L"Расшифрованный текст: '" << decrypted << L"'" << std::endl;
        std::wcout << L"═══════════════════════════════════════════════" << std::endl;
        
    } catch (const cipher_error& e) {
        std::wcout << L"❌ ОШИБКА: " << e.what() << std::endl;
    }
}

// Функция для демонстрации примеров с пробелами
void showExamples() {
    std::wcout << L"\n── ПРИМЕРЫ РАБОТЫ С ПРОБЕЛАМИ ──" << std::endl;
    
    // Пример 1 - простой текст с пробелами
    try {
        modAlphaCipher cipher1(L"СЕКРЕТНЫЙ КЛЮЧ");
        std::wstring encrypted1 = cipher1.encrypt(L"ПРИВЕТ МИР");
        std::wstring decrypted1 = cipher1.decrypt(encrypted1);
        
        std::wcout << L"\nПример 1 - Простые пробелы:" << std::endl;
        std::wcout << L"Ключ: 'СЕКРЕТНЫЙ КЛЮЧ'" << std::endl;
        std::wcout << L"Текст: 'ПРИВЕТ МИР'" << std::endl;
        std::wcout << L"Зашифровано: '" << encrypted1 << L"'" << std::endl;
        std::wcout << L"Расшифровано: '" << decrypted1 << L"'" << std::endl;
        std::wcout << L"✓ Корректность: " << (L"ПРИВЕТ МИР" == decrypted1 ? L"ДА" : L"НЕТ") << std::endl;
    } catch (const cipher_error& e) {
        std::wcout << L"Ошибка в примере 1: " << e.what() << std::endl;
    }
    
    // Пример 2 - несколько пробелов
    try {
        modAlphaCipher cipher2(L"МОЙ КЛЮЧ");
        std::wstring encrypted2 = cipher2.encrypt(L"ПРОГРАММИРОВАНИЕ НА C++");
        std::wstring decrypted2 = cipher2.decrypt(encrypted2);
        
        std::wcout << L"\nПример 2 - Несколько пробелов:" << std::endl;
        std::wcout << L"Ключ: 'МОЙ КЛЮЧ'" << std::endl;
        std::wcout << L"Текст: 'ПРОГРАММИРОВАНИЕ НА C++'" << std::endl;
        std::wcout << L"Зашифровано: '" << encrypted2 << L"'" << std::endl;
        std::wcout << L"Расшифровано: '" << decrypted2 << L"'" << std::endl;
        std::wcout << L"✓ Корректность: " << (L"ПРОГРАММИРОВАНИЕ НА " == decrypted2 ? L"ДА" : L"НЕТ") << std::endl;
        std::wcout << L"Примечание: Символы 'C++' игнорируются" << std::endl;
    } catch (const cipher_error& e) {
        std::wcout << L"Ошибка в примере 2: " << e.what() << std::endl;
    }
    
    // Пример 3 - ключ с пробелами
    try {
        modAlphaCipher cipher3(L"СЕКРЕТНЫЙ ПАРОЛЬ");
        std::wstring encrypted3 = cipher3.encrypt(L"ЭТО ТЕСТОВОЕ СООБЩЕНИЕ");
        std::wstring decrypted3 = cipher3.decrypt(encrypted3);
        
        std::wcout << L"\nПример 3 - Ключ с пробелами:" << std::endl;
        std::wcout << L"Ключ: 'СЕКРЕТНЫЙ ПАРОЛЬ'" << std::endl;
        std::wcout << L"Текст: 'ЭТО ТЕСТОВОЕ СООБЩЕНИЕ'" << std::endl;
        std::wcout << L"Зашифровано: '" << encrypted3 << L"'" << std::endl;
        std::wcout << L"Расшифровано: '" << decrypted3 << L"'" << std::endl;
        std::wcout << L"✓ Корректность: " << (L"ЭТО ТЕСТОВОЕ СООБЩЕНИЕ" == decrypted3 ? L"ДА" : L"НЕТ") << std::endl;
    } catch (const cipher_error& e) {
        std::wcout << L"Ошибка в примере 3: " << e.what() << std::endl;
    }
    
    // Пример 4 - разные регистры и пробелы
    try {
        modAlphaCipher cipher4(L"секретный ключ");
        std::wstring encrypted4 = cipher4.encrypt(L"Привет мир как дела");
        std::wstring decrypted4 = cipher4.decrypt(encrypted4);
        
        std::wcout << L"\nПример 4 - Разные регистры:" << std::endl;
        std::wcout << L"Ключ: 'секретный ключ'" << std::endl;
        std::wcout << L"Текст: 'Привет мир как дела'" << std::endl;
        std::wcout << L"Зашифровано: '" << encrypted4 << L"'" << std::endl;
        std::wcout << L"Расшифровано: '" << decrypted4 << L"'" << std::endl;
        std::wcout << L"✓ Корректность: " << (L"ПРИВЕТ МИР КАК ДЕЛА" == decrypted4 ? L"ДА" : L"НЕТ") << std::endl;
    } catch (const cipher_error& e) {
        std::wcout << L"Ошибка в примере 4: " << e.what() << std::endl;
    }
}

// Функция для отображения информации о шифре
void showInfo() {
    std::wcout << L"\n── ИНФОРМАЦИЯ О ШИФРЕ ГРОНСФЕЛЬДА ──" << std::endl;
    std::wcout << L"Шифр Гронсфельда - это полиалфавитный шифр подстановки," << std::endl;
    std::wcout << L"упрощенная версия шифра Виженера." << std::endl;
    std::wcout << L"\nОСОБЕННОСТИ РЕАЛИЗАЦИИ:" << std::endl;
    std::wcout << L"✓ Работает с русским алфавитом (33 буквы включая Ё)" << std::endl;
    std::wcout << L"✓ Поддерживает ПРОБЕЛЫ в тексте и ключе" << std::endl;
    std::wcout << L"✓ Регистр автоматически приводится к верхнему" << std::endl;
    std::wcout << L"✓ Не-буквенные символы (кроме пробелов) игнорируются" << std::endl;
    std::wcout << L"✓ Пробелы не шифруются, остаются на своих местах" << std::endl;
    std::wcout << L"✓ Ключ может содержать русские буквы и пробелы" << std::endl;
    std::wcout << L"\nПринцип работы с пробелами:" << std::endl;
    std::wcout << L"• Пробел имеет фиксированный индекс 33 в алфавите" << std::endl;
    std::wcout << L"• При шифровании пробел остается пробелом" << std::endl;
    std::wcout << L"• При дешифровании пробел также остается пробелом" << std::endl;
    std::wcout << L"• Пробелы в ключе участвуют в формировании числового вектора" << std::endl;
}

// Функция для тестирования исключений
void testExceptions() {
    std::wcout << L"\n── ТЕСТИРОВАНИЕ ИСКЛЮЧЕНИЙ ──" << std::endl;
    
    std::wcout << L"\n1. Тест пустого ключа:" << std::endl;
    try {
        modAlphaCipher cipher1(L"");
    } catch (const cipher_error& e) {
        std::wcout << L"✓ Поймано исключение: " << e.what() << std::endl;
    }
    
    std::wcout << L"\n2. Тест ключа с недопустимыми символами:" << std::endl;
    try {
        modAlphaCipher cipher2(L"КЛЮЧ123");
    } catch (const cipher_error& e) {
        std::wcout << L"✓ Поймано исключение: " << e.what() << std::endl;
    }
    
    std::wcout << L"\n3. Тест пустого текста для шифрования:" << std::endl;
    try {
        modAlphaCipher cipher3(L"КЛЮЧ");
        cipher3.encrypt(L"");
    } catch (const cipher_error& e) {
        std::wcout << L"✓ Поймано исключение: " << e.what() << std::endl;
    }
    
    std::wcout << L"\n4. Тест текста только с недопустимыми символами:" << std::endl;
    try {
        modAlphaCipher cipher4(L"КЛЮЧ");
        cipher4.encrypt(L"123!@#");
    } catch (const cipher_error& e) {
        std::wcout << L"✓ Поймано исключение: " << e.what() << std::endl;
    }
    
    std::wcout << L"\n5. Тест зашифрованного текста в нижнем регистре:" << std::endl;
    try {
        modAlphaCipher cipher5(L"КЛЮЧ");
        std::wstring encrypted = cipher5.encrypt(L"ТЕСТ");
        // "Портим" зашифрованный текст
        if (!encrypted.empty()) {
            encrypted[0] = L'т'; // меняем на строчную
        }
        cipher5.decrypt(encrypted);
    } catch (const cipher_error& e) {
        std::wcout << L"✓ Поймано исключение: " << e.what() << std::endl;
    }
}

int main() {
    setRussianLocale();
    
    std::wcout << L"████████████████████████████████████████████████" << std::endl;
    std::wcout << L"█                                            █" << std::endl;
    std::wcout << L"█        ШИФРОВАЛЬЩИК ГРОНСФЕЛЬДА           █" << std::endl;
    std::wcout << L"█      с поддержкой ПРОБЕЛОВ                █" << std::endl;
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
            case 5:
                testExceptions();
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
