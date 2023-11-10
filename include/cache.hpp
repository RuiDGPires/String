#pragma once

namespace rui {
    template<typename T>
    struct Cache {
        bool updated;
        T value;
        
        Cache();
        Cache(T v);

        void invalidate();
        void update(T v);
        bool is_valid() const;
        T get() const;
    };

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
}
