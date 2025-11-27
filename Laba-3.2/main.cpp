#include <UnitTest++/UnitTest++.h>
#include "routecipher.h"
#include <string>

// Тестовая группа для тестирования конструктора RouteCipher
SUITE(ConstructorTest) {
    // Тест 1.1: Верный ключ
    TEST(ValidKey) {
        RouteCipher cipher(3);
        CHECK_EQUAL(3, cipher.getKey());
    }
    // Тест 1.2: Ключ больше длины текста
    TEST(LongKey) {
        RouteCipher cipher(10);
        CHECK_EQUAL(10, cipher.getKey());
    }
    // Тест 1.3: В ключе отрицательное число
    TEST(NegativeKey) {
        CHECK_THROW(RouteCipher cipher(-5), cipher_error);
    }
    // Тест 1.4: В ключе ноль
    TEST(ZeroKey) {
        CHECK_THROW(RouteCipher cipher(0), cipher_error);
    }
}

// Тестовая группа для тестирования метода encrypt
SUITE(EncryptTest) {
    // Тест 2.1: Строка из прописных
    TEST(UpperCaseString) {
        RouteCipher cipher(3);
        CHECK_EQUAL("HLODEORLWL", cipher.encrypt("HELLOWORLD"));
    }
    // Тест 2.2: Строка из строчных
    TEST(LowerCaseString) {
        RouteCipher cipher(3);
        CHECK_EQUAL("HLODEORLWL", cipher.encrypt("helloworld"));
    }
    // Тест 2.3: Строка с пробелами
    TEST(StringWithSpaces) {
        RouteCipher cipher(3);
        CHECK_EQUAL("HLODEORLWL", cipher.encrypt("HELLO WORLD"));
    }
    // Тест 2.4: Строка с цифрами
    TEST(StringWithDigits) {
        RouteCipher cipher(3);
        CHECK_EQUAL("TT3E1S2", cipher.encrypt("TEST123"));
    }
    // Тест 2.5: Пустой текст
    TEST(EmptyString) {
        RouteCipher cipher(3);
        CHECK_THROW(cipher.encrypt(""), cipher_error);
    }
    // Тест 2.6: Нет букв
    TEST(NoLetters) {
        RouteCipher cipher(3);
        CHECK_EQUAL("14628537", cipher.encrypt("1234 8765"));
    }
    // Тест 2.7: Текст короче ключа
    TEST(TextShorterThanKey) {
        RouteCipher cipher(5);
        CHECK_EQUAL("HI", cipher.encrypt("HI"));
    }
    // Тест 2.8: Текст равен ключу
    TEST(TextEqualsKey) {
        RouteCipher cipher(4);
        CHECK_EQUAL("TEST", cipher.encrypt("TEST"));
    }
    // Тест 2.9: Длина текста кратна ключу
    TEST(TextLengthMultipleOfKey) {
        RouteCipher cipher(4);
        CHECK_EQUAL("TMAEEGSSETS", cipher.encrypt("TESTMESSAGE"));
    }
}

// Тестовая группа для тестирования метода decrypt
SUITE(DecryptTest) {
    // Тест 3.1: Верный текст
    TEST(ValidText) {
        RouteCipher cipher(3);
        CHECK_EQUAL("HELLOWORLD", cipher.decrypt("HLODEORLWL"));
    }
    // Тест 3.2: Есть строчные
    TEST(HasLowerCase) {
        RouteCipher cipher(3);
        CHECK_EQUAL("HELLOWORLD", cipher.decrypt("hlodeorlwl"));
    }
    // Тест 3.3: Есть пробелы
    TEST(HasSpaces) {
        RouteCipher cipher(3);
        CHECK_EQUAL("HELLOWORLD", cipher.decrypt("HLO DEO RLWL"));
    }
    // Тест 3.4: Есть цифры
    TEST(HasDigits) {
        RouteCipher cipher(3);
        CHECK_EQUAL("TEST123", cipher.decrypt("TT3E1S2"));
    }
    // Тест 3.5: Знаки препинания
    TEST(HasPunctuation) {
        RouteCipher cipher(3);
        CHECK_EQUAL("ACEBDF@#", cipher.decrypt("AB@CD#EF"));
    }
    // Тест 3.6: Пустой текст
    TEST(EmptyString) {
        RouteCipher cipher(3);
        CHECK_THROW(cipher.decrypt(""), cipher_error);
    }
    // Тест 3.7: Текст с пробелами
    TEST(TextWithSpaces) {
        RouteCipher cipher(4);
        CHECK_EQUAL("TESTMESSAGE", cipher.decrypt("TMAEEGSSETS"));
    }
    // Тест 3.8: Неполная таблица
    TEST(IncompleteTable) {
        RouteCipher cipher(3);
        CHECK_EQUAL("HOLLE", cipher.decrypt("HLOEL"));
    }
    // Тест 3.9: Табличный шифр - восстановление с заполнением
    TEST(TableCipherWithPaddingDecrypt) {
        RouteCipher cipher(4);
        CHECK_EQUAL("TESTMESSAGEX", cipher.decrypt("TMAEEGSSETSX"));
    }
}

// Главная функция программы
int main() {
    return UnitTest::RunAllTests();
}
