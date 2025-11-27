#include <iostream>
#include <string>
#include "modAlphaCipher.h"

using namespace std;

void runTests() {
    cout << "МОДУЛЬНОЕ ТЕСТИРОВАНИЕ MODALPHACIPHER" << endl;
    cout << "======================================" << endl << endl;

    // Тестирование конструктора
    cout << "=== ТЕСТИРОВАНИЕ КОНСТРУКТОРА ===" << endl;
    
    // Тест 1.1: Верный ключ
    cout << "Тест 1.1: Верный ключ 'ПАРОЛЬ'... ";
    try {
        modAlphaCipher cipher1("ПАРОЛЬ");
        cout << "ПРОЙДЕН" << endl;
    } catch (const cipher_error& e) {
        cout << "ОШИБКА: " << e.what() << endl;
    }

    // Тест 1.2: Ключ в нижнем регистре
    cout << "Тест 1.2: Ключ 'пароль' (нижний регистр)... ";
    try {
        modAlphaCipher cipher2("пароль");
        cout << "ПРОЙДЕН" << endl;
    } catch (const cipher_error& e) {
        cout << "ОШИБКА: " << e.what() << endl;
    }

    // Тест 1.3: Пустой ключ
    cout << "Тест 1.3: Пустой ключ ''... ";
    try {
        modAlphaCipher cipher3("");
        cout << "ОШИБКА: должно быть исключение" << endl;
    } catch (const cipher_error& e) {
        cout << "ПРОЙДЕН - исключение: " << e.what() << endl;
    }

    // Тест 1.4: Ключ с цифрами
    cout << "Тест 1.4: Ключ с цифрами 'ПАРОЛЬ123'... ";
    try {
        modAlphaCipher cipher4("ПАРОЛЬ123");
        cout << "ОШИБКА: должно быть исключение" << endl;
    } catch (const cipher_error& e) {
        cout << "ПРОЙДЕН - исключение: " << e.what() << endl;
    }

    // Тест 1.5: Ключ с латинскими буквами
    cout << "Тест 1.5: Ключ с латинскими буквами 'KEY'... ";
    try {
        modAlphaCipher cipher5("KEY");
        cout << "ОШИБКА: должно быть исключение" << endl;
    } catch (const cipher_error& e) {
        cout << "ПРОЙДЕН - исключение: " << e.what() << endl;
    }

    // Тест 1.6: Слабый ключ
    cout << "Тест 1.6: Слабый ключ 'ААА'... ";
    try {
        modAlphaCipher cipher6("ААА");
        cout << "ОШИБКА: должно быть исключение" << endl;
    } catch (const cipher_error& e) {
        cout << "ПРОЙДЕН - исключение: " << e.what() << endl;
    }

    // Тест 1.7: Ключ с пробелами
    cout << "Тест 1.7: Ключ с пробелами 'СЕКРЕТНЫЙ КЛЮЧ'... ";
    try {
        modAlphaCipher cipher7("СЕКРЕТНЫЙ КЛЮЧ");
        cout << "ОШИБКА: должно быть исключение" << endl;
    } catch (const cipher_error& e) {
        cout << "ПРОЙДЕН - исключение: " << e.what() << endl;
    }

    // Тест 1.8: Ключ со знаками препинания
    cout << "Тест 1.8: Ключ со знаками препинания 'КЛЮЧ!'... ";
    try {
        modAlphaCipher cipher8("КЛЮЧ!");
        cout << "ОШИБКА: должно быть исключение" << endl;
    } catch (const cipher_error& e) {
        cout << "ПРОЙДЕН - исключение: " << e.what() << endl;
    }

    cout << endl;

    // Тестирование метода encrypt
    cout << "=== ТЕСТИРОВАНИЕ МЕТОДА ENCRYPT ===" << endl;
    modAlphaCipher cipher("КЛЮЧ");

    // Тест 2.1: Текст без пробелов
    cout << "Тест 2.1: 'ПРИВЕТМИР' -> зашифрованный текст... ";
    try {
        string result = cipher.encrypt("ПРИВЕТМИР");
        cout << "ПРОЙДЕН: " << result << endl;
    } catch (const cipher_error& e) {
        cout << "ОШИБКА: " << e.what() << endl;
    }

    // Тест 2.2: Текст в нижнем регистре
    cout << "Тест 2.2: 'приветмир' -> зашифрованный текст... ";
    try {
        string result = cipher.encrypt("приветмир");
        cout << "ПРОЙДЕН: " << result << endl;
    } catch (const cipher_error& e) {
        cout << "ОШИБКА: " << e.what() << endl;
    }

    // Тест 2.3: Текст с пробелами и знаками препинания
    cout << "Тест 2.3: 'ПРИВЕТ, МИР!' -> зашифрованный текст... ";
    try {
        string result = cipher.encrypt("ПРИВЕТ, МИР!");
        cout << "ПРОЙДЕН: " << result << endl;
    } catch (const cipher_error& e) {
        cout << "ОШИБКА: " << e.what() << endl;
    }

    // Тест 2.4: Текст только с русскими буквами
    cout << "Тест 2.4: 'ПРИВЕТ' -> зашифрованный текст... ";
    try {
        string result = cipher.encrypt("ПРИВЕТ");
        cout << "ПРОЙДЕН: " << result << endl;
    } catch (const cipher_error& e) {
        cout << "ОШИБКА: " << e.what() << endl;
    }

    // Тест 2.5: Пустой текст
    cout << "Тест 2.5: Пустой текст... ";
    try {
        string result = cipher.encrypt("");
        cout << "ОШИБКА: должно быть исключение" << endl;
    } catch (const cipher_error& e) {
        cout << "ПРОЙДЕН - исключение: " << e.what() << endl;
    }

    // Тест 2.6: Текст только с недопустимыми символами
    cout << "Тест 2.6: '1231@#' -> зашифрованный текст... ";
    try {
        string result = cipher.encrypt("1231@#");
        cout << "ОШИБКА: должно быть исключение" << endl;
    } catch (const cipher_error& e) {
        cout << "ПРОЙДЕН - исключение: " << e.what() << endl;
    }

    // Тест 2.7: Текст с буквой Ё
    cout << "Тест 2.7: 'СЪЁМКА' -> зашифрованный текст... ";
    try {
        string result = cipher.encrypt("СЪЁМКА");
        cout << "ПРОЙДЕН: " << result << endl;
    } catch (const cipher_error& e) {
        cout << "ОШИБКА: " << e.what() << endl;
    }

    // Тест 2.8: Смешанный текст
    cout << "Тест 2.8: 'Hello ПРИВЕТ 123!' -> зашифрованный текст... ";
    try {
        string result = cipher.encrypt("Hello ПРИВЕТ 123!");
        cout << "ПРОЙДЕН: " << result << endl;
    } catch (const cipher_error& e) {
        cout << "ОШИБКА: " << e.what() << endl;
    }

    cout << endl;

    // Тестирование метода decrypt
    cout << "=== ТЕСТИРОВАНИЕ МЕТОДА DECRYPT ===" << endl;

    // Тест 3.1: Корректный зашифрованный текст
    cout << "Тест 3.1: Полный цикл 'ПРИВЕТМИР' -> encrypt -> decrypt... ";
    try {
        string original = "ПРИВЕТМИР";
        string encrypted = cipher.encrypt(original);
        string decrypted = cipher.decrypt(encrypted);
        if (original == decrypted) {
            cout << "ПРОЙДЕН: '" << original << "' -> '" << encrypted << "' -> '" << decrypted << "'" << endl;
        } else {
            cout << "ОШИБКА: '" << original << "' -> '" << encrypted << "' -> '" << decrypted << "'" << endl;
        }
    } catch (const cipher_error& e) {
        cout << "ОШИБКА: " << e.what() << endl;
    }

    // Тест 3.2: Текст в верхнем регистре
    cout << "Тест 3.2: Полный цикл 'ТЕСТ' -> encrypt -> decrypt... ";
    try {
        string original = "ТЕСТ";
        string encrypted = cipher.encrypt(original);
        string decrypted = cipher.decrypt(encrypted);
        if (original == decrypted) {
            cout << "ПРОЙДЕН: '" << original << "' -> '" << encrypted << "' -> '" << decrypted << "'" << endl;
        } else {
            cout << "ОШИБКА: '" << original << "' -> '" << encrypted << "' -> '" << decrypted << "'" << endl;
        }
    } catch (const cipher_error& e) {
        cout << "ОШИБКА: " << e.what() << endl;
    }

    // Тест 3.3: Пустой текст
    cout << "Тест 3.3: Пустой текст... ";
    try {
        string result = cipher.decrypt("");
        cout << "ОШИБКА: должно быть исключение" << endl;
    } catch (const cipher_error& e) {
        cout << "ПРОЙДЕН - исключение: " << e.what() << endl;
    }

    // Тест 3.4: Текст в нижнем регистре
    cout << "Тест 3.4: Текст в нижнем регистре 'зашифрованныйтекст'... ";
    try {
        string result = cipher.decrypt("зашифрованныйтекст");
        cout << "ОШИБКА: должно быть исключение" << endl;
    } catch (const cipher_error& e) {
        cout << "ПРОЙДЕН - исключение: " << e.what() << endl;
    }

    // Тест 3.5: Текст с недопустимыми символами
    cout << "Тест 3.5: Текст с цифрами 'ТЕКСТ123'... ";
    try {
        string result = cipher.decrypt("ТЕКСТ123");
        cout << "ОШИБКА: должно быть исключение" << endl;
    } catch (const cipher_error& e) {
        cout << "ПРОЙДЕН - исключение: " << e.what() << endl;
    }

    // Тест 3.6: Текст с пробелами
    cout << "Тест 3.6: Текст с пробелами 'ЗАШИФР ТЕКСТ'... ";
    try {
        string result = cipher.decrypt("ЗАШИФР ТЕКСТ");
        cout << "ОШИБКА: должно быть исключение" << endl;
    } catch (const cipher_error& e) {
        cout << "ПРОЙДЕН - исключение: " << e.what() << endl;
    }

    // Тест 3.7: Текст со знаками препинания
    cout << "Тест 3.7: Текст со знаками препинания 'ЗАШИФРОВАННЫЙ!'... ";
    try {
        string result = cipher.decrypt("ЗАШИФРОВАННЫЙ!");
        cout << "ОШИБКА: должно быть исключение" << endl;
    } catch (const cipher_error& e) {
        cout << "ПРОЙДЕН - исключение: " << e.what() << endl;
    }

    // Тест 3.8: Полный цикл шифрование-дешифрование
    cout << "Тест 3.8: Полный цикл 'ПРИВЕТМИР'... ";
    try {
        string original = "ПРИВЕТМИР";
        string encrypted = cipher.encrypt(original);
        string decrypted = cipher.decrypt(encrypted);
        if (original == decrypted) {
            cout << "ПРОЙДЕН: '" << original << "' -> '" << encrypted << "' -> '" << decrypted << "'" << endl;
        } else {
            cout << "ОШИБКА: '" << original << "' -> '" << encrypted << "' -> '" << decrypted << "'" << endl;
        }
    } catch (const cipher_error& e) {
        cout << "ОШИБКА: " << e.what() << endl;
    }

    // Тест 3.9: Текст с буквой Ё
    cout << "Тест 3.9: Текст с буквой Ё 'СЪЁМКА'... ";
    try {
        string original = "СЪЁМКА";
        string encrypted = cipher.encrypt(original);
        string decrypted = cipher.decrypt(encrypted);
        if (!decrypted.empty()) {
            cout << "ПРОЙДЕН: '" << original << "' -> '" << encrypted << "' -> '" << decrypted << "'" << endl;
        } else {
            cout << "ОШИБКА: результат пустой" << endl;
        }
    } catch (const cipher_error& e) {
        cout << "ОШИБКА: " << e.what() << endl;
    }

    cout << endl;
    cout << "=== ТЕСТИРОВАНИЕ ЗАВЕРШЕНО ===" << endl;
}

int main() {
    runTests();
    return 0;
}
