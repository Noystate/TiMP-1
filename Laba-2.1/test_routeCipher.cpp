#include <UnitTest++/UnitTest++.h>
#include "routeCipher.h"
#include <string>
#include <iostream>

using namespace std;

// ============================================================================
// ПРОСТЫЕ ТЕСТЫ КОНСТРУКТОРА
// ============================================================================

SUITE(ConstructorTests)
{
    TEST(ValidKey) {
        TableRouteCipher cipher(3);
        string text = "HELLO";
        string encrypted = cipher.encrypt(text);
        string decrypted = cipher.decrypt(encrypted);
        CHECK_EQUAL("HELLO", decrypted);
    }
    
    TEST(KeyLongerThanText) {
        TableRouteCipher cipher(10);
        string text = "SHORT";
        string encrypted = cipher.encrypt(text);
        string decrypted = cipher.decrypt(encrypted);
        CHECK_EQUAL("SHORT", decrypted);
    }
    
    TEST(SingleColumnKey) {
        TableRouteCipher cipher(1);
        string text = "HELLO";
        string encrypted = cipher.encrypt(text);
        string decrypted = cipher.decrypt(encrypted);
        CHECK_EQUAL("HELLO", decrypted);
    }
    
    TEST(NegativeKey) {
        CHECK_THROW(TableRouteCipher cipher(-5), invalid_argument);
    }
    
    TEST(ZeroKey) {
        CHECK_THROW(TableRouteCipher cipher(0), invalid_argument);
    }
}

// ============================================================================
// ТЕСТЫ ШИФРОВАНИЯ
// ============================================================================

SUITE(EncryptTests)
{
    TEST(UpperCaseText) {
        TableRouteCipher cipher(3);
        string text = "HELLO";
        string result = cipher.encrypt(text);
        CHECK(!result.empty());
    }
    
    TEST(LowerCaseText) {
        TableRouteCipher cipher(3);
        string text = "hello";
        string result = cipher.encrypt(text);
        CHECK(!result.empty());
    }
    
    TEST(TextWithSpaces) {
        TableRouteCipher cipher(3);
        string text = "HELLO WORLD";
        string result = cipher.encrypt(text);
        CHECK(!result.empty());
    }
    
    TEST(TextWithNumbers) {
        TableRouteCipher cipher(3);
        string text = "TEST123";
        string result = cipher.encrypt(text);
        CHECK(!result.empty());
    }
    
    TEST(EmptyText) {
        TableRouteCipher cipher(3);
        string text = "";
        CHECK_THROW(cipher.encrypt(text), invalid_argument);
    }
    
    TEST(ShortText) {
        TableRouteCipher cipher(5);
        string text = "HI";
        string result = cipher.encrypt(text);
        CHECK(!result.empty());
    }
}

// ============================================================================
// ТЕСТЫ ДЕШИФРОВАНИЯ
// ============================================================================

SUITE(DecryptTests)
{
    TEST(DecryptValidText) {
        TableRouteCipher cipher(3);
        string original = "TEST";
        string encrypted = cipher.encrypt(original);
        string decrypted = cipher.decrypt(encrypted);
        CHECK_EQUAL("TEST", decrypted);
    }
    
    TEST(DecryptWithSpaces) {
        TableRouteCipher cipher(3);
        string original = "HELLO WORLD";
        string encrypted = cipher.encrypt(original);
        string decrypted = cipher.decrypt(encrypted);
        CHECK_EQUAL("HELLO WORLD", decrypted);
    }
    
    TEST(DecryptEmpty) {
        TableRouteCipher cipher(3);
        string text = "";
        CHECK_THROW(cipher.decrypt(text), invalid_argument);
    }
}

// ============================================================================
// ИНТЕГРАЦИОННЫЕ ТЕСТЫ
// ============================================================================

SUITE(IntegrationTests)
{
    TEST(SimpleText) {
        TableRouteCipher cipher(3);
        string original = "PROGRAMMING";
        string encrypted = cipher.encrypt(original);
        string decrypted = cipher.decrypt(encrypted);
        CHECK_EQUAL("PROGRAMMING", decrypted);
    }
    
    TEST(TextWithSpaces) {
        TableRouteCipher cipher(4);
        string original = "HELLO WORLD";
        string encrypted = cipher.encrypt(original);
        string decrypted = cipher.decrypt(encrypted);
        CHECK_EQUAL("HELLO WORLD", decrypted);
    }
    
    TEST(LongText) {
        TableRouteCipher cipher(5);
        string original = "THE QUICK BROWN FOX";
        string encrypted = cipher.encrypt(original);
        string decrypted = cipher.decrypt(encrypted);
        CHECK_EQUAL("THE QUICK BROWN FOX", decrypted);
    }
    
    TEST(BoundaryCase) {
        TableRouteCipher cipher(2);
        string original = "TEST";
        string encrypted = cipher.encrypt(original);
        string decrypted = cipher.decrypt(encrypted);
        CHECK_EQUAL("TEST", decrypted);
    }
    
    TEST(MinimalKey) {
        TableRouteCipher cipher(1);
        string original = "SINGLE COLUMN";
        string encrypted = cipher.encrypt(original);
        string decrypted = cipher.decrypt(encrypted);
        CHECK_EQUAL("SINGLE COLUMN", decrypted);
    }
    
    TEST(LargeKey) {
        TableRouteCipher cipher(8);
        string original = "SHORT";
        string encrypted = cipher.encrypt(original);
        string decrypted = cipher.decrypt(encrypted);
        CHECK_EQUAL("SHORT", decrypted);
    }
}

// ============================================================================
// ТЕСТЫ ОСОБЫХ СЛУЧАЕВ
// ============================================================================

SUITE(SpecialCasesTests)
{
    TEST(RepeatingCharacters) {
        TableRouteCipher cipher(3);
        string text = "AAAAA";
        string encrypted = cipher.encrypt(text);
        string decrypted = cipher.decrypt(encrypted);
        CHECK_EQUAL("AAAAA", decrypted);
    }
    
    TEST(SingleCharacter) {
        TableRouteCipher cipher(3);
        string text = "A";
        string encrypted = cipher.encrypt(text);
        string decrypted = cipher.decrypt(encrypted);
        CHECK_EQUAL("A", decrypted);
    }
    
    TEST(Symmetry) {
        TableRouteCipher cipher(3);
        string text = "SYMMETRY TEST";
        string encrypted = cipher.encrypt(text);
        string decrypted = cipher.decrypt(encrypted);
        CHECK_EQUAL("SYMMETRY TEST", decrypted);
    }
    
    TEST(ExactTableSize) {
        TableRouteCipher cipher(4);
        string text = "ABCDEFGH"; // 8 символов = 2 строки × 4 колонки
        string encrypted = cipher.encrypt(text);
        string decrypted = cipher.decrypt(encrypted);
        CHECK_EQUAL("ABCDEFGH", decrypted);
    }
}

// ============================================================================
// ГЛАВНАЯ ФУНКЦИЯ
// ============================================================================

int main() {
    cout << "=============================================" << endl;
    cout << "   ТЕСТИРОВАНИЕ МАРШРУТНОЙ ПЕРЕСТАНОВКИ" << endl;
    cout << "=============================================" << endl;
    
    int result = UnitTest::RunAllTests();
    
    cout << "=============================================" << endl;
    if (result == 0) {
        cout << "✅ ВСЕ ТЕСТЫ ПРОЙДЕНЫ!" << endl;
    } else {
        cout << "❌ ЕСТЬ ОШИБКИ!" << endl;
    }
    cout << "=============================================" << endl;
    
    return result;
}
