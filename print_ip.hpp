#pragma once
#include <type_traits>

// Вызываем если параметр от short до long long
template <typename T>
static std::enable_if_t<std::is_integral_v<T>, void>
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
static std::enable_if_t<std::is_same_v<T, std::string>, void>
print_ip(T value){
    std::cout << value << std::endl;
}

// Вызываем если параметр std::vector или std::list
template<template <typename> typename Container, typename Type>
static std::enable_if_t<std::is_same_v<Container<Type>, std::vector<Type>>, void>
print_ip(Container<Type>){
    std::cout << "test" << std::endl;
}