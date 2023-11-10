#include <string.hpp>
#include <cache.hpp>

using namespace rui;

String::String() {
    string = L"";
    this->cache = std::make_shared<Cache<std::string>>(render());
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
        new_string = modifier->apply(string);

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

String &String::operator+=(const String &other) {
    this->string += other.string;
    this->modifiers.insert(this->modifiers.end(), other.modifiers.begin(), other.modifiers.end());
    this->cache->invalidate();
    return (*this);
}

String &String::operator+=(const char *other) {
    this->string += converter.from_bytes(other);
    this->cache->invalidate();
    return (*this);
}

String &String::operator+=(const std::wstring &other) {
    this->string += other;
    this->cache->invalidate();
    return (*this);
}

String &String::operator+=(const std::string & other) {
    this->string += converter.from_bytes(other);
    this->cache->invalidate();
    return (*this);
}

std::ostream &operator<<(std::ostream &out, String &s) {
    return out << s.str();
}

