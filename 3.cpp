#include <iostream>
#include <numeric>
#include <string>

class Rational {
private:
    int numerator;
    int denominator;

    void normalize() {
        if (denominator == 0) {
            throw std::invalid_argument("Denominator cannot be zero");
        }

        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }

        int gcd = std::gcd(std::abs(numerator), denominator);
        numerator /= gcd;
        denominator /= gcd;
    }

public:
    Rational(int num = 0, int den = 1) : numerator(num), denominator(den) {
        normalize();
    }

    operator double() const {
        return static_cast<double>(numerator) / denominator;
    }

    Rational& operator+=(const Rational& other) {
        numerator = numerator * other.denominator + other.numerator * denominator;
        denominator *= other.denominator;
        normalize();
        return *this;
    }

    Rational& operator-=(const Rational& other) {
        numerator = numerator * other.denominator - other.numerator * denominator;
        denominator *= other.denominator;
        normalize();
        return *this;
    }

    Rational& operator*=(const Rational& other) {
        numerator *= other.numerator;
        denominator *= other.denominator;
        normalize();
        return *this;
    }

    Rational& operator/=(const Rational& other) {
        if (other.numerator == 0) {
            throw std::invalid_argument("Division by zero");
        }
        numerator *= other.denominator;
        denominator *= other.numerator;
        normalize();
        return *this;
    }

    Rational& operator++() {
        numerator += denominator;
        normalize();
        return *this;
    }

    Rational& operator--() {
        numerator -= denominator;
        normalize();
        return *this;
    }

    Rational operator++(int) {
        Rational temp = *this;
        ++(*this);
        return temp;
    }

    Rational operator--(int) {
        Rational temp = *this;
        --(*this);
        return temp;
    }

    friend Rational operator+(Rational lhs, const Rational& rhs) {
        lhs += rhs;
        return lhs;
    }

    friend Rational operator-(Rational lhs, const Rational& rhs) {
        lhs -= rhs;
        return lhs;
    }

    friend Rational operator*(Rational lhs, const Rational& rhs) {
        lhs *= rhs;
        return lhs;
    }

    friend Rational operator/(Rational lhs, const Rational& rhs) {
        lhs /= rhs;
        return lhs;
    }

    friend bool operator==(const Rational& lhs, const Rational& rhs) {
        return lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator;
    }

    friend bool operator!=(const Rational& lhs, const Rational& rhs) {
        return !(lhs == rhs);
    }

    friend bool operator<(const Rational& lhs, const Rational& rhs) {
        return lhs.numerator * rhs.denominator < rhs.numerator * lhs.denominator;
    }

    friend bool operator>(const Rational& lhs, const Rational& rhs) {
        return rhs < lhs;
    }

    friend bool operator<=(const Rational& lhs, const Rational& rhs) {
        return !(rhs < lhs);
    }

    friend bool operator>=(const Rational& lhs, const Rational& rhs) {
        return !(lhs < rhs);
    }

    friend std::ostream& operator<<(std::ostream& os, const Rational& r) {
        if (r.denominator == 1) {
            os << r.numerator;
        } else {
            os << r.numerator << "/" << r.denominator;
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Rational& r) {
        std::string input;
        is >> input;

        size_t slash_pos = input.find('/');
        if (slash_pos != std::string::npos) {
            r.numerator = std::stoi(input.substr(0, slash_pos));
            r.denominator = std::stoi(input.substr(slash_pos + 1));
        } else {
            r.numerator = std::stoi(input);
            r.denominator = 1;
        }

        r.normalize();
        return is;
    }

    int getNumerator() const { return numerator; }
    int getDenominator() const { return denominator; }
};
