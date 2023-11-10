#pragma once
#include <string>

namespace rui {
    enum Color {
        BLUE,
        YELLOW,
        BOLD,
        GREEN,
        GRAY,

        RESET,
    };

    struct Modifier {
        virtual std::wstring apply(const std::wstring &) const = 0;
    };

    struct WordColorer : public Modifier {
        size_t *index;
        bool mine;
        Color color;

        /* Indexes are 1 - based*/
        WordColorer(size_t, Color);
        WordColorer(size_t*, Color);
        ~WordColorer();

        virtual std::wstring apply(const std::wstring&) const override;
    };
}
