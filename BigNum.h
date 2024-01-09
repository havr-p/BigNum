#pragma once
// here you can include whatever you want :)
#include <string>
#include <cstdint>
#include <vector>
#include <cctype>
#include <functional>
#include <iostream>
#include <sstream>
#include <cmath>

// if you do not plan to implement bonus, you can delete those lines
// or just keep them as is and do not define the macro to 1
#define SUPPORT_IFSTREAM 1
#define SUPPORT_ISQRT 0
#define SUPPORT_EVAL 0 // special bonus

class BigInteger;

inline BigInteger operator+(BigInteger lhs, const BigInteger& rhs);

inline BigInteger operator-(BigInteger lhs, const BigInteger& rhs);

inline BigInteger operator*(BigInteger lhs, const BigInteger& rhs);

inline BigInteger operator/(BigInteger lhs, const BigInteger& rhs);

inline BigInteger operator%(BigInteger lhs, const BigInteger& rhs);

inline bool operator==(const BigInteger& lhs, const BigInteger& rhs);

inline bool operator!=(const BigInteger& lhs, const BigInteger& rhs);

inline bool operator<(const BigInteger& lhs, const BigInteger& rhs);

inline bool operator>(const BigInteger& lhs, const BigInteger& rhs);

inline bool operator<=(const BigInteger& lhs, const BigInteger& rhs);

inline bool operator>=(const BigInteger& lhs, const BigInteger& rhs);

static double toDouble(const std::vector<int>& num);

class BigInteger {
public:
    // constructors
    BigInteger() {
        number = { 0 };
    }

    BigInteger(int64_t n) {

        if (n == std::numeric_limits<int64_t>::min()) {
            sign = -1;

            uint64_t positive_n = static_cast<uint64_t>(-(n + 1)) + 1;
            while (positive_n != 0) {
                int digit = static_cast<int>(positive_n % 10);
                number.push_back(digit);
                positive_n /= 10;
            }
        }
        else {
            sign = (n < 0) ? -1 : 1;
            n = std::abs(n);
            if (n == 0) number.push_back(0);
            while (n != 0) {
                int digit = static_cast<int>(n % 10);
                number.push_back(digit);
                n /= 10;
            }
        }
        std::reverse(number.begin(), number.end());
    }

    explicit BigInteger(const std::string& str) {
        std::string s = str;
        if (s.empty()) throw std::invalid_argument("empty string");
        //only sign
        if (s.size() == 1 && !std::isdigit(s[0])) throw std::invalid_argument("received bad formatted string - only sign");
        if (s[0] == '+') {
            sign = 1;
            s.erase(0, 1);
        }
        else if (s[0] == '-') {
            sign = -1;
            s.erase(0, 1);
        }
        else if (!std::isdigit(s[0])) throw std::invalid_argument("received bad formatted string");

        //remove leading zeroes but preserve last one
        while (s[0] == '0') s.erase(0, 1);
        if (s.empty()) {
            number = { 0 };
            sign = 1;
        }
        else {
            for (size_t i = 0; i < s.size(); ++i) {
                if (!isdigit(s[i])) {
                    throw std::invalid_argument("Invalid string for BigInteger - not a digit");
                }
                number.push_back(s[i] - '0');
            }
        }
    }

    // copy
    BigInteger(const BigInteger& other) {
        number = other.number;
        sign = other.sign;
    }

    BigInteger& operator=(const BigInteger& rhs) = default;

    // unary operators
    const BigInteger& operator+() const {
        return *this;
    }

    BigInteger operator-() const {
        BigInteger result = *this;
        result.sign = -this->sign;
        return result;
    }

    // binary arithmetics operators
    BigInteger& operator+=(const BigInteger& rhs) {
        const BigInteger temp = *this + rhs;
        *this = temp;
        return *this;
    }

    BigInteger& operator-=(const BigInteger& rhs) {
        const BigInteger temp = *this - rhs;
        *this = temp;
        return *this;
    }

    BigInteger& operator*=(const BigInteger& rhs) {
        const BigInteger temp = *this * rhs;
        *this = temp;
        return *this;
    }

    BigInteger& operator/=(const BigInteger& rhs) {
        *this = *this / rhs;
        return *this;
    }

    BigInteger& operator%=(const BigInteger& rhs) {
        *this = *this % rhs;
        return *this;
    }


    double sqrt() const {
        if (sign == -1) {
            throw std::runtime_error("invalid argument - negative number.");
        }

        double numAsDouble = toDouble(number);

        return std::sqrt(numAsDouble);
    }

    std::string toString() {
        std::ostringstream stream;
        stream << *this;
        return stream.str();
    }

#if SUPPORT_ISQRT == 1
    BigInteger isqrt() const {
        if (sign < 0) {
            throw std::runtime_error("Square root of a negative number is not real.");
        }

        BigInteger left(0), right(*this), result;
        while (left <= right) {
            BigInteger mid = (left + right) / 2;
            BigInteger midSquared = mid * mid;

            if (midSquared <= *this) {
                result = mid;
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        return result;
    }
#endif
private:
    // here you can add private data and members, but do not add stuff to
    // public interface, also you can declare friends here if you want
    std::vector<int> number;
    int sign = 1;

    friend std::ostream& operator<<(std::ostream& os, const BigInteger& bigInt);

    friend int getSign(const BigInteger& bigInt);

    friend void setSign(BigInteger& bigInt, int sign);

    friend const std::vector<int>& getNumber(const BigInteger& bigInt);

    friend void setNumber(BigInteger& bigInt, const std::vector<int>& num);

    friend BigInteger abs(const BigInteger& bigInt);

    friend std::vector<int> add(const std::vector<int>& lhs, const std::vector<int>& rhs);

    friend std::vector<int> subtract(const std::vector<int>& lhs, const std::vector<int>& rhs);

    friend inline BigInteger operator/(BigInteger lhs, const BigInteger& rhs);
};

std::vector<int> add(const std::vector<int>& lhs, const std::vector<int>& rhs);

std::vector<int> subtract(const std::vector<int>& lhs, const std::vector<int>& rhs);

//std::vector<int> karatsubaMultiplication(const std::vector<int>& x, const std::vector<int>& y);
std::vector<int> karatsuba_mul(const std::vector<int>& x, const std::vector<int>& y);

std::vector<int> naive_mul(const std::vector<int>& x, const std::vector<int>& y);

static double toDouble(const std::vector<int>& num) {
    double numAsDouble = 0;
    for (size_t i = 0; i < num.size(); ++i) {
        numAsDouble += num[i] * std::pow(10, num.size() - i - 1);
    }

    // Check for overflow
    if (!std::isfinite(numAsDouble)) {
        throw std::runtime_error("Number is too large");
    }
    return numAsDouble;
}

static double toDouble(const BigInteger& bi) {
    return toDouble(getNumber(bi));
}


inline BigInteger operator+(BigInteger lhs, const BigInteger& rhs) {
    BigInteger addition = BigInteger();
    if (getSign(lhs) == getSign(rhs)) {
        setNumber(addition, add(getNumber(lhs), getNumber(rhs)));
        setSign(addition, getSign(lhs));
    }
    else {
        if (abs(lhs) == abs(rhs)) return BigInteger(0);

        if (abs(lhs) > abs(rhs)) {
            setNumber(addition, subtract(getNumber(lhs), getNumber(rhs)));
            setSign(addition, getSign(lhs));
        }
        else {
            setNumber(addition, subtract(getNumber(rhs), getNumber(lhs)));
            setSign(addition, getSign(rhs));
        }
    }

    return addition;
}

inline BigInteger operator-(BigInteger lhs, const BigInteger& rhs) {
    BigInteger temp(rhs);
    setSign(temp, -getSign(rhs));
    return temp + lhs;
}

inline BigInteger operator*(BigInteger lhs, const BigInteger& rhs) {
    BigInteger result;
    auto ln = getNumber(lhs);
    auto rn = getNumber(rhs);
    auto rs = getSign(rhs);
    auto ls = getSign(lhs);
    auto zero = std::vector<int>{ 0 };
    auto one = std::vector<int>{ 1 };
    if ((ln == zero) || (rn == zero)) return BigInteger(0);
    if (ln == one) return BigInteger(rhs);
    if (rn == one) return BigInteger(lhs);
    auto resultNum = naive_mul(ln, rn);

    setNumber(result, resultNum);
    setSign(result, rs * ls);

    return result;
}


inline BigInteger operator/(BigInteger lhs, const BigInteger& rhs) {
    auto b = rhs;
    if (getNumber(rhs) == std::vector<int>{0}) {
        throw std::runtime_error("Division by zero");
    }

    BigInteger quotient(0);
    BigInteger remainder(0);
    int quotientSign = getSign(lhs) * getSign(b);

    setSign(lhs, 1);
    setSign(b, 1);

    for (int digit : getNumber(lhs)) {
        remainder = remainder * 10 + BigInteger(digit);
        int count = 0;
        while (remainder >= b) {
            remainder -= b;
            count++;
        }
        auto qNum = getNumber(quotient);
        qNum.push_back(count);
        setNumber(quotient, qNum);
    }


    auto quotientNum = getNumber(quotient);
    auto it = std::find_if(quotientNum.begin(), quotientNum.end(), [](int x) { return x != 0; });
    quotientNum.erase(quotientNum.begin(), it);
    if (quotientNum.empty()) {
        quotientNum.push_back(0);
    }
    setNumber(quotient, quotientNum);
    setSign(quotient, quotientSign);

    return quotient;
}

inline BigInteger operator%(BigInteger lhs, const BigInteger& rhs) {
    auto a = abs(lhs);
    auto b = abs(rhs);
    BigInteger quotient = a / b;
    BigInteger product = quotient * b;
    auto res = a - product;
    return res;
}

// alternatively you can implement
// std::strong_ordering operator<=>(const BigInteger& lhs, const BigInteger& rhs);
// idea is, that all comparison should work, it is not important how you do it
inline bool operator==(const BigInteger& lhs, const BigInteger& rhs) {
    return getSign(lhs) == getSign(rhs) && getNumber(lhs) == getNumber(rhs);
}

inline bool operator!=(const BigInteger& lhs, const BigInteger& rhs) {
    return !(lhs == rhs);
}

inline bool operator<(const BigInteger& lhs, const BigInteger& rhs) {
    if (getSign(lhs) != getSign(rhs)) {
        return getSign(lhs) < getSign(rhs);
    }
    const auto& ln = getNumber(lhs);
    const auto& rn = getNumber(rhs);
    if (ln.size() != rn.size()) {
        return getSign(lhs) == 1 ? ln.size() < rn.size() : ln.size() > rn.size();
    }
    return getSign(lhs) == 1 ? ln < rn : ln > rn;
}

inline bool operator>(const BigInteger& lhs, const BigInteger& rhs) {
    auto ln = getNumber(lhs);
    auto rn = getNumber(rhs);
    auto rs = getSign(rhs);
    auto ls = getSign(lhs);
    if (ls != rs) {
        if (ls == -1) return false;
        else if (ls == 1) return true;
    }
    else if (ls == 1) // both +ve
    {
        if (ln.size() > rn.size())
            return true;
        if (ln.size() < rn.size())
            return false;
        return ln > rn;
    }
    else // both -ve
    {
        if (ln.size() > rn.size())
            return false;
        if (ln.size() < rn.size())
            return true;
        return !(ln > rn);
    }
    return false;
}

inline bool operator<=(const BigInteger& lhs, const BigInteger& rhs) {
    return lhs < rhs || lhs == rhs;
}

inline bool operator>=(const BigInteger& lhs, const BigInteger& rhs) {
    return lhs > rhs || lhs == rhs;
}

inline std::ostream& operator<<(std::ostream& lhs, const BigInteger& rhs) {
    if (rhs.sign == -1 && !(rhs.number.size() == 1 && rhs.number[0] == 0)) lhs << '-';
    for (int digit : rhs.number) {
        lhs << digit;
    }
    return lhs;
}

#if SUPPORT_IFSTREAM == 1

// this should behave exactly the same as reading int with respect to
// whitespace, consumed characters etc...
inline std::istream& operator>>(std::istream& lhs, BigInteger& rhs) {
    std::string input;
    lhs >> input;

    if (input.empty() || (input.size() == 1 && input[0] == '-')) {
        lhs.setstate(std::ios::failbit);
        return lhs;
    }

    try {
        rhs = BigInteger(input);
    }
    catch (const std::invalid_argument&) {
        lhs.setstate(std::ios::failbit);
    }

    return lhs;
} // bonus
#endif

BigInteger gcd(const BigInteger& a, const BigInteger& b);

uint64_t gcd64(const uint64_t& a, const uint64_t& b);

void normalizeInner(BigInteger& numerator, BigInteger& denominator);

class BigRational;

inline BigRational operator+(BigRational lhs, const BigRational& rhs);

inline BigRational operator-(BigRational lhs, const BigRational& rhs);

inline BigRational operator*(BigRational lhs, const BigRational& rhs);

inline BigRational operator/(BigRational lhs, const BigRational& rhs);


class BigRational {
public:
    // constructors
    BigRational() {
        numerator = BigInteger(0);
        denominator = BigInteger(1);
    }

    BigRational(int64_t a, int64_t b) {
        if (b == 0) throw std::runtime_error("invalid argument - zero denominator.");
        auto num = std::make_unsigned_t<int64_t>(a);
        auto denom = std::make_unsigned_t<int64_t>(b);
        auto d = gcd64(num, denom);
        numerator = BigInteger(static_cast<int64_t>(a / d));
        denominator = BigInteger(static_cast<int64_t>(b / d));
        //normalizeInner(numerator, denominator);
    }
    //    if (b[0] == '0' && b.size() == 1) throw std::runtime_error("invalid argument - zero denominator.");
    //    numerator = BigInteger(a);
    //    denominator = BigInteger(b);
    //    normalizeInner(numerator, denominator);

    BigRational(const std::string& a, const std::string& b) {
        if (b[0] == '0' && b.size() == 1) throw std::runtime_error("invalid argument - zero denominator.");
        //only zeroes
        if (std::all_of(b.begin(), b.end(), [](char c) { return c == '0'; }))
            throw std::runtime_error("invalid argument - zero denominator.");
        numerator = BigInteger(a);
        denominator = BigInteger(b);
        normalizeInner(numerator, denominator);
    }

    // copy
    BigRational(const BigRational& other) {
        numerator = other.numerator;
        denominator = other.denominator;
        normalizeInner(numerator, denominator);
    }

    BigRational& operator=(const BigRational& rhs) {
        numerator = rhs.numerator;
        denominator = rhs.denominator;
        normalizeInner(numerator, denominator);
        return *this;
    }

    // unary operators
    const BigRational& operator+() const {
        return *this;
    }

    BigRational operator-() const {
        BigRational result = *this;
        setSign(result.numerator, -getSign(result.numerator));
        return result;
    }

    // binary arithmetics operators
    BigRational& operator+=(const BigRational& rhs) {
        *this = *this + rhs;
        return *this;
    }

    BigRational& operator-=(const BigRational& rhs) {
        *this = *this - rhs;
        return *this;
    }

    BigRational& operator*=(const BigRational& rhs) {
        *this = *this * rhs;
        return *this;
    }

    BigRational& operator/=(const BigRational& rhs) {
        *this = *this / rhs;
        return *this;
    }

    double sqrt() const {
        int sign = getSign(numerator) * getSign(denominator);
        if (sign < 0) throw std::invalid_argument("invalid argument - negative number.");
        return std::sqrt(toDouble(numerator) / toDouble(denominator));
    }

#if SUPPORT_ISQRT == 1
    BigInteger isqrt() const;
#endif
private:
    // here you can add private data and members, but do not add stuff to
    // public interface, also you can declare friends here if you want
    BigInteger numerator = BigInteger(0);
    BigInteger denominator = BigInteger(0);

    friend const BigInteger& getNumerator(const BigRational& br);

    friend void setNumerator(BigRational& br, const BigInteger& bi);

    friend const BigInteger& getDenominator(const BigRational& br);

    friend void setDenominator(BigRational& br, const BigInteger& bi);

    friend BigRational createBigRational(const BigInteger& a, const BigInteger& b);

    friend BigInteger gcd(const BigInteger& a, const BigInteger& b);

    friend int getSign(const BigInteger& bigInt);

    friend inline std::ostream& operator<<(std::ostream& out, const BigRational& rhs);

};

int getSign(const BigInteger& bigInt);

BigRational createBigRational(const BigInteger& a, const BigInteger& b);

BigRational normalize(BigInteger numerator, BigInteger denominator);

inline BigRational operator+(BigRational lhs, const BigRational& rhs) {
    BigInteger d1 = getDenominator(lhs), d2 = getDenominator(rhs);
    BigInteger n1 = getNumerator(lhs), n2 = getNumerator(rhs);
    BigInteger commonDenominator;
    if (d1 != d2) {
        commonDenominator = d1 * d2;
        BigInteger lhsNumerator = n1 * d2;
        BigInteger rhsNumerator = n2 * d1;
        return normalize(lhsNumerator + rhsNumerator, commonDenominator);
    }
    else {
        commonDenominator = d1;
        return normalize(n1 + n2, commonDenominator);
    }
}

inline BigRational operator-(BigRational lhs, const BigRational& rhs) {
    BigInteger d1 = getDenominator(lhs), d2 = getDenominator(rhs);
    BigInteger n1 = getNumerator(lhs), n2 = getNumerator(rhs);
    BigInteger commonDenominator;
    if (d1 != d2) {
        commonDenominator = d1 * d2;
        BigInteger lhsNumerator = n1 * d2;
        BigInteger rhsNumerator = n2 * d1;
        return normalize(lhsNumerator - rhsNumerator, commonDenominator);
    }
    else {
        commonDenominator = d1;
        return normalize(n1 - n2, commonDenominator);
    }
}

inline BigRational operator*(BigRational lhs, const BigRational& rhs) {
    BigInteger commonDenominator = getDenominator(lhs) * getDenominator(rhs);
    auto num = getNumerator(lhs) * getNumerator(rhs);
    //int sign = getSign(getNumerator(lhs)) * getSign(getNumerator(rhs))
    return normalize(num, commonDenominator);
}

inline BigRational operator/(BigRational lhs, const BigRational& rhs) {
    return normalize(getNumerator(lhs) * getDenominator(rhs), getNumerator(rhs) * getDenominator(lhs));
}


// alternatively you can implement
// std::strong_ordering operator<=>(const BigRational& lhs, const BigRational& rhs);
// idea is, that all comparison should work, it is not important how you do it
inline bool operator==(const BigRational& lhs, const BigRational& rhs) {
    return (getNumerator(lhs) * getDenominator(rhs)) == (getNumerator(rhs) * getDenominator(lhs));
}

inline bool operator!=(const BigRational& lhs, const BigRational& rhs) {
    return (getNumerator(lhs) * getDenominator(rhs)) != (getNumerator(rhs) * getDenominator(lhs));
}

inline bool operator<(const BigRational& lhs, const BigRational& rhs) {
    //BigInteger commonDenominator = getDenominator(lhs) * getDenominator(rhs);
    BigInteger lhsNumerator = getNumerator(lhs) * getDenominator(rhs);
    BigInteger rhsNumerator = getNumerator(rhs) * getDenominator(lhs);
    return lhsNumerator < rhsNumerator;
}

inline bool operator>(const BigRational& lhs, const BigRational& rhs) {
    BigInteger lhsNumerator = getNumerator(lhs) * getDenominator(rhs);
    BigInteger rhsNumerator = getNumerator(rhs) * getDenominator(lhs);
    return lhsNumerator > rhsNumerator;
}

inline bool operator<=(const BigRational& lhs, const BigRational& rhs) {
    return ((lhs == rhs) || (lhs < rhs));
}

inline bool operator>=(const BigRational& lhs, const BigRational& rhs) {
    return ((lhs == rhs) || (lhs > rhs));
}

inline std::ostream& operator<<(std::ostream& out, const BigRational& rhs) {
    if (getSign(getNumerator(rhs)) * getSign(getDenominator(rhs)) < 0) {
        //if not zero
        if (!(getNumber(rhs.numerator).size() == 1 && (getNumber(rhs.numerator)[0] == 0)))
            out << '-';
    }

    // Output the absolute value of the numerator
    out << abs(getNumerator(rhs));

    // Output the denominator only if it's not 1
    if (getDenominator(rhs) != BigInteger(1)) {
        out << '/' << abs(getDenominator(rhs));
    }

    return out;
}

#if SUPPORT_IFSTREAM == 1

// this should behave exactly the same as reading int with respect to
// whitespace, consumed characters etc...
inline std::istream& operator>>(std::istream& lhs, BigRational& rhs) {
    std::string numeratorStr, denominatorStr;
    char delimiter;

    lhs >> numeratorStr;
    if (numeratorStr.empty() || (numeratorStr.size() == 1 && numeratorStr[0] == '-')) {
        lhs.setstate(std::ios::failbit);
        return lhs;
    }

    lhs >> std::ws >> delimiter;
    if (!lhs || delimiter != '/') {
        try {
            BigInteger numerator(numeratorStr);
            rhs = createBigRational(numerator, BigInteger(1));
        }
        catch (const std::invalid_argument&) {
            lhs.setstate(std::ios::failbit);
        }
        return lhs;
    }

    lhs >> denominatorStr;
    if (denominatorStr.empty()) {
        lhs.setstate(std::ios::failbit);
        return lhs;
    }

    try {
        BigInteger numerator(numeratorStr);
        BigInteger denominator(denominatorStr);
        rhs = createBigRational(numerator, denominator);
    }
    catch (const std::invalid_argument&) {
        lhs.setstate(std::ios::failbit);
    }

    return lhs;
} // bonus
#endif

#if SUPPORT_EVAL == 1
inline BigInteger eval(const std::string&);
#endif


std::vector<int> add(const std::vector<int>& lhs, const std::vector<int>& rhs) {
    std::vector<int> result;
    int carry = 0;
    size_t maxLength = std::max(lhs.size(), rhs.size());

    for (size_t i = 0; i < maxLength || carry; ++i) {
        int sum = carry;
        if (i < lhs.size()) sum += lhs[lhs.size() - 1 - i];
        if (i < rhs.size()) sum += rhs[rhs.size() - 1 - i];
        carry = sum / 10;
        sum %= 10;
        result.push_back(sum);
    }

    std::reverse(result.begin(), result.end());
    return result;
}

std::vector<int> subtract(const std::vector<int>& lhs, const std::vector<int>& rhs) {

    auto a = lhs;
    auto b = rhs;

    if (a.size() < b.size() || (a.size() == b.size() && a < b)) {
        std::swap(a, b);
    }


    b.insert(b.begin(), a.size() - b.size(), 0);

    std::vector<int> result;
    int borrow = 0;


    for (int i = static_cast<int>(a.size() - 1); i >= 0; --i) {
        int digitA = a[i];
        int digitB = b[i] + borrow;

        if (digitA < digitB) {
            digitA += 10;
            borrow = 1;
        }
        else {
            borrow = 0;
        }

        result.push_back(digitA - digitB);
    }


    while (!result.empty() && result.back() == 0) {
        result.pop_back();
    }


    if (result.empty()) {
        return { 0 };
    }

    std::reverse(result.begin(), result.end());

    return result;
}


std::vector<int> naive_mul(const std::vector<int>& x, const std::vector<int>& y) {


    int tsize = static_cast<int>(x.size());
    int bsize = static_cast<int>(y.size());

    std::vector<int> pos(static_cast<int>(tsize + bsize), 0);
    for (int i = tsize - 1; i >= 0; i--) {
        for (int j = bsize - 1; j >= 0; j--) {
            int mul = (x[i]) * (y[j]);
            int p1 = i + j, p2 = i + j + 1;
            int sum = mul + pos[p2];
            pos[p1] += sum / 10;
            pos[p2] = sum % 10;
        }
    }
    std::vector<int> res;
    for (int p : pos) if (!(res.size() == 0 && p == 0)) res.push_back(p);

    //std::reverse(res.begin(), res.end());
    return res;

}


std::vector<int> karatsuba_mul(const std::vector<int>& x, const std::vector<int>& y) {
    auto len = x.size();
    if (len < y.size()) {
        return karatsuba_mul(y, x);
    }
    if (len == 0 || y.size() == 0) {
        return std::vector<int>();
    }
    if (len <= 32) {
        return naive_mul(x, y);
    }

    auto half = len / 2;
    auto low1 = std::vector<int>(x.begin(), x.begin() + half);
    auto high1 = std::vector<int>(x.begin() + half, x.end());
    auto low2 = std::vector<int>(y.begin(), y.begin() + std::min(half, y.size()));
    auto high2 = std::vector<int>(y.begin() + std::min(half, y.size()), y.end());

    auto z0 = karatsuba_mul(low1, low2);
    auto z1 = karatsuba_mul(add(low1, high1), add(low2, high2));
    auto z2 = karatsuba_mul(high1, high2);

    // Resize z1 to accommodate subtraction
    z1.resize(z2.size() + half, 0);
    for (size_t i = 0; i < z2.size(); i++) {
        z1[i + half] -= z2[i];
    }
    for (size_t i = 0; i < low1.size(); i++) {
        z1[i] -= z0[i];
    }

    std::vector<int> result(len * 2);
    for (size_t i = 0; i < z0.size(); i++) {
        result[i] += z0[i];
    }
    for (size_t i = half; i < z1.size() + half; i++) {
        result[i] += z1[i - half];
    }
    for (size_t i = 0; i < z2.size(); i++) {
        result[i + len] += z2[i];
    }
    return result;
}


int getSign(const BigInteger& bigInt) {
    return bigInt.sign;
}

void setSign(BigInteger& bigInt, int sign) {
    bigInt.sign = sign;
}


void setNumber(BigInteger& bigInt, const std::vector<int>& num) {
    bigInt.number = num;
}

const std::vector<int>& getNumber(const BigInteger& bigInt) {
    return bigInt.number;
}

BigInteger abs(const BigInteger& bigInt) {
    BigInteger result = BigInteger(bigInt);
    result.sign = 1;
    return result;
}


const BigInteger& getNumerator(const BigRational& br) {
    return br.numerator;
}

void setNumerator(BigRational& br, const BigInteger& bi) {
    br.numerator = bi;
}

const BigInteger& getDenominator(const BigRational& br) {
    return br.denominator;
}

void setDenominator(BigRational& br, const BigInteger& bi) {
    br.numerator = bi;
}

BigRational createBigRational(const BigInteger& a, const BigInteger& b) {
    if (b == BigInteger(0)) {
        throw std::runtime_error("Denominator cannot be zero");
    }
    BigRational br;
    br.numerator = a;
    br.denominator = b;
    return br;
}

BigInteger gcd(const BigInteger& a, const BigInteger& b) {
    if (b == BigInteger(0)) {
        return a;
    }
    else {
        return gcd(b, a % b);
    }
}

uint64_t gcd64(const uint64_t& a, const uint64_t& b) {
    if (b == 0) {
        return a;
    }
    else {
        return gcd64(b, a % b);
    }
}

void normalizeInner(BigInteger& numerator, BigInteger& denominator) {
    int sign = getSign(numerator) * getSign(denominator);
    BigInteger d = gcd(numerator, denominator);
    numerator = numerator / d;
    setSign(numerator, sign);
    denominator = denominator / d;
    setSign(denominator, 1);
}

BigRational normalize(BigInteger numerator, BigInteger denominator) {
    normalizeInner(numerator, denominator);
    return createBigRational(numerator, denominator);
}

BigRational normalize(const BigRational& br) {
    if (getDenominator(br) == BigInteger(0)) {
        throw std::runtime_error("Denominator cannot be zero");
    }
    auto numerator = getNumerator(br);
    auto denominator = getDenominator(br);
    // Normalize the sign
    int sign = 1;
    if (numerator < BigInteger(0)) {
        sign = -1;

    }
    if (denominator < BigInteger(0)) {
        sign *= -1;

    }

    BigInteger d = gcd(numerator, denominator);

    numerator = numerator / d;
    setSign(numerator, sign);
    denominator = denominator / d;
    setSign(denominator, 1);
    return createBigRational(numerator, denominator);
}

