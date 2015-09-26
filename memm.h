#ifndef MEMM_H
#define MEMM_H

#include <memory>

template <typename T> using ptr = std::shared_ptr<T>;
template <typename T> using raw_ptr = std::unique_ptr<T>;

template <typename T>
inline ptr<T> createptr() noexcept
{
    return std::make_shared<T>();
}

template <typename T, typename... Args>
inline ptr<T> createptr(Args&&... args) noexcept
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

#endif // MEMM_H

