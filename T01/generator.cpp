#include <stdlib.h>
#include <iostream>
#include "generator.h"

Generator::Generator(void) {
    FILE *fNames = fopen("MOCK_names.txt", "r");

    char[1024] stream
    fread(fNames, 64, <#(size_t)__n#>, <#(FILE *)__stream#>)

    FILE *fSurnames = fopen("MOCK_surnames.txt", "r");

}

string Generator::getName() {
    return std::basic_string<char, char_traits<_CharT>, allocator<_CharT>>();
}

string Generator::getSurname() {
    return std::basic_string<char, char_traits<_CharT>, allocator<_CharT>>();
}

string Generator::getFullName() {
    return std::basic_string<char, char_traits<_CharT>, allocator<_CharT>>();
}

string Generator::getDate() {
    return std::basic_string<char, char_traits<_CharT>, allocator<_CharT>>();
}
