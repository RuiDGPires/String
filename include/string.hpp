#pragma once
#include <string>
#include <iostream>
#include <codecvt>
#include <locale>
#include <vector>
#include <memory>

#include "cache.hpp"
#include "modifier.hpp"

namespace rui {
    class String {
        private:
            std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
            std::wstring string;
            std::vector<std::shared_ptr<Modifier>> modifiers;
            std::shared_ptr<Cache<std::string>> cache;

            std::string render();

        public:
            String();
            String(const String &s);
            String(const std::string &s);
            String(const std::wstring &s);
            String(const char *s);

            ~String() = default;

            const std::string &str();

            wchar_t at(size_t i) const;
            wchar_t operator[](size_t i) const;

            size_t size() const;

            String &mod(const std::shared_ptr<Modifier> &modifier);

            String &operator=(const String &other);
            String &operator=(const char *other);
            String &operator=(const std::wstring &other);
            String &operator=(const std::string & other);

            
            String &append(std::wstring::iterator _first, std::wstring::iterator _last);
            String &append(const String &other);
            String &append(const char *other);
            String &append(const std::wstring &other);
            String &append(const std::string & other);

            String &operator+=(const String &other);
            String &operator+=(const char *other);
            String &operator+=(const std::wstring &other);
            String &operator+=(const std::string & other);

            String operator+(const String &other);
            String operator+(const char *other);
            String operator+(const std::wstring &other);
            String operator+(const std::string & other);
    };
}

std::ostream &operator<<(std::ostream &out, rui::String s);
