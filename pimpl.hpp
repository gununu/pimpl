#ifndef GUNUNU_PIMPL_HPP
#define GUNUNU_PIMPL_HPP

#include <memory>
#include <utility>

namespace gununu {

struct pimpl_noinit_t{};

constexpr pimpl_noinit_t pimpl_noinit;

namespace detail {
struct holder {
    holder(){};
    virtual ~holder(){};
    virtual holder* clone() = 0;
    virtual void destroy() = 0;
    virtual void* get() = 0;
};

template <class T>
struct holder_t : public holder {
    template <class... Args>
    holder_t(Args&&... args) : obj(std::forward<Args>(args)...) {}
    holder* clone() override {
        return new holder_t<T>(obj);
    }

    void destroy() override {
        (void)sizeof(T);
        std::default_delete<holder_t<T>>()(this);
    }

    void* get() override {
        return static_cast<void*>(&obj);
    }
private:
    T obj;
};
} //namespace detail

template <class T>
class pimpl {
public:
    pimpl(): ptr_(new detail::holder_t<T>()) {}
    ~pimpl() { if (ptr_) ptr_->destroy(); }
    constexpr pimpl(pimpl_noinit_t) noexcept {}

    pimpl(pimpl&& rhs) noexcept {
        *this = std::move(rhs);
    }
    pimpl(pimpl const& rhs) {
        *this = rhs;
    }

    explicit pimpl(T const& v) {
        ptr_ = new detail::holder_t<T>(v);
    }
    explicit pimpl(T&& v) {
        ptr_ = new detail::holder_t<T>(std::move(v));
    }

    T* get() const noexcept {
        return static_cast<T*>(ptr_->get());
    }

    T& operator *() const {
        return *get();
    }
    T* operator ->() const noexcept {
        return get();
    }
    
    explicit operator bool() const noexcept {
        return !!ptr_;
    }

    void swap(pimpl& rhs) noexcept {
        std::swap(ptr_, rhs.ptr_);
    }

    pimpl& operator = (pimpl&& rhs) noexcept {
        swap(rhs);
        return *this;
    }
    pimpl& operator = (pimpl const& rhs) {
        auto* cloned = (rhs ? rhs.ptr_->clone() : nullptr);
        if (ptr_) ptr_->destroy();
        ptr_ = cloned;  
        return *this;
    }
private: 
    template <class T2, class... Args2>
    friend pimpl<T2> make_pimpl(Args2&&...);
private:
    detail::holder* ptr_ = nullptr;
};

template <class T, class... Args>
pimpl<T> make_pimpl(Args&&... args)
{
    pimpl<T> v(pimpl_noinit);
    v.ptr_ = new detail::holder_t<T>(std::forward<Args>(args)...);
    return v;
}

template <class T>
void swap(pimpl<T>& lhs, pimpl<T>& rhs) noexcept {
    lhs.swap(rhs);
}

} //namespace

#endif
