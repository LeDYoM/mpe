#ifndef MEMM_H
#define MEMM_H

#include <memory>

template <typename T> using sptr = std::shared_ptr<T>;
template <typename T> using uptr = std::unique_ptr<T>;

template <typename T>
inline sptr<T> createptr()
{
    return sptr<T>(new T());
}

template <typename T, typename... Args>
inline sptr<T> createptr(Args&&... args) noexcept
{
    return sptr<T>(new T(std::forward<Args>(args)...));
}

#endif // MEMM_H

