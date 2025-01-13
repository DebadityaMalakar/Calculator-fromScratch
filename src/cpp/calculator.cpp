#include "calculator.hpp"
#include <cmath>
#include <stdexcept>

#if defined(__x86_64__)
extern "C" int64_t add_numbers(int64_t a, int64_t b);
extern "C" int64_t sub_numbers(int64_t a, int64_t b);
extern "C" int64_t mul_numbers(int64_t a, int64_t b);
extern "C" int64_t div_numbers(int64_t a, int64_t b);
extern "C" double asm_pow(double base, double exponent);
#elif defined(__i386__)
extern "C" void add_numbers(int32_t low1, int32_t high1, int32_t low2, int32_t high2, int32_t* result_low, int32_t* result_high);
extern "C" void sub_numbers(int32_t low1, int32_t high1, int32_t low2, int32_t high2, int32_t* result_low, int32_t* result_high);
extern "C" void mul_numbers(int32_t low1, int32_t high1, int32_t low2, int32_t high2, int32_t* result_low, int32_t* result_high);
extern "C" void div_numbers(int32_t low1, int32_t high1, int32_t low2, int32_t high2, int32_t* result_low, int32_t* result_high);
#endif

// Addition
int64_t Calculator::add(int64_t a, int64_t b) {
#if defined(__x86_64__)
    return add_numbers(a, b);
#elif defined(__i386__)
    int32_t low1 = static_cast<int32_t>(a);
    int32_t high1 = static_cast<int32_t>(a >> 32);
    int32_t low2 = static_cast<int32_t>(b);
    int32_t high2 = static_cast<int32_t>(b >> 32);
    int32_t result_low, result_high;
    add_numbers(low1, high1, low2, high2, &result_low, &result_high);
    return (static_cast<int64_t>(result_high) << 32) | result_low;
#endif
}

// Subtraction
int64_t Calculator::sub(int64_t a, int64_t b) {
#if defined(__x86_64__)
    return sub_numbers(a, b);
#elif defined(__i386__)
    int32_t low1 = static_cast<int32_t>(a);
    int32_t high1 = static_cast<int32_t>(a >> 32);
    int32_t low2 = static_cast<int32_t>(b);
    int32_t high2 = static_cast<int32_t>(b >> 32);
    int32_t result_low, result_high;
    sub_numbers(low1, high1, low2, high2, &result_low, &result_high);
    return (static_cast<int64_t>(result_high) << 32) | result_low;
#endif
}

// Multiplication
int64_t Calculator::mul(int64_t a, int64_t b) {
#if defined(__x86_64__)
    return mul_numbers(a, b);
#elif defined(__i386__)
    int32_t low1 = static_cast<int32_t>(a);
    int32_t high1 = static_cast<int32_t>(a >> 32);
    int32_t low2 = static_cast<int32_t>(b);
    int32_t high2 = static_cast<int32_t>(b >> 32);
    int32_t result_low, result_high;
    mul_numbers(low1, high1, low2, high2, &result_low, &result_high);
    return (static_cast<int64_t>(result_high) << 32) | result_low;
#endif
}

// Division
int64_t Calculator::div(int64_t a, int64_t b) {
    if (b == 0) throw std::invalid_argument("Division by zero");
#if defined(__x86_64__)
    return div_numbers(a, b);
#elif defined(__i386__)
    int32_t low1 = static_cast<int32_t>(a);
    int32_t high1 = static_cast<int32_t>(a >> 32);
    int32_t low2 = static_cast<int32_t>(b);
    int32_t high2 = static_cast<int32_t>(b >> 32);
    int32_t result_low, result_high;
    div_numbers(low1, high1, low2, high2, &result_low, &result_high);
    return (static_cast<int64_t>(result_high) << 32) | result_low;
#endif
}

// Power
double Calculator::pow(double base, double exponent) {
#if defined(__x86_64__)
    return asm_pow(base, exponent);
#elif defined(__i386__)
    return software_pow(base, exponent);
#endif
}

// Logarithm
double Calculator::log(double value, double base) {
    if (value <= 0 || base <= 0 || base == 1) throw std::invalid_argument("Invalid logarithm arguments");
#if defined(__x86_64__)
    return std::log(value) / std::log(base);
#elif defined(__i386__)
    return software_log(value, base);
#endif
}

// Root
double Calculator::root(double value, double n) {
    if (value < 0 || n <= 0) throw std::invalid_argument("Invalid root arguments");
#if defined(__x86_64__)
    return std::pow(value, 1.0 / n);
#elif defined(__i386__)
    return software_root(value, n);
#endif
}

// Software implementations for i386
#if defined(__i386__)
double Calculator::software_pow(double base, double exponent) {
    return std::exp(exponent * std::log(base));
}

double Calculator::software_log(double value, double base) {
    return std::log(value) / std::log(base);
}

double Calculator::software_root(double value, double n) {
    return std::exp(std::log(value) / n);
}
#endif
