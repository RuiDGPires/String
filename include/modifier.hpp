#pragma once
#include <string>
#include <cache.hpp>
#include <memory>

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
        std::shared_ptr<Cache<std::string>> cache = nullptr; // Ugh
        void set_cache(std::shared_ptr<Cache<std::string>> &cache);
        virtual std::wstring apply(const std::wstring &) const = 0;
    };

    struct WordColorer : public Modifier {
        private:
        size_t index;
        bool mine;
        Color color;

        public:

        /* Indexes are 1 - based*/
        WordColorer(size_t, Color);
        ~WordColorer() = default;

        void set_index(size_t);
        size_t get_index() const;

        virtual std::wstring apply(const std::wstring&) const override;
    };
}
