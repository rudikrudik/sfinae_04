#pragma once
#include <type_traits>

// Вызываем если параметр от short до long long
template <typename T>
static std::enable_if_t<std::is_integral_v<T>>
print_ip(T value)
{
    static const size_t constexpr size = sizeof(T);
    for (size_t i = size; i--;)
    {
        std::cout << (value >> (i << 3) & 0xFF);
        if (i > 0)
            std::cout << '.';
    }
    std::cout << std::endl;
}

// Вызываем если std::string
template<typename T>
static std::enable_if_t<std::is_same_v<T, std::string>>
print_ip(T value){
    std::cout << value << std::endl;
}

// Вызываем если параметр std::vector или std::list
template <typename>
struct is_std_vector_or_list : std::false_type {};

template <typename T, typename... Args>
struct is_std_vector_or_list<std::vector<T, Args...>> : std::true_type {};

template <typename T, typename... Args>
struct is_std_vector_or_list<std::list<T, Args...>> : std::true_type {};

template <typename T>
static void print_ip(std::enable_if_t<is_std_vector_or_list<T>::value, const T&> container)
{
    for (auto it = container.begin(); it != container.end(); ++it)
    {
        std::cout << *it;
        if (it != std::prev(container.end()))
            std::cout << '.';
    }
    std::cout << std::endl;
}

// Вызываем если std::tuple
template <size_t I>
struct PrintTuple
{
    template <typename Type0, typename... Types>
    static constexpr void Print(const std::tuple<Type0, Types...>& tuple)
    {
        auto number = std::get<sizeof...(Types) + 1 - I>(tuple);
        std::cout << number;
        if constexpr (I > 1)
            std::cout << '.';

        PrintTuple<I - 1>::Print(tuple);
    }
};

template <>
struct PrintTuple<0>
{
    template <typename... Types>
    static constexpr void Print(const std::tuple<Types...>&) {}
};

template <typename... Types>
static void print_ip(const std::tuple<Types...>& tuple)
{
    PrintTuple<sizeof...(Types)>::Print(tuple);
    std::cout << std::endl;
}