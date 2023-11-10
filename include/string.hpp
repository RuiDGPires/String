#pragma once
#include <string>
#include <iostream>
#include <codecvt>
#include <locale>
#include <vector>
#include <memory>
#include "modifier.hpp"

namespace rui {
    class String {
        private:
            std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

        public:
            std::wstring _wstring;
            std::vector<std::shared_ptr<Modifier>> modifiers;

            ~String() = default;

            String();

            String(const std::string &s);

            String(const std::wstring &s);

            String(const char *s);

            std::string str();

            wchar_t at(size_t i);

            wchar_t operator[](size_t i);

            size_t size() const;

            String &mod(const std::shared_ptr<Modifier> &modifier);

            String& operator=(const String &other);

            String& operator=(const char *other);
            String& operator=(const std::wstring &other);
            String& operator=(const std::string & other);
    };
}

std::ostream &operator<<(std::ostream &out, rui::String &s);
