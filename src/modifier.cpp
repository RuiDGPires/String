#include <modifier.hpp>
#include <memory>
#include <locale>

using namespace rui;

WordColorer::WordColorer(size_t i, Color c) {
    this->index = i;
    this->color = c;
}

#define BLUE_STR    "\e[1;36m"
#define YELLOW_STR  "\e[1;33m"
#define BOLD_STR    "\e[1;37m"
#define GREEN_STR   "\e[1;32m"
#define RESET_STR   "\e[0m"
#define GRAY_STR    "\e[1;90m"

static std::wstring get_wcolor(const Color &c) {
    switch (c) {
        case Color::BLUE:
            return L"" BLUE_STR;
            break;
        case Color::YELLOW:
            return L"" YELLOW_STR;
            break;
        case Color::GREEN:
            return L"" GREEN_STR;
            break;
        case Color::GRAY:
            return L"" GRAY_STR;
            break;
        case Color::RESET:
            return L"" RESET_STR;
            break;
        default:
            return L"";
    }
}

void WordColorer::set_index(size_t i) {
    if (cache)
        cache->invalidate();

    index = i;
}

size_t WordColorer::get_index() const {
    return index;
}

std::wstring WordColorer::apply(const std::wstring &str) const {
    size_t current_word = 0;
    bool within_word = false;

    std::wstring new_str= L"";

    for (size_t i = 0; i < str.size(); i++) {
        if (std::iswspace(str[i])) {
            if (within_word && current_word == index)
                new_str += L"" RESET_STR;

            within_word = false;
        } else {
            if (!within_word) {
                within_word = true;
                current_word++;
                if (current_word == index)
                    new_str += get_wcolor(this->color);
            }
        }
        new_str += str[i];
    }

    if (within_word && current_word == index)
        new_str += L"" RESET_STR;

    return new_str;
}
