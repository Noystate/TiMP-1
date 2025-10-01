#include <iostream>
#include <string>
#include <locale>
#include <limits>
#include "modAlphaCipher.h"
#include "TableCipher.h"

using namespace std;

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void testModAlphaCipher() {
    cout << "\n=== ТЕСТИРОВАНИЕ ШИФРА ГРОНСФЕЛЬДА ===" << endl;
    
    try {
        modAlphaCipher cipher("ПАРОЛЬ");
        string text = "ПРИВЕТ МИР ЭТО ТЕСТОВЫЙ ТЕКСТ";
        string encrypted = cipher.encrypt(text);
        string decrypted = cipher.decrypt(encrypted);
        
        cout << "Исходный:  " << text << endl;
        cout << "Зашифр:    " << encrypted << endl;
        cout << "Расшифр:   " << decrypted << endl;
        cout << "Результат: " << (text == decrypted ? "УСПЕХ" : "ОШИБКА") << endl;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void testTableCipher() {
    cout << "\n=== ТЕСТИРОВАНИЕ ТАБЛИЧНОЙ ПЕРЕСТАНОВКИ ===" << endl;
    
    try {
        TableCipher cipher("4");
        string text = "ПРИВЕТ МИР ЭТО ТЕСТ";
        string encrypted = cipher.encrypt(text);
        string decrypted = cipher.decrypt(encrypted);
        
        cout << "Исходный:  " << text << endl;
        cout << "Зашифр:    " << encrypted << endl;
        cout << "Расшифр:   " << decrypted << endl;
        cout << "Результат: " << (text == decrypted ? "УСПЕХ" : "ОШИБКА") << endl;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    cout << "=== ТЕСТИРОВАНИЕ ДВУХ ШИФРОВ ===" << endl;
    
    testModAlphaCipher();
    testTableCipher();
    
    return 0;
}
