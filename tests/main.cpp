#include "test.hpp"

int main() {
    // can construct, use, copy, destruct without including the implimentation on this translation unit
    sample s;
    s.func();

    sample t;
    t = s;
    std::swap(s, t);

    return 0;
}
