#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include "routeCipher.h"

// Функции для конвертации между string и wstring
std::wstring string_to_wstring(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(str);
}

std::string wstring_to_string(const std::wstring& wstr) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wstr);
}

// Установка русской локали
void setRussianLocale() {
    try {
        std::locale::global(std::locale("ru_RU.UTF-8"));
        std::wcout.imbue(std::locale());
        std::wcin.imbue(std::locale());
    } catch (const std::exception& e) {
        std::cout << "Не удалось установить локаль, используется по умолчанию" << std::endl;
    }
}

// Отображение меню
void showMenu() {
    std::wcout << L"\n=== ШИФР МАРШРУТНОЙ ПЕРЕСТАНОВКИ ===" << std::endl;
    std::wcout << L"1. Зашифровать текст" << std::endl;
    std::wcout << L"2. Расшифровать текст" << std::endl;
    std::wcout << L"3. Показать примеры" << std::endl;
    std::wcout << L"4. Сменить ключ" << std::endl;
    std::wcout << L"0. Выход" << std::endl;
    std::wcout << L"Выберите действие: ";
}

// Основная функция программы
int main() {
    setRussianLocale();
    
    std::wcout << L"=== ШИФР МАРШРУТНОЙ ПЕРЕСТАНОВКИ ===" << std::endl;
    std::wcout << L"• Поддержка русского языка" << std::endl;
    std::wcout << L"• Буквы Ё и пробелы" << std::endl;
    
    // Создаем шифратор с ключом по умолчанию
    RouteCipher* cipher = nullptr;
    try {
        cipher = new RouteCipher("3");
        std::wcout << L"✅ Ключ установлен: 3 столбца" << std::endl;
    } catch (const cipher_error& e) {
        std::wcout << L"❌ Ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    int choice;
    do {
        showMenu();
        std::wcin >> choice;
        std::wcin.ignore(); // Очищаем буфер
        
        switch (choice) {
            case 1: { // Шифрование
                std::wstring text;
                std::wcout << L"\n--- ШИФРОВАНИЕ ---" << std::endl;
                std::wcout << L"Текущий ключ: " << cipher->getKey() << L" столбцов" << std::endl;
                std::wcout << L"Введите текст: ";
                std::getline(std::wcin, text);
                
                try {
                    std::wstring encrypted = cipher->encrypt(text);
                    std::wcout << L"✅ Зашифрованный текст: " << encrypted << std::endl;
                } catch (const cipher_error& e) {
                    std::wcout << L"❌ Ошибка: " << e.what() << std::endl;
                }
                break;
            }
            
            case 2: { // Дешифрование
                std::wstring text;
                std::wcout << L"\n--- ДЕШИФРОВАНИЕ ---" << std::endl;
                std::wcout << L"Текущий ключ: " << cipher->getKey() << L" столбцов" << std::endl;
                std::wcout << L"Введите текст: ";
                std::getline(std::wcin, text);
                
                try {
                    std::wstring decrypted = cipher->decrypt(text);
                    std::wcout << L"✅ Расшифрованный текст: " << decrypted << std::endl;
                } catch (const cipher_error& e) {
                    std::wcout << L"❌ Ошибка: " << e.what() << std::endl;
                }
                break;
            }
            
            case 3: { // Примеры
                std::wcout << L"\n--- ПРИМЕРЫ РАБОТЫ ---" << std::endl;
                try {
                    std::wstring encrypted1 = cipher->encrypt(L"ПРИВЕТ");
                    std::wstring decrypted1 = cipher->decrypt(encrypted1);
                    
                    std::wcout << L"Пример 1: 'ПРИВЕТ'" << std::endl;
                    std::wcout << L"Зашифровано: " << encrypted1 << std::endl;
                    std::wcout << L"Расшифровано: " << decrypted1 << std::endl;
                    std::wcout << L"✅ Корректность: " << (L"ПРИВЕТ" == decrypted1 ? L"ДА" : L"НЕТ") << std::endl;
                    
                    std::wcout << L"\nПример 2: 'ЁЛКА ЁЖИК'" << std::endl;
                    std::wstring encrypted2 = cipher->encrypt(L"ЁЛКА ЁЖИК");
                    std::wstring decrypted2 = cipher->decrypt(encrypted2);
                    std::wcout << L"Зашифровано: " << encrypted2 << std::endl;
                    std::wcout << L"Расшифровано: " << decrypted2 << std::endl;
                    std::wcout << L"✅ Корректность: " << (L"ЁЛКА ЁЖИК" == decrypted2 ? L"ДА" : L"НЕТ") << std::endl;
                    
                } catch (const cipher_error& e) {
                    std::wcout << L"❌ Ошибка: " << e.what() << std::endl;
                }
                break;
            }
            
            case 4: { // Смена ключа
                std::string newKey;
                std::wcout << L"\n--- СМЕНА КЛЮЧА ---" << std::endl;
                std::wcout << L"Текущий ключ: " << cipher->getKey() << L" столбцов" << std::endl;
                std::wcout << L"Введите новый ключ (число): ";
                std::string temp;
                std::getline(std::cin, temp);
                newKey = temp;
                
                try {
                    delete cipher;
                    cipher = new RouteCipher(newKey);
                    std::wcout << L"✅ Новый ключ установлен: " << cipher->getKey() << L" столбцов" << std::endl;
                } catch (const cipher_error& e) {
                    std::wcout << L"❌ Ошибка: " << e.what() << std::endl;
                    // Восстанавливаем старый ключ при ошибке
                    try {
                        cipher = new RouteCipher("3");
                    } catch (...) {
                        std::wcout << L"Критическая ошибка!" << std::endl;
                        return 1;
                    }
                }
                break;
            }
            
            case 0: // Выход
                std::wcout << L"\nДо свидания!" << std::endl;
                break;
                
            default:
                std::wcout << L"❌ Неверный выбор!" << std::endl;
        }
        
        if (choice != 0) {
            std::wcout << L"\nНажмите Enter для продолжения...";
            std::wcin.get();
        }
        
    } while (choice != 0);
    
    // Освобождаем память
    delete cipher;
    
    return 0;
}
