#include <string.hpp>

using namespace rui;

String::String() {
    _wstring = L"";
}

String::String(const std::string &s) {
    _wstring = converter.from_bytes(s);
}

String::String(const std::wstring &s) {
    _wstring = s;
}

String::String(const char *s) {
    _wstring = converter.from_bytes(s);
}

std::string String::str() {
    // Apply modifiers
    std::wstring new_str = _wstring;
    for (const auto &modifier : modifiers) {
        new_str = modifier->apply(_wstring);
    }

    return std::string(converter.to_bytes(new_str));
}

wchar_t String::at(size_t i) {
    return _wstring[i];
}

wchar_t String::operator[](size_t i) {
    return this->at(i);
}

size_t String::size() const {
    return _wstring.size();
}

String &String::mod(const std::shared_ptr<Modifier> &modifier) {
    this->modifiers.push_back(modifier);
    return (*this);
}

String& String::operator=(const String &other) {
    _wstring = other._wstring;
    modifiers = other.modifiers;
    return *this;
}
String& String::operator=(const char *other) {
    _wstring = converter.from_bytes(other);
    modifiers.clear();
    return *this;
}
String& String::operator=(const std::wstring &other) {
    _wstring = other;
    modifiers.clear();
    return *this;
}

String& String::operator=(const std::string & other) {
    _wstring = converter.from_bytes(other);
    modifiers.clear();
    return *this;
}

std::ostream &operator<<(std::ostream &out, String &s) {
    return out << s.str();
}
