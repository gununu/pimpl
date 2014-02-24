pimpl
=====

"pimpl" is C++11 simple pimpl idiom library using std::unique_ptr.  
This library has value semantics.

Pimpl idiom can reduce dependency among source files and make compiling faster.

###Usage
See test.cpp test.hpp

###Interface
```c++
namespace gununu {

struct pimpl_noinit_t{};

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
