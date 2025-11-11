#include <iostream>
#include <string>
#include <cassert>
#include <functional>
#include "modAlphaCipher.h"

using namespace std;

// Функция для проверки исключений
bool throws_cipher_error(const std::function<void()>& func) {
    try {
        func();
        return false;
    } catch (const cipher_error& e) {
        return true;
    }
}

void test_constructor() {
    cout << "=== ТЕСТИРОВАНИЕ КОНСТРУКТОРА ===" << endl;
    
    // ТЕСТ 1.1: Верный ключ
    cout << "Тест 1.1: Верный ключ 'ПАРОЛЬ'... ";
    try {
        modAlphaCipher cipher1(L"ПАРОЛЬ");
        cout << "ПРОЙДЕН" << endl;
    } catch (...) {
        cout << "ПРОВАЛЕН" << endl;
    }
    
    // ТЕСТ 1.2: Ключ с пробелами
    cout << "Тест 1.2: Ключ 'СЕКРЕТНЫЙ КЛЮЧ' (с пробелами)... ";
    try {
        modAlphaCipher cipher2(L"СЕКРЕТНЫЙ КЛЮЧ");
        cout << "ПРОЙДЕН" << endl;
    } catch (...) {
        cout << "ПРОВАЛЕН" << endl;
    }
    
    // ТЕСТ 1.3: Пустой ключ
    cout << "Тест 1.3: Пустой ключ... ";
    try {
        modAlphaCipher cipher3(L"");
        cout << "ПРОВАЛЕН - исключение не выброшено" << endl;
    } catch (const cipher_error& e) {
        cout << "ПРОЙДЕН - исключение: " << e.what() << endl;
    }
    
    // ТЕСТ 1.4: Ключ с цифрами
    cout << "Тест 1.4: Ключ 'КЛЮЧ123' (с цифрами)... ";
    try {
        modAlphaCipher cipher4(L"КЛЮЧ123");
        cout << "ПРОВАЛЕН - исключение не выброшено" << endl;
    } catch (const cipher_error& e) {
        cout << "ПРОЙДЕН - исключение: " << e.what() << endl;
    }
    
    // ТЕСТ 1.5: Ключ с латинскими буквами
    cout << "Тест 1.5: Ключ 'KEY' (латинские буквы)... ";
    try {
        modAlphaCipher cipher5(L"KEY");
        cout << "ПРОВАЛЕН - исключение не выброшено" << endl;
    } catch (const cipher_error& e) {
        cout << "ПРОЙДЕН - исключение: " << e.what() << endl;
    }
    
    // ТЕСТ 1.6: Слабый ключ (одинаковые символы)
    cout << "Тест 1.6: Слабый ключ 'ААА'... ";
    try {
        modAlphaCipher cipher6(L"ААА");
        cout << "ПРОВАЛЕН - исключение не выброшено" << endl;
    } catch (const cipher_error& e) {
        cout << "ПРОЙДЕН - исключение: " << e.what() << endl;
    }
}

void test_encrypt() {
    cout << "\n=== ТЕСТИРОВАНИЕ МЕТОДА ENCRYPT ===" << endl;
    
    // ТЕСТ 2.1: Текст без пробелов
    cout << "Тест 2.1: Текст без пробелов 'ПРИВЕТМИР'... ";
    try {
        modAlphaCipher cipher(L"КЛЮЧ");
        wstring result = cipher.encrypt(L"ПРИВЕТМИР");
        // Проверяем, что результат не пустой и содержит только допустимые символы
        if (!result.empty() && result.find_first_not_of(L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ ") == wstring::npos) {
            cout << "ПРОЙДЕН: '" << string(result.begin(), result.end()) << "'" << endl;
        } else {
            cout << "ПРОВАЛЕН: неверный результат" << endl;
        }
    } catch (const cipher_error& e) {
        cout << "ИСКЛЮЧЕНИЕ: " << e.what() << endl;
    }
    
    // ТЕСТ 2.2: Текст с пробелами
    cout << "Тест 2.2: Текст с пробелами 'ПРИВЕТ МИР'... ";
    try {
        modAlphaCipher cipher(L"КЛЮЧ");
        wstring result = cipher.encrypt(L"ПРИВЕТ МИР");
        // Проверяем, что пробел сохранился
        if (result.find(L' ') != wstring::npos) {
            cout << "ПРОЙДЕН: пробелы сохранены, результат: '" << string(result.begin(), result.end()) << "'" << endl;
        } else {
            cout << "ПРОВАЛЕН: пробелы не сохранены" << endl;
        }
    } catch (const cipher_error& e) {
        cout << "ИСКЛЮЧЕНИЕ: " << e.what() << endl;
    }
    
    // ТЕСТ 2.3: Текст в нижнем регистре
    cout << "Тест 2.3: Текст в нижнем регистре 'привет мир'... ";
    try {
        modAlphaCipher cipher(L"КЛЮЧ");
        wstring result = cipher.encrypt(L"привет мир");
        // Проверяем, что результат в верхнем регистре
        bool isUpper = true;
        for (wchar_t c : result) {
            if (c != L' ' && (c < L'А' || c > L'Я') && c != L'Ё') {
                isUpper = false;
                break;
            }
        }
        if (isUpper) {
            cout << "ПРОЙДЕН: регистр приведен к верхнему, результат: '" << string(result.begin(), result.end()) << "'" << endl;
        } else {
            cout << "ПРОВАЛЕН: регистр не приведен к верхнему" << endl;
        }
    } catch (const cipher_error& e) {
        cout << "ИСКЛЮЧЕНИЕ: " << e.what() << endl;
    }
    
    // ТЕСТ 2.4: Текст с разными пробелами
    cout << "Тест 2.4: Текст с несколькими пробелами 'ПРИВЕТ  МИР'... ";
    try {
        modAlphaCipher cipher(L"КЛЮЧ");
        wstring result = cipher.encrypt(L"ПРИВЕТ  МИР");
        // Подсчитываем пробелы
        int spaceCount = 0;
        for (wchar_t c : result) {
            if (c == L' ') spaceCount++;
        }
        if (spaceCount >= 2) {
            cout << "ПРОЙДЕН: множественные пробелы сохранены, результат: '" << string(result.begin(), result.end()) << "'" << endl;
        } else {
            cout << "ПРОВАЛЕН: множественные пробелы не сохранены" << endl;
        }
    } catch (const cipher_error& e) {
        cout << "ИСКЛЮЧЕНИЕ: " << e.what() << endl;
    }
    
    // ТЕСТ 2.5: Пустой текст
    cout << "Тест 2.5: Пустой текст... ";
    try {
        modAlphaCipher cipher(L"КЛЮЧ");
        wstring result = cipher.encrypt(L"");
        cout << "ПРОВАЛЕН - исключение не выброшено" << endl;
    } catch (const cipher_error& e) {
        cout << "ПРОЙДЕН - исключение: " << e.what() << endl;
    }
    
    // ТЕСТ 2.6: Текст только с недопустимыми символами
    cout << "Тест 2.6: Текст '123!@#' (только недопустимые символы)... ";
    try {
        modAlphaCipher cipher(L"КЛЮЧ");
        wstring result = cipher.encrypt(L"123!@#");
        cout << "ПРОВАЛЕН - исключение не выброшено" << endl;
    } catch (const cipher_error& e) {
        cout << "ПРОЙДЕН - исключение: " << e.what() << endl;
    }
    
    // ТЕСТ 2.7: Текст с игнорируемыми символами
    cout << "Тест 2.7: Текст 'ПРИВЕТ, МИР!' (с знаками препинания)... ";
    try {
        modAlphaCipher cipher(L"КЛЮЧ");
        wstring result = cipher.encrypt(L"ПРИВЕТ, МИР!");
        // Проверяем, что знаки препинания удалены
        if (result.find(L',') == wstring::npos && result.find(L'!') == wstring::npos) {
            cout << "ПРОЙДЕН: знаки препинания удалены, результат: '" << string(result.begin(), result.end()) << "'" << endl;
        } else {
            cout << "ПРОВАЛЕН: знаки препинания не удалены" << endl;
        }
    } catch (const cipher_error& e) {
        cout << "ИСКЛЮЧЕНИЕ: " << e.what() << endl;
    }
}

void test_decrypt() {
    cout << "\n=== ТЕСТИРОВАНИЕ МЕТОДА DECRYPT ===" << endl;
    
    // ТЕСТ 3.1: Корректный зашифрованный текст
    cout << "Тест 3.1: Корректный зашифрованный текст... ";
    try {
        modAlphaCipher cipher(L"КЛЮЧ");
        wstring original = L"ПРИВЕТМИР";
        wstring encrypted = cipher.encrypt(original);
        wstring decrypted = cipher.decrypt(encrypted);
        
        if (original == decrypted) {
            cout << "ПРОЙДЕН: '" << string(original.begin(), original.end()) << "' -> '" 
                 << string(encrypted.begin(), encrypted.end()) << "' -> '" 
                 << string(decrypted.begin(), decrypted.end()) << "'" << endl;
        } else {
            cout << "ПРОВАЛЕН: дешифрование не восстановило исходный текст" << endl;
        }
    } catch (const cipher_error& e) {
        cout << "ИСКЛЮЧЕНИЕ: " << e.what() << endl;
    }
    
    // ТЕСТ 3.2: Текст с пробелами
    cout << "Тест 3.2: Текст с пробелами 'ПРИВЕТ МИР'... ";
    try {
        modAlphaCipher cipher(L"КЛЮЧ");
        wstring original = L"ПРИВЕТ МИР";
        wstring encrypted = cipher.encrypt(original);
        wstring decrypted = cipher.decrypt(encrypted);
        
        if (original == decrypted) {
            cout << "ПРОЙДЕН: пробелы сохранены, полный цикл корректен" << endl;
        } else {
            cout << "ПРОВАЛЕН: пробелы не сохранены при дешифровании" << endl;
        }
    } catch (const cipher_error& e) {
        cout << "ИСКЛЮЧЕНИЕ: " << e.what() << endl;
    }
    
    // ТЕСТ 3.3: Пустой текст
    cout << "Тест 3.3: Пустой текст для дешифрования... ";
    try {
        modAlphaCipher cipher(L"КЛЮЧ");
        wstring result = cipher.decrypt(L"");
        cout << "ПРОВАЛЕН - исключение не выброшено" << endl;
    } catch (const cipher_error& e) {
        cout << "ПРОЙДЕН - исключение: " << e.what() << endl;
    }
    
    // ТЕСТ 3.4: Текст в нижнем регистре
    cout << "Тест 3.4: Зашифрованный текст в нижнем регистре... ";
    try {
        modAlphaCipher cipher(L"КЛЮЧ");
        wstring encrypted = cipher.encrypt(L"ТЕСТ");
        // "Портим" зашифрованный текст - переводим в нижний регистр
        for (wchar_t& c : encrypted) {
            if (c >= L'А' && c <= L'Я') c = c - L'А' + L'а';
            else if (c == L'Ё') c = L'ё';
        }
        wstring result = cipher.decrypt(encrypted);
        cout << "ПРОВАЛЕН - исключение не выброшено" << endl;
    } catch (const cipher_error& e) {
        cout << "ПРОЙДЕН - исключение: " << e.what() << endl;
    }
    
    // ТЕСТ 3.5: Текст с недопустимыми символами
    cout << "Тест 3.5: Зашифрованный текст 'ТЕКСТ123' (с цифрами)... ";
    try {
        modAlphaCipher cipher(L"КЛЮЧ");
        wstring result = cipher.decrypt(L"ТЕКСТ123");
        cout << "ПРОВАЛЕН - исключение не выброшено" << endl;
    } catch (const cipher_error& e) {
        cout << "ПРОЙДЕН - исключение: " << e.what() << endl;
    }
    
    // ТЕСТ 3.6: Полный цикл шифрование-дешифрование
    cout << "Тест 3.6: Полный цикл с пробелами и разным регистром... ";
    try {
        modAlphaCipher cipher(L"СЕКРЕТНЫЙКЛЮЧ");
        wstring original = L"Это тестовое сообщение с пробелами";
        wstring encrypted = cipher.encrypt(original);
        wstring decrypted = cipher.decrypt(encrypted);
        
        wstring expected = L"ЭТО ТЕСТОВОЕ СООБЩЕНИЕ С ПРОБЕЛАМИ";
        if (decrypted == expected) {
            cout << "ПРОЙДЕН: регистр и пробелы обработаны корректно" << endl;
        } else {
            cout << "ПРОВАЛЕН: ожидалось '" << string(expected.begin(), expected.end()) 
                 << "', получено '" << string(decrypted.begin(), decrypted.end()) << "'" << endl;
        }
    } catch (const cipher_error& e) {
        cout << "ИСКЛЮЧЕНИЕ: " << e.what() << endl;
    }
}

void test_additional_cases() {
    cout << "\n=== ДОПОЛНИТЕЛЬНЫЕ ТЕСТЫ ===" << endl;
    
    // Тест с длинным текстом
    cout << "Тест с длинным текстом и пробелами... ";
    try {
        modAlphaCipher cipher(L"ДЛИННЫЙКЛЮЧ");
        wstring original = L"ЭТО ДЛИННЫЙ ТЕКСТ С МНОЖЕСТВОМ ПРОБЕЛОВ И РАЗНЫМИ СЛОВАМИ";
        wstring encrypted = cipher.encrypt(original);
        wstring decrypted = cipher.decrypt(encrypted);
        
        if (original == decrypted) {
            cout << "ПРОЙДЕН: длинный текст с пробелами обработан корректно" << endl;
        } else {
            cout << "ПРОВАЛЕН: ошибка в обработке длинного текста" << endl;
        }
    } catch (const cipher_error& e) {
        cout << "ИСКЛЮЧЕНИЕ: " << e.what() << endl;
    }
    
    // Тест с ключом содержащим букву Ё
    cout << "Тест с ключом содержащим Ё... ";
    try {
        modAlphaCipher cipher(L"КЛЮЧЁЁ");
        wstring original = L"ПРИВЕТ МИР";
        wstring encrypted = cipher.encrypt(original);
        wstring decrypted = cipher.decrypt(encrypted);
        
        if (original == decrypted) {
            cout << "ПРОЙДЕН: ключ с буквой Ё работает корректно" << endl;
        } else {
            cout << "ПРОВАЛЕН: ошибка с ключом содержащим Ё" << endl;
        }
    } catch (const cipher_error& e) {
        cout << "ИСКЛЮЧЕНИЕ: " << e.what() << endl;
    }
    
    // Тест с текстом содержащим букву Ё
    cout << "Тест с текстом содержащим Ё... ";
    try {
        modAlphaCipher cipher(L"КЛЮЧ");
        wstring original = L"ЁЛКА ПАЁК";
        wstring encrypted = cipher.encrypt(original);
        wstring decrypted = cipher.decrypt(encrypted);
        
        if (original == decrypted) {
            cout << "ПРОЙДЕН: текст с буквой Ё обработан корректно" << endl;
        } else {
            cout << "ПРОВАЛЕН: ошибка с текстом содержащим Ё" << endl;
        }
    } catch (const cipher_error& e) {
        cout << "ИСКЛЮЧЕНИЕ: " << e.what() << endl;
    }
}

int main() {
    // Установка локали для работы с широкими символами
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    cout << "МОДУЛЬНОЕ ТЕСТИРОВАНИЕ MODALPHACIPHER" << endl;
    cout << "=====================================" << endl;
    
    // Запуск всех тестов
    test_constructor();
    test_encrypt();
    test_decrypt();
    test_additional_cases();
    
    cout << "\n=====================================" << endl;
    cout << "ТЕСТИРОВАНИЕ ЗАВЕРШЕНО" << endl;
    
    return 0;
}
