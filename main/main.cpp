#include <iostream>
#include <string>
#include <locale>
#include <limits>
#include <cctype>
#include "modAlphaCipher.h"
#include "TableCipher.h"

using namespace std;

// Функция для очистки буфера ввода
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Функция для установки русской локали
void setRussianLocale() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    cout.imbue(locale("ru_RU.UTF-8"));
    cin.imbue(locale("ru_RU.UTF-8"));
}

// Функция для отображения главного меню
void displayMainMenu() {
    setRussianLocale();
    cout << "\n=== ГЛАВНОЕ МЕНЮ ===" << endl;
    cout << "1. Шифр Гронсфельда" << endl;
    cout << "2. Табличная перестановка" << endl;
    cout << "3. Сравнить оба шифра" << endl;
    cout << "4. Демонстрация работы с пробелами" << endl;
    cout << "0. Выход" << endl;
    cout << "Выберите опцию: ";
}

// Функция для отображения меню операций
void displayOperationMenu(const string& cipherName) {
    setRussianLocale();
    cout << "\n=== " << cipherName << " ===" << endl;
    cout << "1. Зашифровать текст" << endl;
    cout << "2. Расшифровать текст" << endl;
    cout << "3. Вернуться в главное меню" << endl;
    cout << "Выберите операцию: ";
}

// Функция для работы с шифром Гронсфельда
void gronsfeldMode() {
    setRussianLocale();
    
    string key;
    cout << "Введите ключ для шифра Гронсфельда: ";
    getline(cin, key);
    
    try {
        modAlphaCipher cipher(key);
        cout << "✓ Шифр Гронсфельда инициализирован" << endl;
        
        int operation;
        do {
            displayOperationMenu("ШИФР ГРОНСФЕЛЬДА");
            cin >> operation;
            clearInputBuffer();
            
            switch (operation) {
                case 1: {
                    setRussianLocale();
                    string text;
                    cout << "Введите текст для шифрования: ";
                    getline(cin, text);
                    
                    try {
                        string encrypted = cipher.encrypt(text);
                        cout << "✓ Зашифрованный текст: " << encrypted << endl;
                    } catch (const exception& e) {
                        setRussianLocale();
                        cout << "✗ Ошибка шифрования: " << e.what() << endl;
                    }
                    break;
                }
                    
                case 2: {
                    setRussianLocale();
                    string text;
                    cout << "Введите текст для расшифрования: ";
                    getline(cin, text);
                    
                    try {
                        string decrypted = cipher.decrypt(text);
                        cout << "✓ Расшифрованный текст: " << decrypted << endl;
                    } catch (const exception& e) {
                        setRussianLocale();
                        cout << "✗ Ошибка расшифрования: " << e.what() << endl;
                    }
                    break;
                }
                    
                case 3:
                    setRussianLocale();
                    cout << "Возврат в главное меню..." << endl;
                    break;
                    
                default:
                    setRussianLocale();
                    cout << "Неверный выбор. Попробуйте снова." << endl;
            }
        } while (operation != 3);
        
    } catch (const exception& e) {
        setRussianLocale();
        cout << "✗ Ошибка инициализации шифра: " << e.what() << endl;
        cout << "Нажмите Enter для продолжения...";
        clearInputBuffer();
    }
}

// Функция для работы с табличной перестановкой
void tableCipherMode() {
    setRussianLocale();
    
    string key;
    cout << "Введите ключ (количество столбцов) для табличной перестановки: ";
    getline(cin, key);
    
    try {
        TableCipher cipher(key);
        cout << "✓ Табличная перестановка инициализирована с ключом: " << cipher.getKey() << endl;
        
        int operation;
        do {
            displayOperationMenu("ТАБЛИЧНАЯ ПЕРЕСТАНОВКА");
            cin >> operation;
            clearInputBuffer();
            
            switch (operation) {
                case 1: {
                    setRussianLocale();
                    string text;
                    cout << "Введите текст для шифрования: ";
                    getline(cin, text);
                    
                    try {
                        string encrypted = cipher.encrypt(text);
                        cout << "✓ Зашифрованный текст: " << encrypted << endl;
                    } catch (const exception& e) {
                        setRussianLocale();
                        cout << "✗ Ошибка шифрования: " << e.what() << endl;
                    }
                    break;
                }
                    
                case 2: {
                    setRussianLocale();
                    string text;
                    cout << "Введите текст для расшифрования: ";
                    getline(cin, text);
                    
                    try {
                        string decrypted = cipher.decrypt(text);
                        cout << "✓ Расшифрованный текст: " << decrypted << endl;
                    } catch (const exception& e) {
                        setRussianLocale();
                        cout << "✗ Ошибка расшифрования: " << e.what() << endl;
                    }
                    break;
                }
                    
                case 3:
                    setRussianLocale();
                    cout << "Возврат в главное меню..." << endl;
                    break;
                    
                default:
                    setRussianLocale();
                    cout << "Неверный выбор. Попробуйте снова." << endl;
            }
        } while (operation != 3);
        
    } catch (const exception& e) {
        setRussianLocale();
        cout << "✗ Ошибка инициализации шифра: " << e.what() << endl;
        cout << "Нажмите Enter для продолжения...";
        clearInputBuffer();
    }
}

// Функция для сравнения обоих шифров
void compareCiphers() {
    setRussianLocale();
    
    cout << "\n=== СРАВНЕНИЕ ШИФРОВ ===" << endl;
    
    string text;
    cout << "Введите текст для сравнения: ";
    getline(cin, text);
    
    string key1, key2;
    cout << "Введите ключ для Гронсфельда: ";
    getline(cin, key1);
    cout << "Введите ключ для табличной перестановки: ";
    getline(cin, key2);
    
    try {
        modAlphaCipher cipher1(key1);
        TableCipher cipher2(key2);
        
        string encrypted1 = cipher1.encrypt(text);
        string encrypted2 = cipher2.encrypt(text);
        
        string decrypted1 = cipher1.decrypt(encrypted1);
        string decrypted2 = cipher2.decrypt(encrypted2);
        
        setRussianLocale();
        cout << "\n--- РЕЗУЛЬТАТЫ СРАВНЕНИЯ ---" << endl;
        cout << "Исходный текст: " << text << endl;
        cout << endl;
        
        cout << "ШИФР ГРОНСФЕЛЬДА:" << endl;
        cout << "  Ключ: " << key1 << endl;
        cout << "  Зашифрованный: " << encrypted1 << endl;
        cout << "  Расшифрованный: " << decrypted1 << endl;
        cout << "  Корректность: " << (text == decrypted1 ? "✓ УСПЕХ" : "✗ ОШИБКА") << endl;
        cout << endl;
        
        cout << "ТАБЛИЧНАЯ ПЕРЕСТАНОВКА:" << endl;
        cout << "  Ключ: " << key2 << " (столбцов: " << cipher2.getKey() << ")" << endl;
        cout << "  Зашифрованный: " << encrypted2 << endl;
        cout << "  Расшифрованный: " << decrypted2 << endl;
        cout << "  Корректность: " << (text == decrypted2 ? "✓ УСПЕХ" : "✗ ОШИБКА") << endl;
        
    } catch (const exception& e) {
        setRussianLocale();
        cout << "✗ Ошибка: " << e.what() << endl;
    }
    
    cout << "\nНажмите Enter для продолжения...";
    clearInputBuffer();
}

// Функция для демонстрации работы с пробелами
void demonstrateSpaces() {
    setRussianLocale();
    
    cout << "\n=== ДЕМОНСТРАЦИЯ РАБОТЫ С ПРОБЕЛАМИ ===" << endl;
    
    string demoText = "ПРИВЕТ МИР ЭТО ТЕСТ С ПРОБЕЛАМИ";
    string key1 = "СЕКРЕТ";
    string key2 = "4";
    
    try {
        modAlphaCipher cipher1(key1);
        TableCipher cipher2(key2);
        
        cout << "Демонстрационный текст: '" << demoText << "'" << endl;
        cout << endl;
        
        // Гронсфельд
        string enc1 = cipher1.encrypt(demoText);
        string dec1 = cipher1.decrypt(enc1);
        setRussianLocale();
        cout << "Гронсфельд (ключ: " << key1 << "):" << endl;
        cout << "  Зашифрованный: '" << enc1 << "'" << endl;
        cout << "  Расшифрованный: '" << dec1 << "'" << endl;
        cout << "  Пробелы сохранились: " << (demoText == dec1 ? "✓ ДА" : "✗ НЕТ") << endl;
        cout << endl;
        
        // Табличная перестановка
        string enc2 = cipher2.encrypt(demoText);
        string dec2 = cipher2.decrypt(enc2);
        setRussianLocale();
        cout << "Табличная перестановка (ключ: " << key2 << "):" << endl;
        cout << "  Зашифрованный: '" << enc2 << "'" << endl;
        cout << "  Расшифрованный: '" << dec2 << "'" << endl;
        cout << "  Пробелы сохранились: " << (demoText == dec2 ? "✓ ДА" : "✗ НЕТ") << endl;
        
    } catch (const exception& e) {
        setRussianLocale();
        cout << "✗ Ошибка: " << e.what() << endl;
    }
    
    cout << "\nНажмите Enter для продолжения...";
    clearInputBuffer();
}

// Функция для отображения приветственного сообщения
void displayWelcomeMessage() {
    setRussianLocale();
    cout << "==========================================" << endl;
    cout << "    ПРОГРАММА ШИФРОВАНИЯ" << endl;
    cout << "==========================================" << endl;
    cout << "Поддерживаемые шифры:" << endl;
    cout << "• Шифр Гронсфельда" << endl;
    cout << "• Табличная маршрутная перестановка" << endl;
    cout << "• Работа с пробелами и русским текстом" << endl;
    cout << "==========================================" << endl;
}

// Главная функция
int main() {
    // Установка русской локали при запуске программы
    setRussianLocale();
    displayWelcomeMessage();
    
    int choice;
    do {
        displayMainMenu();
        cin >> choice;
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                gronsfeldMode();
                break;
                
            case 2:
                tableCipherMode();
                break;
                
            case 3:
                compareCiphers();
                break;
                
            case 4:
                demonstrateSpaces();
                break;
                
            case 0:
                setRussianLocale();
                cout << "\nСпасибо за использование программы! До свидания!" << endl;
                break;
                
            default:
                setRussianLocale();
                cout << "Неверный выбор. Попробуйте снова." << endl;
        }
    } while (choice != 0);
    
    return 0;
}
