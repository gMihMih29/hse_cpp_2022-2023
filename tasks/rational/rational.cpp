#include "rational.h"

#include <cmath>
#include <string>

Rational::Rational() : numer_(0), denom_(1) {
}

Rational::Rational(int value) : numer_(value), denom_(1) {  // NOLINT
}

Rational::Rational(int numer, int denom) {
    denom_ = 1;
    SetNumerator(numer);
    SetDenominator(denom);
}

int Rational::GetNumerator() const {
    return numer_;
}

int Rational::GetDenominator() const {
    return denom_;
}

void Rational::SetNumerator(int value) {
    int gcd = std::gcd(value, denom_);
    numer_ = value / gcd;
    denom_ /= gcd;
}

void Rational::SetDenominator(int value) {
    if (value == 0) {
        throw RationalDivisionByZero();
    }
    int gcd = std::gcd(numer_, value);
    numer_ /= (value > 0 ? gcd : -gcd);
    denom_ = std::abs(value) / gcd;
}

Rational& operator+=(Rational& lhs, const Rational& rhs) {
    int64_t top = static_cast<int64_t>(lhs.GetNumerator()) * rhs.GetDenominator() +
                  static_cast<int64_t>(rhs.GetNumerator()) * lhs.GetDenominator();
    int64_t bottom = static_cast<int64_t>(lhs.GetDenominator()) * rhs.GetDenominator();
    int64_t gcd = std::gcd(top, bottom);
    lhs.SetDenominator(1);
    lhs.SetNumerator(static_cast<int>(top / gcd));
    lhs.SetDenominator(static_cast<int>(bottom / gcd));
    return lhs;
}

Rational& operator*=(Rational& lhs, const Rational& rhs) {
    int64_t top = static_cast<int64_t>(lhs.GetNumerator()) * rhs.GetNumerator();
    int64_t bottom = static_cast<int64_t>(lhs.GetDenominator()) * rhs.GetDenominator();
    int64_t gcd = std::gcd(top, bottom);
    lhs.SetDenominator(1);
    lhs.SetNumerator(static_cast<int>(top / gcd));
    lhs.SetDenominator(static_cast<int>(bottom / gcd));
    return lhs;
}

Rational& operator++(Rational& ratio) {
    ratio.SetNumerator(ratio.numer_ + ratio.denom_);
    return ratio;
}

Rational& operator--(Rational& ratio) {
    ratio.SetNumerator(ratio.numer_ - ratio.denom_);
    return ratio;
}

std::istream& operator>>(std::istream& is, Rational& ratio) {
    const int base = 10;
    std::string input;
    is >> input;
    int top = 0;
    int bottom = 0;
    bool is_top = true;
    bool is_negative = false;
    for (const char& i : input) {
        if (i == '/') {
            is_top = false;
            continue;
        }
        if (i == '+') {
            continue;
        }
        if (i == '-') {
            is_negative = !is_negative;
            continue;
        }
        if (is_top) {
            top = top * base + (i - '0');
        } else {
            bottom = bottom * base + (i - '0');
        }
    }
    if (is_top) {
        bottom = 1;
    }
    ratio.SetDenominator(1);
    ratio.SetNumerator(top * (is_negative ? -1 : 1));
    ratio.SetDenominator(bottom);
    return is;
}

Rational operator+(const Rational& ratio) {
    return Rational(ratio.GetNumerator(), ratio.GetDenominator());
}

Rational operator-(const Rational& ratio) {
    return Rational(-ratio.GetNumerator(), ratio.GetDenominator());
}

Rational& operator-=(Rational& lhs, const Rational& rhs) {
    return lhs += -rhs;
}

Rational& operator/=(Rational& lhs, const Rational& rhs) {
    return lhs *= Rational(rhs.GetDenominator(), rhs.GetNumerator());
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational lhs_copy = lhs;
    return lhs_copy += rhs;
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    Rational lhs_copy = lhs;
    return lhs_copy -= rhs;
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    Rational lhs_copy = lhs;
    return lhs_copy *= rhs;
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    Rational lhs_copy = lhs;
    return lhs_copy /= rhs;
}

Rational operator++(Rational& ratio, int) {
    Rational ans = ratio;
    ++ratio;
    return ans;
}

Rational operator--(Rational& ratio, int) {
    Rational ans = ratio;
    --ratio;
    return ans;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    return (lhs - rhs).GetNumerator() < 0;
}

bool operator>(const Rational& lhs, const Rational& rhs) {
    return rhs < lhs;
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return lhs < rhs || lhs == rhs;
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    return lhs > rhs || lhs == rhs;
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    return lhs.GetNumerator() == rhs.GetNumerator() && lhs.GetDenominator() == rhs.GetDenominator();
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Rational& ratio) {
    if (ratio.GetDenominator() == 1) {
        return os << ratio.GetNumerator();
    }
    return os << ratio.GetNumerator() << '/' << ratio.GetDenominator();
}