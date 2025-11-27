// Подключение библиотеки UnitTest++ для модульного тестирования
#include <UnitTest++/UnitTest++.h>
// Подключение заголовочного файла для класса modAlphaCipher
#include "modAlphaCipher.h"

// Объявление тестовой группы (Test Suite) для тестирования ключей
SUITE(KeyTest)
{
    // Тест 1.1: Верный ключ
    TEST(ValidKey) {
        modAlphaCipher cipher("ПАРОЛЬ");
        std::string result = cipher.encrypt("ТЕСТ");
        CHECK(!result.empty());
    }
    
    // Тест 1.2: Ключ в нижнем регистре (должен преобразовываться в верхний)
    TEST(LowCaseKey) {
        modAlphaCipher cipher("пароль");
        std::string result = cipher.encrypt("ТЕСТ");
        CHECK(!result.empty());
    }
    
    // Тест 1.3: Пустой ключ - должен выбрасывать исключение
    TEST(EmptyKey) {
        CHECK_THROW(modAlphaCipher cp(""),cipher_error);
    }
    
    // Тест 1.4: Ключ с цифрами - должен выбрасывать исключение
    TEST(DigitsInKey) {
        CHECK_THROW(modAlphaCipher cp("ПАРОЛЬ123"),cipher_error);
    }
    
    // Тест 1.5: Ключ с латинскими буквами - должен выбрасывать исключение
    TEST(LatinKey) {
        CHECK_THROW(modAlphaCipher cp("KEY"),cipher_error);
    }
    
    // Тест 1.6: Слабый ключ (повторяющиеся символы) - должен выбрасывать исключение
    TEST(WeakKey) {
        CHECK_THROW(modAlphaCipher cp("ААА"),cipher_error);
    }
    
    // Тест 1.7: Ключ с пробелами - должен выбрасывать исключение
    TEST(WhitespaceInKey) {
        CHECK_THROW(modAlphaCipher cp("СЕКРЕТНЫЙ КЛЮЧ"),cipher_error);
    }
    
    // Тест 1.8: Ключ со знаками препинания - должен выбрасывать исключение
    TEST(PunctuationInKey) {
        CHECK_THROW(modAlphaCipher cp("КЛЮЧ!"),cipher_error);
    }
}

// Фикстура (вспомогательная структура) для тестов шифрования/дешифрования
struct KeyB_fixture {
    modAlphaCipher * p;
    
    KeyB_fixture() {
        p = new modAlphaCipher("КЛЮЧ");
    }
    
    ~KeyB_fixture() {
        delete p;
    }
};

// Тестовая группа для тестирования шифрования
SUITE(EncryptTest)
{
    // Тест 2.1: Текст без пробелов
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        std::string result = p->encrypt("ПРИВЕТМИР");
        CHECK(!result.empty());
    }
    
    // Тест 2.2: Текст в нижнем регистре
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        std::string result = p->encrypt("приветмир");
        CHECK(!result.empty());
    }
    
    // Тест 2.3: Текст с пробелами и знаками препинания
    TEST_FIXTURE(KeyB_fixture, StringWithWhitspaceAndPunct) {
        std::string result = p->encrypt("ПРИВЕТ, МИР!");
        CHECK(!result.empty());
    }
    
    // Тест 2.4: Текст только с русскими буквами
    TEST_FIXTURE(KeyB_fixture, RussianLettersOnly) {
        std::string original = "ПРИВЕТ";
        std::string result = p->encrypt(original);
        CHECK(!result.empty());
    }
    
    // Тест 2.5: Пустой текст - должен выбрасывать исключение
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->encrypt(""), cipher_error);
    }
    
    // Тест 2.6: Текст только с недопустимыми символами - должен выбрасывать исключение
    TEST_FIXTURE(KeyB_fixture, NoAlphaString) {
        CHECK_THROW(p->encrypt("1231@#"), cipher_error);
    }
    
    // Тест 2.7: Текст с буквой Ё
    TEST_FIXTURE(KeyB_fixture, LetterYo) {
        std::string result = p->encrypt("СЪЁМКА");
        CHECK(!result.empty());
    }
    
    // Тест 2.8: Смешанный текст
    TEST_FIXTURE(KeyB_fixture, MixedString) {
        std::string result = p->encrypt("Hello ПРИВЕТ 123!");
        CHECK(!result.empty());
    }
}

// Тестовая группа для тестирования дешифрования
SUITE(DecryptText)
{
    struct DecryptFixture {
        modAlphaCipher * p;
        DecryptFixture() { p = new modAlphaCipher("КЛЮЧ"); }
        ~DecryptFixture() { delete p; }
    };
    
    // Тест 3.1: Корректный зашифрованный текст
    TEST_FIXTURE(DecryptFixture, UpCaseString) {
        std::string original = "ПРИВЕТМИР";
        std::string encrypted = p->encrypt(original);
        std::string decrypted = p->decrypt(encrypted);
        CHECK_EQUAL(original, decrypted);
    }
    
    // Тест 3.2: Текст в верхнем регистре
    TEST_FIXTURE(DecryptFixture, ValidCipherText) {
        std::string original = "ТЕСТ";
        std::string encrypted = p->encrypt(original);
        std::string result = p->decrypt(encrypted);
        CHECK_EQUAL(original, result);
    }
    
    // Тест 3.3: Пустой текст - должен выбрасывать исключение
    TEST_FIXTURE(DecryptFixture, EmptyString) {
        CHECK_THROW(p->decrypt(""), cipher_error);
    }
    
    // Тест 3.4: Текст в нижнем регистре - должен выбрасывать исключение
    TEST_FIXTURE(DecryptFixture, LowCaseString) {
        CHECK_THROW(p->decrypt("зашифрованныйтекст"), cipher_error);
    }
    
    // Тест 3.5: Текст с недопустимыми символами - должен выбрасывать исключение
    TEST_FIXTURE(DecryptFixture, DigitsString) {
        CHECK_THROW(p->decrypt("ТЕКСТ123"), cipher_error);
    }
    
    // Тест 3.6: Текст с пробелами - должен выбрасывать исключение
    TEST_FIXTURE(DecryptFixture, WhitespaceString) {
        CHECK_THROW(p->decrypt("ЗАШИФР ТЕКСТ"), cipher_error);
    }
    
    // Тест 3.7: Текст со знаками препинания - должен выбрасывать исключение
    TEST_FIXTURE(DecryptFixture, PunctString) {
        CHECK_THROW(p->decrypt("ЗАШИФРОВАННЫЙ!"), cipher_error);
    }
    
    // Тест 3.8: Полный цикл шифрование-дешифрование
    TEST_FIXTURE(DecryptFixture, FullCycle) {
        std::string original = "ПРИВЕТМИР";
        std::string encrypted = p->encrypt(original);
        std::string decrypted = p->decrypt(encrypted);
        CHECK_EQUAL(original, decrypted);
    }
    
    // Тест 3.9: Текст с буквой Ё
    TEST_FIXTURE(DecryptFixture, LetterYo) {
        std::string original = "СЪЁМКА";
        std::string encrypted = p->encrypt(original);
        std::string decrypted = p->decrypt(encrypted);
        CHECK(!decrypted.empty());
    }
}

// Главная функция программы
int main() {
    return UnitTest::RunAllTests();
}
