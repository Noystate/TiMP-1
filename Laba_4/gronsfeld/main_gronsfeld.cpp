/**
 * @file main_gronsfeld.cpp
 * @author Артёмка
 * @version 1.0
 * @date 2025
 * @brief Главный модуль программы для работы с шифром Гронсфельда
 */

#include <iostream>
#include <string>
#include <limits>
#include "modAlphaCipher.h"

using namespace std;

bool isValidKey(const string& key) {
    if (key.empty()) {
        cout << "Ошибка: Ключ не может быть пустым!\n";
        return false;
    }
    for (char c : key) {
        if (!isdigit(c)) {
            cout << "Ошибка: Ключ должен содержать только цифры!\n";
            return false;
        }
    }
    return true;
}

bool isValidText(const string& text) {
    if (text.empty()) {
        cout << "Ошибка: Текст не может быть пустым!\n";
        return false;
    }
    return true;
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void printHeader() {
    cout << "=== ШИФР ГРОНСФЕЛЬДА ===\n";
}

int main() {
    string key;
    unsigned choice;
    
    printHeader();
    cout << "Введите ключ (только цифры): ";
    cin >> key;
    
    if (!isValidKey(key)) {
        return 1;
    }
    
    try {
        modAlphaCipher cipher(key);
        
        cout << "\nШифр успешно инициализирован!\n";
        
        do {
            printHeader();
            cout << "1. Зашифровать текст\n";
            cout << "2. Расшифровать текст\n";
            cout << "0. Выход\n";
            cout << "Выберите операцию: ";
            cin >> choice;
            
            if (choice == 0) break;
            
            switch (choice) {
                case 1: {
                    string text;
                    cout << "Введите текст для шифрования: ";
                    clearInputBuffer();
                    getline(cin, text);
                    
                    if (!isValidText(text)) break;
                    
                    try {
                        string encrypted = cipher.encrypt(text);
                        cout << "\n--- Результат шифрования ---\n";
                        cout << "Исходный текст: " << text << endl;
                        cout << "Зашифрованный текст: " << encrypted << endl;
                        cout << "\nНажмите Enter для продолжения...";
                        clearInputBuffer();
                    } catch (const exception& e) {
                        cout << "Ошибка: " << e.what() << endl;
                    }
                    break;
                }
                
                case 2: {
                    string text;
                    cout << "Введите текст для расшифрования: ";
                    clearInputBuffer();
                    getline(cin, text);
                    
                    if (!isValidText(text)) break;
                    
                    try {
                        string decrypted = cipher.decrypt(text);
                        cout << "\n--- Результат расшифрования ---\n";
                        cout << "Зашифрованный текст: " << text << endl;
                        cout << "Расшифрованный текст: " << decrypted << endl;
                        cout << "\nНажмите Enter для продолжения...";
                        clearInputBuffer();
                    } catch (const exception& e) {
                        cout << "Ошибка: " << e.what() << endl;
                    }
                    break;
                }
                
                default:
                    cout << "Неверная операция!\n";
                    break;
            }
            
            cout << endl;
            
        } while (choice != 0);
        
    } catch (const exception& e) {
        cout << "Ошибка при создании шифратора: " << e.what() << endl;
        return 1;
    }
    
    cout << "Выход из программы.\n";
    return 0;
}
