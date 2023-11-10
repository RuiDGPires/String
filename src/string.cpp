#include <string.hpp>

using namespace rui;

template<typename T>
Cache<T>::Cache() {
    this->updated = false;
}

template<typename T>
Cache<T>::Cache(T v) {
    this->value = v;
    this->updated = true;
}

template<typename T>
void Cache<T>::invalidate() {
    this->updated = false;
}

template<typename T>
void Cache<T>::update(T v) {
    this->updated = true;
    this->value = v;
}

template<typename T>
bool Cache<T>::is_valid() const {
    return this->updated;
}

template<typename T>
T Cache<T>::get() const {
    return this->value;
}

String::String() {
    string = L"";
}

String::String(const std::string &s) {
    string = converter.from_bytes(s);
}

String::String(const std::wstring &s) {
    string = s;
}

String::String(const char *s) {
    string = converter.from_bytes(s);
}

const std::string &String::render() {
    if (!cache.is_valid()) {
        // Apply modifiers
        std::wstring new_string = string;
        for (const auto &modifier : modifiers) {
            new_string = modifier->apply(string);
        }

        cache.update(std::string(converter.to_bytes(new_string)));
    }

    return cache.value;
}

const std::string &String::str() {
    return this->render();
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
    this->modifiers.push_back(modifier);
    this->cache.invalidate();
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
    this->cache.invalidate();
    return *this;
}
String& String::operator=(const std::wstring &other) {
    string = other;
    modifiers.clear();
    this->cache.invalidate();
    return *this;
}

String& String::operator=(const std::string & other) {
    string = converter.from_bytes(other);
    modifiers.clear();
    this->cache.invalidate();
    return *this;
}

String &String::operator+=(const String &other) {
    this->string += other.string;
    this->modifiers.insert(this->modifiers.end(), other.modifiers.begin(), other.modifiers.end());
    this->cache.invalidate();
    return (*this);
}

String &String::operator+=(const char *other) {
    this->string += converter.from_bytes(other);
    this->cache.invalidate();
    return (*this);
}

String &String::operator+=(const std::wstring &other) {
    this->string += other;
    this->cache.invalidate();
    return (*this);
}

String &String::operator+=(const std::string & other) {
    this->string += converter.from_bytes(other);
    this->cache.invalidate();
    return (*this);
}

std::ostream &operator<<(std::ostream &out, String &s) {
    return out << s.str();
}

