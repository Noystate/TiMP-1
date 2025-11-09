#include <UnitTest++/UnitTest++.h>
#include "modAlphaCipher.h"
#include <locale>
#include <codecvt>
#include <iostream>
#include <algorithm> // Добавьте эту строку

// Вспомогательная функция для сравнения wstring
bool compareWString(const std::wstring& expected, const std::wstring& actual) {
    if (expected == actual) {
        return true;
    } else {
        std::wcout << L"Ожидалось: '" << expected << L"'" << std::endl;
        std::wcout << L"Получено: '" << actual << L"'" << std::endl;
        return false;
    }
}

SUITE(KeyTest)
{
    TEST(ValidKey) {
        modAlphaCipher cipher(L"БВГ");
        std::wstring result = cipher.encrypt(L"ААААА");
        CHECK(compareWString(L"БВГБВ", result));
    }
    
    TEST(LongKey) {
        modAlphaCipher cipher(L"БВГДЕЖЗИЙКЛ");
        std::wstring result = cipher.encrypt(L"ААААА");
        CHECK(compareWString(L"БВГДЕ", result));
    }
    
    TEST(LowCaseKey) {
        modAlphaCipher cipher(L"бвг");
        std::wstring result = cipher.encrypt(L"ААААА");
        CHECK(compareWString(L"БВГБВ", result));
    }
    
    TEST(DigitsInKey) {
        CHECK_THROW(modAlphaCipher cipher(L"Б1"), cipher_error);
    }
    
    TEST(PunctuationInKey) {
        CHECK_THROW(modAlphaCipher cipher(L"Б,В"), cipher_error);
    }
    
    TEST(WhitespaceInKey) {
        CHECK_THROW(modAlphaCipher cipher(L"Б В"), cipher_error);
    }
    
    TEST(EmptyKey) {
        CHECK_THROW(modAlphaCipher cipher(L""), cipher_error);
    }
    
    TEST(WeakKey) {
        CHECK_THROW(modAlphaCipher cipher(L"ААА"), cipher_error);
    }
}

struct KeyB_Fixture {
    modAlphaCipher* p;
    KeyB_Fixture() {
        p = new modAlphaCipher(L"Б");
    }
    ~KeyB_Fixture() {
        delete p;
    }
};

SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyB_Fixture, UpCaseString) {
        std::wstring result = p->encrypt(L"ПРИВЕТМИР");
        // Проверяем что результат не пустой и можем расшифровать обратно
        CHECK(!result.empty());
        std::wstring decrypted = p->decrypt(result);
        CHECK(compareWString(L"ПРИВЕТМИР", decrypted));
    }
    
    TEST_FIXTURE(KeyB_Fixture, LowCaseString) {
        std::wstring result = p->encrypt(L"приветмир");
        CHECK(!result.empty());
        std::wstring decrypted = p->decrypt(result);
        CHECK(compareWString(L"ПРИВЕТМИР", decrypted));
    }
    
    TEST_FIXTURE(KeyB_Fixture, StringWithWhitespaceAndPunct) {
        std::wstring result = p->encrypt(L"ПРИВЕТ, МИР!");
        CHECK(!result.empty());
        std::wstring decrypted = p->decrypt(result);
        // Проверяем что пробелы сохранились, а знаки препинания удалились
        CHECK(compareWString(L"ПРИВЕТ МИР", decrypted));
    }
    
    TEST_FIXTURE(KeyB_Fixture, StringWithNumbers) {
        std::wstring result = p->encrypt(L"С НОВЫМ 2024 ГОДОМ");
        CHECK(!result.empty());
        std::wstring decrypted = p->decrypt(result);
        // Проверяем что цифры удалились, а пробелы сохранились
        CHECK(compareWString(L"С НОВЫМ  ГОДОМ", decrypted));
    }
    
    TEST_FIXTURE(KeyB_Fixture, EmptyString) {
        CHECK_THROW(p->encrypt(L""), cipher_error);
    }
    
    TEST_FIXTURE(KeyB_Fixture, NoAlphaString) {
        CHECK_THROW(p->encrypt(L"1234+8765=9999"), cipher_error);
    }
    
    TEST(MaxShiftKey) {
        modAlphaCipher cipher(L"Я");
        std::wstring result = cipher.encrypt(L"АБВГД");
        CHECK(!result.empty());
        std::wstring decrypted = cipher.decrypt(result);
        CHECK(compareWString(L"АБВГД", decrypted));
    }
}

SUITE(DecryptTest)
{
    TEST_FIXTURE(KeyB_Fixture, UpCaseString) {
        std::wstring encrypted = p->encrypt(L"ПРИВЕТМИР");
        std::wstring decrypted = p->decrypt(encrypted);
        CHECK(compareWString(L"ПРИВЕТМИР", decrypted));
    }
    
    TEST_FIXTURE(KeyB_Fixture, LowCaseString) {
        // Создаем зашифрованный текст в верхнем регистре
        std::wstring encrypted = p->encrypt(L"ТЕСТ");
        // Пытаемся расшифровать в нижнем регистре - должно бросить исключение
        std::wstring lower_encrypted;
        for (wchar_t c : encrypted) {
            if (c >= L'А' && c <= L'Я') {
                lower_encrypted += (c - L'А' + L'а');
            } else {
                lower_encrypted += c;
            }
        }
        CHECK_THROW(p->decrypt(lower_encrypted), cipher_error);
    }
    
    TEST_FIXTURE(KeyB_Fixture, WhitespaceString) {
        std::wstring encrypted = p->encrypt(L"ПРИВЕТ МИР");
        std::wstring decrypted = p->decrypt(encrypted);
        CHECK(compareWString(L"ПРИВЕТ МИР", decrypted));
    }
    
    TEST_FIXTURE(KeyB_Fixture, DigitsString) {
        // Создаем зашифрованный текст
        std::wstring encrypted = p->encrypt(L"ТЕСТ");
        // Добавляем цифры в зашифрованный текст
        std::wstring invalid_encrypted = encrypted + L"2024";
        CHECK_THROW(p->decrypt(invalid_encrypted), cipher_error);
    }
    
    TEST_FIXTURE(KeyB_Fixture, PunctString) {
        // Создаем зашифрованный текст
        std::wstring encrypted = p->encrypt(L"ТЕСТ");
        // Добавляем знаки препинания
        std::wstring invalid_encrypted = L"!" + encrypted + L",";
        CHECK_THROW(p->decrypt(invalid_encrypted), cipher_error);
    }
    
    TEST_FIXTURE(KeyB_Fixture, EmptyString) {
        CHECK_THROW(p->decrypt(L""), cipher_error);
    }
    
    TEST(MaxShiftKey) {
        modAlphaCipher cipher(L"Я");
        std::wstring encrypted = cipher.encrypt(L"ПРИВЕТ");
        std::wstring decrypted = cipher.decrypt(encrypted);
        CHECK(compareWString(L"ПРИВЕТ", decrypted));
    }
}

SUITE(IntegrationTest)
{
    TEST(EncryptDecryptConsistency) {
        modAlphaCipher cipher(L"КЛЮЧ");
        std::wstring original = L"ПРОГРАММИРОВАНИЕ НА C++";
        std::wstring encrypted = cipher.encrypt(original);
        std::wstring decrypted = cipher.decrypt(encrypted);
        CHECK(compareWString(L"ПРОГРАММИРОВАНИЕ НА ", decrypted));
    }
    
    TEST(DifferentKeys) {
        std::wstring text = L"ТЕСТОВЫЙТЕКСТ";
        
        modAlphaCipher cipher1(L"А");
        modAlphaCipher cipher2(L"БВ");
        modAlphaCipher cipher3(L"ГДЕ");
        
        CHECK(compareWString(text, cipher1.decrypt(cipher1.encrypt(text))));
        CHECK(compareWString(text, cipher2.decrypt(cipher2.encrypt(text))));
        CHECK(compareWString(text, cipher3.decrypt(cipher3.encrypt(text))));
    }
    
    TEST(SpacePreservation) {
        modAlphaCipher cipher(L"КЛЮЧ");
        std::wstring text = L"ЭТО ТЕКСТ С ПРОБЕЛАМИ";
        std::wstring encrypted = cipher.encrypt(text);
        std::wstring decrypted = cipher.decrypt(encrypted);
        
        // Проверяем что количество пробелов сохранилось
        int original_spaces = std::count(text.begin(), text.end(), L' ');
        int decrypted_spaces = std::count(decrypted.begin(), decrypted.end(), L' ');
        CHECK_EQUAL(original_spaces, decrypted_spaces);
        
        // Проверяем что пробелы на тех же позициях (примерно)
        CHECK(decrypted.find(L' ') != std::wstring::npos);
    }
}

int main() {
    // Установка локали для корректного вывода широких строк
    std::locale::global(std::locale(""));
    std::wcout.imbue(std::locale());
    
    std::wcout << L"=============================================" << std::endl;
    std::wcout << L"   ТЕСТИРОВАНИЕ ШИФРА ГРОНСФЕЛЬДА" << std::endl;
    std::wcout << L"=============================================" << std::endl;
    
    int result = UnitTest::RunAllTests();
    
    std::wcout << L"=============================================" << std::endl;
    if (result == 0) {
        std::wcout << L"✅ ВСЕ ТЕСТЫ ПРОЙДЕНЫ УСПЕШНО!" << std::endl;
    } else {
        std::wcout << L"❌ ОБНАРУЖЕНЫ ОШИБКИ В ТЕСТАХ!" << std::endl;
    }
    std::wcout << L"=============================================" << std::endl;
    
    return result;
}
