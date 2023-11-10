#include <string.hpp>
#include <cache.hpp>

using namespace rui;

String::String() {
    string = L"";
    this->cache = std::make_shared<Cache<std::string>>(render());
}

String::String(const String &s) {
    string = s.string;
    this->cache = s.cache;
    this->modifiers = s.modifiers;
}

String::String(const std::string &s) {
    string = converter.from_bytes(s);
    this->cache = std::make_shared<Cache<std::string>>(render());
}

String::String(const std::wstring &s) {
    string = s;
    this->cache = std::make_shared<Cache<std::string>>(render());
}

String::String(const char *s) {
    string = converter.from_bytes(s);
    this->cache = std::make_shared<Cache<std::string>>(render());
}

std::string String::render() {
    // Apply modifiers
    std::wstring new_string = string;

    for (const auto &modifier : modifiers)
        new_string = modifier->apply(new_string);

    return std::string(converter.to_bytes(new_string));
}

const std::string &String::str() {
    if (!cache->is_valid())
        cache->update(this->render());
    return cache->value;
}

wchar_t String::at(size_t i) {
    return string[i];
}

wchar_t String::operator[](size_t i) {
    return this->at(i);
}

size_t String::size() const {
    return string.size();
}

String &String::mod(const std::shared_ptr<Modifier> &modifier) {
    modifier->cache = this->cache;
    this->modifiers.push_back(std::move(modifier));
    this->cache->invalidate();
    return (*this);
}

String& String::operator=(const String &other) {
    this->string = other.string;
    this->modifiers = other.modifiers;
    this->cache = other.cache;
    return *this;
}
String& String::operator=(const char *other) {
    string = converter.from_bytes(other);
    modifiers.clear();
    this->cache->invalidate();
    return *this;
}
String& String::operator=(const std::wstring &other) {
    string = other;
    modifiers.clear();
    this->cache->invalidate();
    return *this;
}

String& String::operator=(const std::string & other) {
    string = converter.from_bytes(other);
    modifiers.clear();
    this->cache->invalidate();
    return *this;
}

String &String::append(std::wstring::iterator _first, std::wstring::iterator _last) {
    this->string.append(_first, _last);
    this->cache->invalidate();
    return (*this);
}

String &String::append(const String &other) {
    this->string += other.string;
    this->modifiers.insert(this->modifiers.end(), other.modifiers.begin(), other.modifiers.end());
    this->cache->invalidate();
    return (*this);
}

String &String::append(const char *other) {
    this->string += converter.from_bytes(other);
    this->cache->invalidate();
    return (*this);
}
String &String::append(const std::wstring &other) {
    this->string += other;
    this->cache->invalidate();
    return (*this);
}
String &String::append(const std::string & other) {
    this->string += converter.from_bytes(other);
    this->cache->invalidate();
    return (*this);
}

String &String::operator+=(const String &other) {
    return this->append(other);
}

String &String::operator+=(const char *other) {
    return this->append(other);
}

String &String::operator+=(const std::wstring &other) {
    return this->append(other);
}

String &String::operator+=(const std::string & other) {
    return this->append(other);
}

String String::operator+(const String &other) {
    String new_string;

    new_string.string = this->string + other.string;
    new_string.modifiers = this->modifiers;
    new_string.modifiers.insert(new_string.modifiers.end(), other.modifiers.begin(), other.modifiers.end());
    new_string.cache->invalidate();

    return new_string;
}

String String::operator+(const char *other) {
    String new_string;

    new_string.string = this->string + new_string.converter.from_bytes(other);
    new_string.modifiers = this->modifiers;
    new_string.cache->invalidate();

    return new_string;
}

String String::operator+(const std::wstring &other) {
    String new_string;

    new_string.string = this->string + other;
    new_string.modifiers = this->modifiers;
    new_string.cache->invalidate();

    return new_string;
}

String String::operator+(const std::string & other) {
    String new_string;

    new_string.string = this->string + new_string.converter.from_bytes(other);
    new_string.modifiers = this->modifiers;
    new_string.cache->invalidate();

    return new_string;
}

std::ostream &operator<<(std::ostream &out, String s) {
    return out << s.str();
}
