#ifndef GUNUNU_PIMPL_HPP
#define GUNUNU_PIMPL_HPP

#include <memory>
#include <utility>

namespace gununu {

struct pimpl_noinit_t{};

template <class T>
class pimpl {
public:
    pimpl(): ptr_(new T()) {}
    ~pimpl() { incomplete_check(); }
    constexpr pimpl(pimpl_noinit_t) noexcept {}

    pimpl(pimpl&&) noexcept = default;
    pimpl(pimpl const& rhs) {
        *this = rhs;
    }

    explicit pimpl(T const& v) {
        ptr_.reset(new T(v));
    }
    explicit pimpl(T&& v) {
        ptr_.reset(new T(std::move(v)));
    }

    T* get() const noexcept {
        return ptr_.get();
    }

    T& operator *() const {
        return *ptr_.get();
    }
    T* operator ->() const noexcept {
        return ptr_.get();
    }
    
    explicit operator bool() const noexcept {
        return ptr_.operator bool();
    }

    void swap(pimpl& rhs) noexcept {
        ptr_.swap(rhs.ptr_);
    }

    pimpl& operator = (pimpl&&) noexcept = default;
    pimpl& operator = (pimpl const& rhs) {
        ptr_.reset(rhs ? new T(*rhs.get()) : nullptr);
        return *this;
    }
private: 
    template <class T2, class... Args2>
    friend pimpl<T2> make_pimpl(Args2&&...);
    void incomplete_check() { (void)sizeof(T); }
private:
    std::unique_ptr<T> ptr_;
};

template <class T, class... Args>
pimpl<T> make_pimpl(Args&&... args)
{
    pimpl<T> v(pimpl_noinit_t{});
    v.ptr_.reset(new T(std::forward<Args>(args)...));
    return v;
}

template <class T>
void swap(pimpl<T>& lhs, pimpl<T>& rhs) noexcept {
    lhs.swap(rhs);
}

} //namespace

#endif
