#include <iostream>
#include <string>
#include <locale>
#include "routeCipher.h"

using namespace std;

// Установка локали для русского вывода меню
void setRussianLocale() {
    setlocale(LC_ALL, "");
}

// Отображение меню на русском
void showMenu() {
    cout << "\n=== TABLE ROUTE TRANSPOSITION CIPHER ===" << endl;
    cout << "=== ШИФР ТАБЛИЧНОЙ МАРШРУТНОЙ ПЕРЕСТАНОВКИ ===" << endl;
    cout << "1. Зашифровать текст" << endl;
    cout << "2. Расшифровать текст" << endl;
    cout << "3. Показать примеры" << endl;
    cout << "4. Сменить ключ" << endl;
    cout << "0. Выход" << endl;
    cout << "Выберите действие: ";
}

// Функция для демонстрации примеров
void showExamples(RouteCipher& cipher) {
    cout << "\n--- WORK EXAMPLES ---" << endl;
    cout << "--- ПРИМЕРЫ РАБОТЫ ---" << endl;
    
    // Пример 1
    cout << "Пример 1: 'HELLO'" << endl;
    try {
        string encrypted1 = cipher.encrypt("HELLO");
        string decrypted1 = cipher.decrypt(encrypted1);
        cout << "Зашифровано: " << encrypted1 << endl;
        cout << "Расшифровано: " << decrypted1 << endl;
        cout << "✔ Корректность: " << ("HELLO" == decrypted1 ? "ДА" : "НЕТ") << endl;
    } catch (const exception& e) {
        cout << "❌ Ошибка: " << e.what() << endl;
    }
    
    // Пример 2
    cout << "\nПример 2: 'HELLO WORLD'" << endl;
    try {
        string encrypted2 = cipher.encrypt("HELLO WORLD");
        string decrypted2 = cipher.decrypt(encrypted2);
        cout << "Зашифровано: " << encrypted2 << endl;
        cout << "Расшифровано: " << decrypted2 << endl;
        cout << "✔ Корректность: " << ("HELLO WORLD" == decrypted2 ? "ДА" : "НЕТ") << endl;
    } catch (const exception& e) {
        cout << "❌ Ошибка: " << e.what() << endl;
    }
    
    // Пример 3 - тест ошибки с пустым ключом
    cout << "\nПример 3: Тест ошибки - пустой текст" << endl;
    try {
        string encrypted3 = cipher.encrypt("");
        cout << "Зашифровано: " << encrypted3 << endl;
    } catch (const exception& e) {
        cout << "❌ Ошибка: " << e.what() << endl;
    }
    
    // Пример 4 - тест ошибки с недопустимыми символами
    cout << "\nПример 4: Тест ошибки - недопустимые символы" << endl;
    try {
        string encrypted4 = cipher.encrypt("HELLO123");
        string decrypted4 = cipher.decrypt("HELLO@#$"); // Недопустимые символы
        cout << "Зашифровано: " << encrypted4 << endl;
    } catch (const exception& e) {
        cout << "❌ Ошибка: " << e.what() << endl;
    }
}

int main() {
    setRussianLocale();
    
    cout << "=== TABLE ROUTE TRANSPOSITION CIPHER ===" << endl;
    cout << "=== ШИФР ТАБЛИЧНОЙ МАРШРУТНОЙ ПЕРЕСТАНОВКИ ===" << endl;
    cout << "• English language only • Spaces supported" << endl;
    cout << "• Только английский язык • Поддержка пробелов" << endl;
    cout << "• Write route: left to right, top to bottom" << endl;
    cout << "• Read route: top to bottom, right to left" << endl;
    cout << "• Маршрут записи: слева направо, сверху вниз" << endl;
    cout << "• Маршрут считывания: сверху вниз, справа налево" << endl;
    
    // Создаем шифратор с ключом по умолчанию
    RouteCipher cipher("3");
    cout << "Ключ по умолчанию: 3 столбца" << endl;
    cout << "Default key: 3 columns" << endl;
    
    int choice;
    string input;
    
    do {
        showMenu();
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1: {
                cout << "\n--- ENCRYPTION ---" << endl;
                cout << "--- ШИФРОВАНИЕ ---" << endl;
                cout << "Текущий ключ: " << cipher.getKey() << " столбцов" << endl;
                cout << "Current key: " << cipher.getKey() << " columns" << endl;
                cout << "Введите текст: ";
                getline(cin, input);
                
                try {
                    string encrypted = cipher.encrypt(input);
                    cout << "✅ Зашифрованный текст: " << encrypted << endl;
                    cout << "✅ Encrypted text: " << encrypted << endl;
                } catch (const exception& e) {
                    cout << "❌ Ошибка шифрования: " << e.what() << endl;
                    cout << "❌ Encryption error: " << e.what() << endl;
                    cout << "Подсказка: используйте только английские буквы и пробелы" << endl;
                    cout << "Hint: use only English letters and spaces" << endl;
                }
                break;
            }
            
            case 2: {
                cout << "\n--- DECRYPTION ---" << endl;
                cout << "--- ДЕШИФРОВАНИЕ ---" << endl;
                cout << "Текущий ключ: " << cipher.getKey() << " столбцов" << endl;
                cout << "Current key: " << cipher.getKey() << " columns" << endl;
                cout << "Введите текст: ";
                getline(cin, input);
                
                try {
                    string decrypted = cipher.decrypt(input);
                    cout << "✅ Расшифрованный текст: " << decrypted << endl;
                    cout << "✅ Decrypted text: " << decrypted << endl;
                } catch (const exception& e) {
                    cout << "❌ Ошибка дешифрования: " << e.what() << endl;
                    cout << "❌ Decryption error: " << e.what() << endl;
                }
                break;
            }
            
            case 3: {
                showExamples(cipher);
                break;
            }
            
            case 4: {
                cout << "\n--- CHANGE KEY ---" << endl;
                cout << "--- СМЕНА КЛЮЧА ---" << endl;
                cout << "Текущий ключ: " << cipher.getKey() << " столбцов" << endl;
                cout << "Current key: " << cipher.getKey() << " columns" << endl;
                cout << "Введите новый ключ: ";
                string newKeyStr;
                getline(cin, newKeyStr);
                
                try {
                    // Создаем временный шифратор для валидации ключа
                    RouteCipher tempCipher(newKeyStr);
                    cipher.setKey(tempCipher.getKey());
                    cout << "✅ Новый ключ установлен: " << cipher.getKey() << " столбцов" << endl;
                    cout << "✅ New key set: " << cipher.getKey() << " columns" << endl;
                } catch (const exception& e) {
                    cout << "❌ Ошибка: " << e.what() << endl;
                    cout << "❌ Error: " << e.what() << endl;
                }
                break;
            }
            
            case 0: {
                cout << "\nВыход из программы..." << endl;
                cout << "Exiting program..." << endl;
                break;
            }
            
            default: {
                cout << "❌ Неверный выбор!" << endl;
                cout << "❌ Invalid choice!" << endl;
                break;
            }
        }
        
        if (choice != 0) {
            cout << "\nНажмите Enter для продолжения..." << endl;
            cout << "Press Enter to continue..." << endl;
            cin.get();
        }
        
    } while (choice != 0);
    
    return 0;
}
