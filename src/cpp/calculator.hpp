#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <cstdint>

class Calculator {
public:
    // Arithmetic operations
    static int64_t add(int64_t a, int64_t b);
    static int64_t sub(int64_t a, int64_t b);
    static int64_t mul(int64_t a, int64_t b);
    static int64_t div(int64_t a, int64_t b);

    // Advanced operations
    static double pow(double base, double exponent);
    static double log(double value, double base = 10.0);
    static double root(double value, double n);

private:
    // Helpers for i386
#if defined(__i386__)
    static double software_pow(double base, double exponent);
    static double software_log(double value, double base);
    static double software_root(double value, double n);
#endif
};

#endif // CALCULATOR_H
