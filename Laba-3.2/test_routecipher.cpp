#include <iostream>
#include <string>
#include <cassert>
#include <functional>
#include "routecipher.h"

using namespace std;

// Функция для проверки исключений
bool throws_exception(const std::function<void()>& func) {
    try {
        func();
        return false;
    } catch (const std::exception& e) {
        return true;
    }
}

void test_constructor() {
    cout << "=== ТЕСТИРОВАНИЕ КОНСТРУКТОРА ===" << endl;
    
    // ТЕСТ 1.1: Верный ключ
    cout << "Тест 1.1: Верный ключ '3'... ";
    try {
        RouteCipher cipher1(3);
        assert(cipher1.getKey() == 3);
        cout << "ПРОЙДЕН" << endl;
    } catch (...) {
        cout << "ПРОВАЛЕН" << endl;
    }
    
    // ТЕСТ 1.2: Ключ больше длины текста
    cout << "Тест 1.2: Ключ '10' (больше длины текста)... ";
    try {
        RouteCipher cipher2(10);
        assert(cipher2.getKey() == 10);
        cout << "ПРОЙДЕН" << endl;
    } catch (...) {
        cout << "ПРОВАЛЕН" << endl;
    }
    
    // ТЕСТ 1.3: В ключе отрицательное число
    cout << "Тест 1.3: Отрицательный ключ '-5'... ";
    try {
        RouteCipher cipher3(-5);
        cout << "ПРОВАЛЕН - исключение не выброшено" << endl;
    } catch (const std::exception& e) {
        cout << "ПРОЙДЕН - исключение: " << e.what() << endl;
    }
    
    // ТЕСТ 1.4: В ключе ноль
    cout << "Тест 1.4: Ключ '0'... ";
    try {
        RouteCipher cipher4(0);
        cout << "ПРОВАЛЕН - исключение не выброшено" << endl;
    } catch (const std::exception& e) {
        cout << "ПРОЙДЕН - исключение: " << e.what() << endl;
    }
}

void test_encrypt() {
    cout << "\n=== ТЕСТИРОВАНИЕ МЕТОДА ENCRYPT ===" << endl;
    
    // ТЕСТ 2.1: Строка из прописных
    cout << "Тест 2.1: 'HELLOWORLD' -> 'HLODEORLWL'... ";
    try {
        RouteCipher cipher(3);
        string result = cipher.encrypt("HELLOWORLD");
        string expected = "HLODEORLWL";
        if (result == expected) {
            cout << "ПРОЙДЕН: " << result << endl;
        } else {
            cout << "ПРОВАЛЕН: ожидалось '" << expected << "', получено '" << result << "'" << endl;
        }
    } catch (const std::exception& e) {
        cout << "ИСКЛЮЧЕНИЕ: " << e.what() << endl;
    }
    
    // ТЕСТ 2.2: Строка из строчных
    cout << "Тест 2.2: 'helloworld' -> 'HLODEORLWL'... ";
    try {
        RouteCipher cipher(3);
        string result = cipher.encrypt("helloworld");
        string expected = "HLODEORLWL";
        if (result == expected) {
            cout << "ПРОЙДЕН: " << result << endl;
        } else {
            cout << "ПРОВАЛЕН: ожидалось '" << expected << "', получено '" << result << "'" << endl;
        }
    } catch (const std::exception& e) {
        cout << "ИСКЛЮЧЕНИЕ: " << e.what() << endl;
    }
    
    // ТЕСТ 2.3: Строка с пробелами
    cout << "Тест 2.3: 'HELLO WORLD' -> 'HLODEORLWL'... ";
    try {
        RouteCipher cipher(3);
        string result = cipher.encrypt("HELLO WORLD");
        string expected = "HLODEORLWL";
        if (result == expected) {
            cout << "ПРОЙДЕН: " << result << endl;
        } else {
            cout << "ПРОВАЛЕН: ожидалось '" << expected << "', получено '" << result << "'" << endl;
        }
    } catch (const std::exception& e) {
        cout << "ИСКЛЮЧЕНИЕ: " << e.what() << endl;
    }
    
    // ТЕСТ 2.4: Строка с цифрами
    cout << "Тест 2.4: 'TEST123' -> 'TT3E1S2'... ";
    try {
        RouteCipher cipher(3);
        string result = cipher.encrypt("TEST123");
        string expected = "TT3E1S2";
        if (result == expected) {
            cout << "ПРОЙДЕН: " << result << endl;
        } else {
            cout << "ПРОВАЛЕН: ожидалось '" << expected << "', получено '" << result << "'" << endl;
        }
    } catch (const std::exception& e) {
        cout << "ИСКЛЮЧЕНИЕ: " << e.what() << endl;
    }
    
    // ТЕСТ 2.5: Пустой текст
    cout << "Тест 2.5: Пустой текст... ";
    try {
        RouteCipher cipher(3);
        string result = cipher.encrypt("");
        cout << "ПРОВАЛЕН - исключение не выброшено" << endl;
    } catch (const std::exception& e) {
        cout << "ПРОЙДЕН - исключение: " << e.what() << endl;
    }
    
    // ТЕСТ 2.6: Нет букв (только цифры и пробелы)
    cout << "Тест 2.6: '1234 8765' -> '14628537'... ";
    try {
        RouteCipher cipher(3);
        string result = cipher.encrypt("1234 8765");
        string expected = "14628537";
        if (result == expected) {
            cout << "ПРОЙДЕН: " << result << endl;
        } else {
            cout << "ПРОВАЛЕН: ожидалось '" << expected << "', получено '" << result << "'" << endl;
        }
    } catch (const std::exception& e) {
        cout << "ИСКЛЮЧЕНИЕ: " << e.what() << endl;
    }
    
    // ТЕСТ 2.7: Текст короче ключа
    cout << "Тест 2.7: Ключ=5, текст='HI' -> 'HI'... ";
    try {
        RouteCipher cipher5(5);
        string result = cipher5.encrypt("HI");
        string expected = "HI";
        if (result == expected) {
            cout << "ПРОЙДЕН: " << result << endl;
        } else {
            cout << "ПРОВАЛЕН: ожидалось '" << expected << "', получено '" << result << "'" << endl;
        }
    } catch (const std::exception& e) {
        cout << "ИСКЛЮЧЕНИЕ: " << e.what() << endl;
    }
    
    // ТЕСТ 2.8: Текст равен ключу
    cout << "Тест 2.8: Ключ=4, текст='TEST' -> 'TEST'... ";
    try {
        RouteCipher cipher4(4);
        string result = cipher4.encrypt("TEST");
        string expected = "TEST";
        if (result == expected) {
            cout << "ПРОЙДЕН: " << result << endl;
        } else {
            cout << "ПРОВАЛЕН: ожидалось '" << expected << "', получено '" << result << "'" << endl;
        }
    } catch (const std::exception& e) {
        cout << "ИСКЛЮЧЕНИЕ: " << e.what() << endl;
    }
    
    // ТЕСТ 2.9: Длина текста кратна ключу
    cout << "Тест 2.9: Ключ=4, текст='TESTMESSAGE' -> 'TMAEEGSSETS'... ";
    try {
        RouteCipher cipher4(4);
        string result = cipher4.encrypt("TESTMESSAGE");
        string expected = "TMAEEGSSETS";
        if (result == expected) {
            cout << "ПРОЙДЕН: " << result << endl;
        } else {
            cout << "ПРОВАЛЕН: ожидалось '" << expected << "', получено '" << result << "'" << endl;
        }
    } catch (const std::exception& e) {
        cout << "ИСКЛЮЧЕНИЕ: " << e.what() << endl;
    }
}

void test_decrypt() {
    cout << "\n=== ТЕСТИРОВАНИЕ МЕТОДА DECRYPT ===" << endl;
    
    // ТЕСТ 3.1: Верный текст
    cout << "Тест 3.1: 'HLODEORLWL' -> 'HELLOWORLD'... ";
    try {
        RouteCipher cipher(3);
        string result = cipher.decrypt("HLODEORLWL");
        string expected = "HELLOWORLD";
        if (result == expected) {
            cout << "ПРОЙДЕН: " << result << endl;
        } else {
            cout << "ПРОВАЛЕН: ожидалось '" << expected << "', получено '" << result << "'" << endl;
        }
    } catch (const std::exception& e) {
        cout << "ИСКЛЮЧЕНИЕ: " << e.what() << endl;
    }
    
    // ТЕСТ 3.2: Есть строчные
    cout << "Тест 3.2: 'hlodeorlwl' -> 'HELLOWORLD'... ";
    try {
        RouteCipher cipher(3);
        string result = cipher.decrypt("hlodeorlwl");
        string expected = "HELLOWORLD";
        if (result == expected) {
            cout << "ПРОЙДЕН: " << result << endl;
        } else {
            cout << "ПРОВАЛЕН: ожидалось '" << expected << "', получено '" << result << "'" << endl;
        }
    } catch (const std::exception& e) {
        cout << "ИСКЛЮЧЕНИЕ: " << e.what() << endl;
    }
    
    // ТЕСТ 3.3: Есть пробелы
    cout << "Тест 3.3: 'HLO DEO RLW L' -> 'HELLOWORLD'... ";
    try {
        RouteCipher cipher(3);
        string result = cipher.decrypt("HLO DEO RLW L");
        string expected = "HELLOWORLD";
        if (result == expected) {
            cout << "ПРОЙДЕН: " << result << endl;
        } else {
            cout << "ПРОВАЛЕН: ожидалось '" << expected << "', получено '" << result << "'" << endl;
        }
    } catch (const std::exception& e) {
        cout << "ИСКЛЮЧЕНИЕ: " << e.what() << endl;
    }
    
    // ТЕСТ 3.4: Есть цифры
    cout << "Тест 3.4: 'TT3E1S2' -> 'TEST123'... ";
    try {
        RouteCipher cipher(3);
        string result = cipher.decrypt("TT3E1S2");
        string expected = "TEST123";
        if (result == expected) {
            cout << "ПРОЙДЕН: " << result << endl;
        } else {
            cout << "ПРОВАЛЕН: ожидалось '" << expected << "', получено '" << result << "'" << endl;
        }
    } catch (const std::exception& e) {
        cout << "ИСКЛЮЧЕНИЕ: " << e.what() << endl;
    }
    
    // ТЕСТ 3.5: Знаки препинания
    cout << "Тест 3.5: 'AB@CD#EF' -> 'ACEBDF@#'... ";
    try {
        RouteCipher cipher(3);
        string result = cipher.decrypt("AB@CD#EF");
        string expected = "ACEBDF@#";
        if (result == expected) {
            cout << "ПРОЙДЕН: " << result << endl;
        } else {
            cout << "ПРОВАЛЕН: ожидалось '" << expected << "', получено '" << result << "'" << endl;
        }
    } catch (const std::exception& e) {
        cout << "ИСКЛЮЧЕНИЕ: " << e.what() << endl;
    }
    
    // ТЕСТ 3.6: Пустой текст
    cout << "Тест 3.6: Пустой текст... ";
    try {
        RouteCipher cipher(3);
        string result = cipher.decrypt("");
        cout << "ПРОВАЛЕН - исключение не выброшено" << endl;
    } catch (const std::exception& e) {
        cout << "ПРОЙДЕН - исключение: " << e.what() << endl;
    }
    
    // ТЕСТ 3.7: Текст с пробелами
    cout << "Тест 3.7: 'TMAEEGSSETS' -> 'TESTMESSAGE'... ";
    try {
        RouteCipher cipher4(4);
        string result = cipher4.decrypt("TMAEEGSSETS");
        string expected = "TESTMESSAGE";
        if (result == expected) {
            cout << "ПРОЙДЕН: " << result << endl;
        } else {
            cout << "ПРОВАЛЕН: ожидалось '" << expected << "', получено '" << result << "'" << endl;
        }
    } catch (const std::exception& e) {
        cout << "ИСКЛЮЧЕНИЕ: " << e.what() << endl;
    }
    
    // ТЕСТ 3.8: Неполная таблица
    cout << "Тест 3.8: 'HLOEL' -> 'HOLLE'... ";
    try {
        RouteCipher cipher(3);
        string result = cipher.decrypt("HLOEL");
        string expected = "HOLLE";
        if (result == expected) {
            cout << "ПРОЙДЕН: " << result << endl;
        } else {
            cout << "ПРОВАЛЕН: ожидалось '" << expected << "', получено '" << result << "'" << endl;
        }
    } catch (const std::exception& e) {
        cout << "ИСКЛЮЧЕНИЕ: " << e.what() << endl;
    }
    
    // ТЕСТ 3.9: Длина текста кратна ключу
    cout << "Тест 3.9: Ключ=4, текст='TMAEEGSSETS' -> 'TESTMESSAGE'... ";
    try {
        RouteCipher cipher4(4);
        string result = cipher4.decrypt("TMAEEGSSETS");
        string expected = "TESTMESSAGE";
        if (result == expected) {
            cout << "ПРОЙДЕН: " << result << endl;
        } else {
            cout << "ПРОВАЛЕН: ожидалось '" << expected << "', получено '" << result << "'" << endl;
        }
    } catch (const std::exception& e) {
        cout << "ИСКЛЮЧЕНИЕ: " << e.what() << endl;
    }
}

void test_additional_cases() {
    cout << "\n=== ДОПОЛНИТЕЛЬНЫЕ ТЕСТЫ ===" << endl;
    
    // Тест на корректность шифрования/дешифрования
    cout << "Тест полного цикла шифрование-дешифрование... ";
    RouteCipher cipher(4);
    string original = "TESTMESSAGE";
    string encrypted = cipher.encrypt(original);
    string decrypted = cipher.decrypt(encrypted);
    if (original == decrypted) {
        cout << "ПРОЙДЕН: '" << original << "' -> '" << encrypted << "' -> '" << decrypted << "'" << endl;
    } else {
        cout << "ПРОВАЛЕН: '" << original << "' -> '" << encrypted << "' -> '" << decrypted << "'" << endl;
    }
    
    // Тест с разными ключами
    cout << "Тест с ключом=2... ";
    RouteCipher cipher2(2);
    string result = cipher2.encrypt("ABCD");
    string expected = "ACBD";
    if (result == expected) {
        cout << "ПРОЙДЕН: 'ABCD' -> '" << result << "'" << endl;
    } else {
        cout << "ПРОВАЛЕН: ожидалось '" << expected << "', получено '" << result << "'" << endl;
    }
    
    // Тест с ключом=1
    cout << "Тест с ключом=1... ";
    RouteCipher cipher1(1);
    string result1 = cipher1.encrypt("HELLO");
    string expected1 = "HELLO";
    if (result1 == expected1) {
        cout << "ПРОЙДЕН: 'HELLO' -> '" << result1 << "'" << endl;
    } else {
        cout << "ПРОВАЛЕН: ожидалось '" << expected1 << "', получено '" << result1 << "'" << endl;
    }
    
    // Тест с длинным текстом
    cout << "Тест с длинным текстом... ";
    RouteCipher cipher3(3);
    string long_text = "ABCDEFGHIJKLMNOPQRST";
    string long_encrypted = cipher3.encrypt(long_text);
    string long_decrypted = cipher3.decrypt(long_encrypted);
    if (long_decrypted == long_text) {
        cout << "ПРОЙДЕН: длина=20, ключ=3" << endl;
    } else {
        cout << "ПРОВАЛЕН: '" << long_text << "' -> '" << long_encrypted << "' -> '" << long_decrypted << "'" << endl;
    }
}

int main() {
    cout << "МОДУЛЬНОЕ ТЕСТИРОВАНИЕ ROUTECIPHER" << endl;
    cout << "==================================" << endl;
    
    // Запуск всех тестов
    test_constructor();
    test_encrypt();
    test_decrypt();
    test_additional_cases();
    
    cout << "\n==================================" << endl;
    cout << "ТЕСТИРОВАНИЕ ЗАВЕРШЕНО" << endl;
    
    return 0;
}
