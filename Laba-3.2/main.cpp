#include <iostream>
#include <string>
#include <limits>
#include "routecipher.h"

using namespace std;

bool isValidKey(int k) {
    if (k <= 0) {
        cout << "Ошибка: Ключ должен быть положительным числом!\n";
        return false;
    }
    return true;
}

bool isValidText(const string &text) {
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
    cout << "=== ШИФР ТАБЛИЧНОЙ МАРШРУТНОЙ ПЕРЕСТАНОВКИ ===\n";
}

int main() {
    int key;
    unsigned choice;
    
    printHeader();
    cout << "Введите начальный ключ (количество столбцов): ";
    cin >> key;
    
    if (!isValidKey(key)) {
        return 1;
    }
    
    RouteCipher cipher(key);
    
    cout << "\nШифр успешно инициализирован!\n";
    cout << "Текущий ключ: " << cipher.getKey() << endl;
    cout << "Используйте меню для работы с программой.\n\n";
    
    do {
        printHeader();
        cout << "1. Зашифровать текст\n";
        cout << "2. Расшифровать текст\n";
        cout << "3. Изменить ключ (количество столбцов)\n";
        cout << "0. Выход\n";
        cout << "Выберите операцию: ";
        cin >> choice;
        
        if (choice == 0) {
            break;
        }
        
        switch (choice) {
            case 1: {
                string text;
                cout << "Введите текст для шифрования: ";
                clearInputBuffer();
                getline(cin, text);
                
                if (!isValidText(text)) {
                    break;
                }
                
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
                
                if (!isValidText(text)) {
                    break;
                }
                
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
            
            case 3: {
                int newKey;
                cout << "Введите новый ключ (количество столбцов): ";
                cin >> newKey;
                
                if (isValidKey(newKey)) {
                    cipher.setKey(newKey);
                    cout << "Ключ успешно изменен на: " << newKey << endl;
                }
                break;
            }
            
            default:
                cout << "Неверная операция!\n";
                break;
        }
        
        cout << endl;
        
    } while (choice != 0);
    
    cout << "Выход из программы.\n";
    return 0;
}
