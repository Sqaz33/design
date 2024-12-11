#ifndef PRINT
#define PRINT

#include <iostream>
#include <vector>

namespace print_utils {

template <class T>
inline void print(std::vector<T>&& vec) {
    for (const auto& el : vec) { std::cout << el << ' '; }
    std::cout << '\n';
}

template <class... Args>
inline void print(Args&&... args) {
    ((std::cout << args << ' '), ...);
    std::cout << '\n';
}

} // namespace print


#endif // PRINT