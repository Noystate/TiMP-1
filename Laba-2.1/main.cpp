#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>
#include "routeCipher.h"

using namespace std;

bool isValidText(string &text) {
    for (char c : text) {
        if (!isalpha(c) && c != ' ') {
            return false;
        }
    }
    return true;
}

bool isValid(const int k, string &text) {
    if (k <= 0) {
        cout << "Ошибка: Ключ должен быть положительным числом\n";
        return false;
    }
    if (k == 1) {
        cout << "Ошибка: Ключ не может быть равен 1\n";
        return false;
    }
    if (text.empty()) {
        cout << "Ошибка: Текст не может быть пустым\n";
        return false;
    }
    if (!isValidText(text)) {
        cout << "Ошибка: Текст содержит недопустимые символы\n";
        cout << "Разрешены только английские буквы и пробелы\n";
        return false;
    }
    return true;
}

int main() {
    string text;
    int key;
    unsigned vibor;
    
    cout << "=== Шифратор табличным маршрутным шифром ===\n";
    cout << "Поддерживаются только английские буквы и пробелы\n";
    cout << "=============================================\n\n";
    
    cout << "Введите текст для шифрования: ";
    getline(cin, text);
    
    cout << "Введите количество столбцов (ключ): ";
    cin >> key;
    
    if (!isValid(key, text)) {
        cout << "Программа завершена из-за ошибки ввода.\n";
        return 1;
    }
    
    try {
        TableRouteCipher shifr(key);
        cout << "Шифратор успешно создан с ключом: " << key << "\n\n";
        
        string original_text = text;
        string current_text = text;
        
        do {
            cout << "\nВыберите операцию:\n";
            cout << "0 - Выход\n";
            cout << "1 - Зашифровать текст\n";
            cout << "2 - Расшифровать текст\n";
            cout << "Ваш выбор: ";
            cin >> vibor;
            
            if (vibor > 2) {
                cout << "Неверная операция! Пожалуйста, выберите 0, 1 или 2.\n";
            } else if (vibor > 0) {
                try {
                    if (vibor == 1) {
                        current_text = shifr.encrypt(current_text);
                        cout << "Текст успешно зашифрован!\n";
                        cout << "Зашифрованный текст: " << current_text << endl;
                    } else {
                        current_text = shifr.decrypt(current_text);
                        
                        // Восстанавливаем пробелы из оригинального текста
                        string result_with_spaces = current_text;
                        string clean_decrypted = current_text;
                        
                        // ИСПРАВЛЕННАЯ СТРОКА 89: используем size_t вместо int
                        for (size_t i = 0, decr_index = 0; i < original_text.length(); i++) {
                            if (original_text[i] == ' ') {
                                // ИСПРАВЛЕННАЯ СТРОКА 91: используем size_t вместо int
                                if (decr_index < clean_decrypted.length()) {
                                    result_with_spaces.insert(result_with_spaces.find(clean_decrypted[decr_index]), 1, ' ');
                                }
                            } else {
                                decr_index++;
                            }
                        }
                        
                        cout << "Текст успешно расшифрован!\n";
                        cout << "Расшифрованный текст: " << result_with_spaces << endl;
                        current_text = clean_decrypted;
                    }
                } catch (const exception& e) {
                    cout << "Ошибка при выполнении операции: " << e.what() << endl;
                }
            }
        } while (vibor != 0);
        
        cout << "Программа завершена. До свидания!\n";
        
    } catch (const exception& e) {
        cout << "Ошибка при создании шифратора: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
