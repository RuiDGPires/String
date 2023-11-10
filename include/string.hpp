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
            /* Private member variables */
            std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
            std::wstring string;
            std::vector<std::shared_ptr<Modifier>> modifiers;
            std::shared_ptr<Cache<std::string>> cache;

            /* Private methods */
            std::string render();

        public:
            /* Constructors */
            String();
            String(const String &s);
            String(const std::string &s);
            String(const std::wstring &s);
            String(const char *s);

            /* Destructor */
            ~String() = default;

            /* Get std::string representation 
             * ---
             * Internally, gets the string from cache. If cache is invalid, it is updated with a new render beforehand.
             * */
            const std::string &str();

            /* item accessing */
            wchar_t at(size_t i) const;
            wchar_t operator[](size_t i) const;
 
            /* Get string length */
            size_t size() const;

            /* Clears internal string and modifiers */
            void clear();

            /* Add modifier */
            String &mod(const std::shared_ptr<Modifier> &modifier);

            /* Operators */
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
