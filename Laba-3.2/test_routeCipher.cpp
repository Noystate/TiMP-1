#include <UnitTest++/UnitTest++.h>  // Подключение фреймворка для модульного тестирования
#include "routeCipher.h"            // Подключение заголовочного файла с классом RouteCipher
#include <string>                   // Подключение библиотеки для работы со строками
#include <iostream>                 // Подключение библиотеки для ввода/вывода

using namespace std;                // Использование стандартного пространства имен

// ============================================================================
// ПРОСТЫЕ ТЕСТЫ КОНСТРУКТОРА
// ============================================================================

SUITE(ConstructorTests)  // Группа тестов для конструктора класса
{
    // Тест: Проверка работы с корректным ключом
    TEST(ValidKey) {
        RouteCipher cipher("3");           // Создание объекта с ключом "3"
        string text = "HELLO";             // Исходный текст для шифрования
        string encrypted = cipher.encrypt(text);     // Шифрование текста
        string decrypted = cipher.decrypt(encrypted); // Дешифрование обратно
        CHECK_EQUAL("HELLO", decrypted);   // Проверка, что результат совпадает с оригиналом
    }
    
    // Тест: Ключ длиннее текста
    TEST(KeyLongerThanText) {
        RouteCipher cipher("10");          // Создание объекта с ключом "10"
        string text = "SHORT";             // Короткий текст
        string encrypted = cipher.encrypt(text);     // Шифрование
        string decrypted = cipher.decrypt(encrypted); // Дешифрование
        CHECK_EQUAL("SHORT", decrypted);   // Проверка сохранения текста
    }
    
    // Тест: Ключ равный 1 (должен вызывать исключение)
    TEST(SingleColumnKey) {
        CHECK_THROW(RouteCipher cipher("1"), cipher_error); // Проверка выброса исключения
    }
    
    // Тест: Буквенный ключ (должен вызывать исключение)
    TEST(LetterKey) {
        CHECK_THROW(RouteCipher cipher("ABC"), cipher_error); // Проверка выброса исключения
    }
    
    // Тест: Отрицательный ключ (должен вызывать исключение)
    TEST(NegativeKey) {
        CHECK_THROW(RouteCipher cipher("-5"), cipher_error); // Проверка выброса исключения
    }
    
    // Тест: Нулевой ключ (должен вызывать исключение)
    TEST(ZeroKey) {
        CHECK_THROW(RouteCipher cipher("0"), cipher_error); // Проверка выброса исключения
    }
    
    // Тест: Пустой ключ (должен вызывать исключение)
    TEST(EmptyKey) {
        CHECK_THROW(RouteCipher cipher(""), cipher_error); // Проверка выброса исключения
    }
}

// ============================================================================
// ТЕСТЫ ШИФРОВАНИЯ
// ============================================================================

SUITE(EncryptTests)  // Группа тестов для метода encrypt
{
    // Тест: Шифрование текста в верхнем регистре
    TEST(UpperCaseText) {
        RouteCipher cipher("3");           // Создание объекта с ключом "3"
        string text = "HELLO";             // Текст в верхнем регистре
        string result = cipher.encrypt(text); // Шифрование текста
        CHECK(!result.empty());            // Проверка, что результат не пустой
    }
    
    // Тест: Шифрование текста в нижнем регистре
    TEST(LowerCaseText) {
        RouteCipher cipher("3");           // Создание объекта с ключом "3"
        string text = "hello";             // Текст в нижнем регистре
        string result = cipher.encrypt(text); // Шифрование текста
        CHECK(!result.empty());            // Проверка, что результат не пустой
    }
    
    // Тест: Шифрование текста с пробелами
    TEST(TextWithSpaces) {
        RouteCipher cipher("3");           // Создание объекта с ключом "3"
        string text = "HELLO WORLD";       // Текст с пробелами
        string result = cipher.encrypt(text); // Шифрование текста
        CHECK(!result.empty());            // Проверка, что результат не пустой
    }
    
    // Тест: Шифрование текста с цифрами (должен вызывать исключение)
    TEST(TextWithNumbers) {
        RouteCipher cipher("3");           // Создание объекта с ключом "3"
        string text = "TEST123";           // Текст с цифрами
        CHECK_THROW(cipher.encrypt(text), cipher_error); // Проверка выброса исключения
    }
    
    // Тест: Шифрование пустого текста (должен вызывать исключение)
    TEST(EmptyText) {
        RouteCipher cipher("3");           // Создание объекта с ключом "3"
        string text = "";                  // Пустая строка
        CHECK_THROW(cipher.encrypt(text), cipher_error); // Проверка выброса исключения
    }
    
    // Тест: Шифрование текста короче ключа
    TEST(ShortText) {
        RouteCipher cipher("5");           // Создание объекта с ключом "5"
        string text = "HI";                // Короткий текст (2 символа)
        string result = cipher.encrypt(text); // Шифрование текста
        CHECK(!result.empty());            // Проверка, что результат не пустой
    }
}

// ============================================================================
// ТЕСТЫ ДЕШИФРОВАНИЯ
// ============================================================================

SUITE(DecryptTests)  // Группа тестов для метода decrypt
{
    // Тест: Дешифрование корректного текста
    TEST(DecryptValidText) {
        RouteCipher cipher("3");           // Создание объекта с ключом "3"
        string original = "TEST";          // Исходный текст
        string encrypted = cipher.encrypt(original); // Шифрование текста
        string decrypted = cipher.decrypt(encrypted); // Дешифрование обратно
        CHECK_EQUAL("TEST", decrypted);    // Проверка совпадения с оригиналом
    }
    
    // Тест: Дешифрование текста с пробелами
    TEST(DecryptWithSpaces) {
        RouteCipher cipher("3");           // Создание объекта с ключом "3"
        string original = "HELLO WORLD";   // Исходный текст с пробелами
        string encrypted = cipher.encrypt(original); // Шифрование текста
        string decrypted = cipher.decrypt(encrypted); // Дешифрование обратно
        CHECK_EQUAL("HELLO WORLD", decrypted); // Проверка сохранения пробелов
    }
    
    // Тест: Дешифрование пустой строки (должен вызывать исключение)
    TEST(DecryptEmpty) {
        RouteCipher cipher("3");           // Создание объекта с ключом "3"
        string text = "";                  // Пустая строка
        CHECK_THROW(cipher.decrypt(text), cipher_error); // Проверка выброса исключения
    }
    
    // Тест: Дешифрование текста с недопустимыми символами (должен вызывать исключение)
    TEST(DecryptInvalidChars) {
        RouteCipher cipher("3");           // Создание объекта с ключом "3"
        string text = "HELLO@123";         // Текст с недопустимыми символами
        CHECK_THROW(cipher.decrypt(text), cipher_error); // Проверка выброса исключения
    }
}

// ============================================================================
// ИНТЕГРАЦИОННЫЕ ТЕСТЫ
// ============================================================================

SUITE(IntegrationTests)  // Группа интеграционных тестов (полный цикл шифрование-дешифрование)
{
    // Тест: Простая строка без пробелов
    TEST(SimpleText) {
        RouteCipher cipher("3");           // Создание объекта с ключом "3"
        string original = "PROGRAMMING";   // Исходный текст
        string encrypted = cipher.encrypt(original); // Шифрование
        string decrypted = cipher.decrypt(encrypted); // Дешифрование
        CHECK_EQUAL("PROGRAMMING", decrypted); // Проверка полного восстановления
    }
    
    // Тест: Строка с пробелами
    TEST(TextWithSpaces) {
        RouteCipher cipher("4");           // Создание объекта с ключом "4"
        string original = "HELLO WORLD";   // Исходный текст с пробелами
        string encrypted = cipher.encrypt(original); // Шифрование
        string decrypted = cipher.decrypt(encrypted); // Дешифрование
        CHECK_EQUAL("HELLO WORLD", decrypted); // Проверка сохранения пробелов
    }
    
    // Тест: Длинный текст с пробелами
    TEST(LongText) {
        RouteCipher cipher("5");           // Создание объекта с ключом "5"
        string original = "THE QUICK BROWN FOX"; // Длинный исходный текст
        string encrypted = cipher.encrypt(original); // Шифрование
        string decrypted = cipher.decrypt(encrypted); // Дешифрование
        CHECK_EQUAL("THE QUICK BROWN FOX", decrypted); // Проверка полного восстановления
    }
    
    // Тест: Текст с разным регистром
    TEST(MixedCase) {
        RouteCipher cipher("3");           // Создание объекта с ключом "3"
        string original = "Hello World";   // Текст со смешанным регистром
        string encrypted = cipher.encrypt(original); // Шифрование
        string decrypted = cipher.decrypt(encrypted); // Дешифрование
        CHECK_EQUAL("HELLO WORLD", decrypted); // Проверка приведения к верхнему регистру
    }
    
    // Тест: Граничный случай (минимальный нетривиальный ключ)
    TEST(BoundaryCase) {
        RouteCipher cipher("2");           // Создание объекта с ключом "2"
        string original = "TEST";          // Исходный текст
        string encrypted = cipher.encrypt(original); // Шифрование
        string decrypted = cipher.decrypt(encrypted); // Дешифрование
        CHECK_EQUAL("TEST", decrypted);    // Проверка полного восстановления
    }
    
    // Тест: Минимальный допустимый ключ
    TEST(MinimalKey) {
        RouteCipher cipher("2");           // Создание объекта с ключом "2"
        string original = "SINGLE COLUMN"; // Исходный текст с пробелами
        string encrypted = cipher.encrypt(original); // Шифрование
        string decrypted = cipher.decrypt(encrypted); // Дешифрование
        CHECK_EQUAL("SINGLE COLUMN", decrypted); // Проверка полного восстановления
    }
    
    // Тест: Большой ключ для короткого текста
    TEST(LargeKey) {
        RouteCipher cipher("8");           // Создание объекта с ключом "8"
        string original = "SHORT";         // Короткий исходный текст
        string encrypted = cipher.encrypt(original); // Шифрование
        string decrypted = cipher.decrypt(encrypted); // Дешифрование
        CHECK_EQUAL("SHORT", decrypted);   // Проверка полного восстановления
    }
}

// ============================================================================
// ТЕСТЫ ОСОБЫХ СЛУЧАЕВ
// ============================================================================

SUITE(SpecialCasesTests)  // Группа тестов для особых случаев
{
    // Тест: Повторяющиеся символы
    TEST(RepeatingCharacters) {
        RouteCipher cipher("3");           // Создание объекта с ключом "3"
        string text = "AAAAA";             // Текст с повторяющимися символами
        string encrypted = cipher.encrypt(text); // Шифрование
        string decrypted = cipher.decrypt(encrypted); // Дешифрование
        CHECK_EQUAL("AAAAA", decrypted);   // Проверка полного восстановления
    }
    
    // Тест: Одиночный символ
    TEST(SingleCharacter) {
        RouteCipher cipher("3");           // Создание объекта с ключом "3"
        string text = "A";                 // Текст из одного символа
        string encrypted = cipher.encrypt(text); // Шифрование
        string decrypted = cipher.decrypt(encrypted); // Дешифрование
        CHECK_EQUAL("A", decrypted);       // Проверка полного восстановления
    }
    
    // Тест: Симметричность преобразований
    TEST(Symmetry) {
        RouteCipher cipher("3");           // Создание объекта с ключом "3"
        string text = "SYMMETRY TEST";     // Исходный текст
        string encrypted = cipher.encrypt(text); // Шифрование
        string decrypted = cipher.decrypt(encrypted); // Дешифрование
        CHECK_EQUAL("SYMMETRY TEST", decrypted); // Проверка симметричности
    }
    
    // Тест: Точное соответствие размеров таблицы
    TEST(ExactTableSize) {
        RouteCipher cipher("4");           // Создание объекта с ключом "4"
        string text = "ABCDEFGH";          // 8 символов = 2 строки × 4 колонки
        string encrypted = cipher.encrypt(text); // Шифрование
        string decrypted = cipher.decrypt(encrypted); // Дешифрование
        CHECK_EQUAL("ABCDEFGH", decrypted); // Проверка полного восстановления
    }
}

// ============================================================================
// ГЛАВНАЯ ФУНКЦИЯ
// ============================================================================

int main() {
    // Вывод заголовка тестирования
    cout << "=============================================" << endl;
    cout << "   ТЕСТИРОВАНИЕ МАРШРУТНОЙ ПЕРЕСТАНОВКИ" << endl;
    cout << "=============================================" << endl;
    
    // Запуск всех тестов и получение результата
    int result = UnitTest::RunAllTests();
    
    // Вывод итогов тестирования
    cout << "=============================================" << endl;
    if (result == 0) {
        cout << "✅ ВСЕ ТЕСТЫ ПРОЙДЕНЫ!" << endl;  // Все тесты успешны
    } else {
        cout << "❌ ЕСТЬ ОШИБКИ!" << endl;         // Обнаружены ошибки
    }
    cout << "=============================================" << endl;
    
    return result;  // Возврат кода результата (0 - успех, иначе - ошибки)
}
