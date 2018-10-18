pimpl
=====
[![Build Status](https://travis-ci.org/gununu/pimpl.svg)](https://travis-ci.org/gununu/pimpl)

"pimpl" is C++11 simple pimpl idiom library.  
This library has value semantics.

Pimpl idiom can reduce dependency among source files and make compilation faster.

### Usage
1. Declare a prototype of a heavy class in a header file that would be included in many places.
```
// lightweight.hpp
class heavy;
```

2. Define a gununu::pimpl<heavy> object in the header file.
```
// lightweight.hpp
#include <gununu/pimpl.hpp>
class heavy;

class lightweight {
public:
lightweight();

gununu::pimpl<heavy> object;
void method();
};
```

3. Define or include the implementation of the heavy in a source file.
```
// lightweight.cpp
#include "lightweight.hpp"
#include "heavy.hpp"
```

4. Construct the object in the source file.
```
// lightweight.cpp
#include "lightweight.hpp"
#include "heavy.hpp"
lightweight::lightweight() : object() {}
```

5. Use the object in the source file.
```
// lightweight.cpp
#include "lightweight.hpp"
#include "heavy.hpp"
lightweight::lightweight() : object() {}

void lightweight::method() {
    object->XXXXXX();
    // etc..
}

```

6. Now, you can use the lightweight class without including the heavy class. Congrats!
```
// main.cpp
#include "lightweight.hpp"
int main() {
    lightweight lw;
    lw.method();
}
```

See test.cpp test.hpp

### License
Public Domain

### Interface
```c++
namespace gununu {

struct pimpl_noinit_t{};

constexpr pimpl_noinit_t pimpl_noinit;

template <class T>
class pimpl {
public:
    pimpl()
    ~pimpl()
    constexpr pimpl(pimpl_noinit_t) noexcept

    pimpl(pimpl&&) noexcept
    pimpl(pimpl const& rhs)

    explicit pimpl(T const& v)
    explicit pimpl(T&& v)

    T* get() const noexcept
    T& operator *() const
    T* operator ->() const noexcept
    explicit operator bool() const noexcept

    void swap(pimpl& rhs) noexcept

    pimpl& operator = (pimpl&&) noexcept
    pimpl& operator = (pimpl const& rhs)
};

template <class T, class... Args>
pimpl<T> make_pimpl(Args&&... args)

template <class T>
void swap(pimpl<T>& lhs, pimpl<T>& rhs) noexcept
}
```
