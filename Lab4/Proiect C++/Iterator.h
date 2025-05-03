#pragma once
#include <stdexcept>

#include "DO.h"
class IteratorDO {
    friend class DO;
private:
    const DO& dict;
    int current;

    explicit IteratorDO(const DO& d) : dict(d), current(d.head) {}

public:

    // Pointer-like behavior
    TElem operator*() const {
        return element();
    }

    const TElem* operator->() const {
        static TElem temp = element();
        return &temp;
    }

    IteratorDO& operator++() {
        next();
        return *this;
    }

    IteratorDO operator++(int) {
        IteratorDO temp = *this;
        next();
        return temp;
    }

    IteratorDO& operator=(const IteratorDO& rhs) {
        if (this != &rhs) { // Avoid self-assignment
            this->current = rhs.current;
        }
        return *this;
    }

    void first() {
        current = dict.head;
    }

    void next() {
        if (!valid()) {
            throw std::out_of_range("Iterator out of range");
        }
        current = dict.next[current];
    }

    void prev() {
        if (!valid()) {
            throw std::out_of_range("Iterator out of range");
        }
        current = dict.prev[current];
    }

    bool valid() const {
        return current != -1;
    }

    TElem element() const {
        if (!valid()) {
            throw std::out_of_range("Iterator out of range");
        }
        return dict.elems[current];
    }
};
