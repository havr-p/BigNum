#pragma once
// here you can include whatever you want :)
#include <string>
#include <stdint.h>
#include <vector>
#include <ctype.h>
#include <functional>
#include <iostream>

// if you do not plan to implement bonus, you can delete those lines
// or just keep them as is and do not define the macro to 1
#define SUPPORT_IFSTREAM 0
#define SUPPORT_ISQRT 0
#define SUPPORT_EVAL 0 // special bonus
class BigInteger;
inline BigInteger operator+(BigInteger lhs, const BigInteger& rhs);
inline BigInteger operator-(BigInteger lhs, const BigInteger& rhs);
inline BigInteger operator*(BigInteger lhs, const BigInteger& rhs);
inline BigInteger operator/(BigInteger lhs, const BigInteger& rhs);
inline BigInteger operator%(BigInteger lhs, const BigInteger& rhs);

// alternatively you can implement 
// std::strong_ordering operator<=>(const BigInteger& lhs, const BigInteger& rhs);
// idea is, that all comparison should work, it is not important how you do it
inline bool operator==(const BigInteger& lhs, const BigInteger& rhs);
inline bool operator!=(const BigInteger& lhs, const BigInteger& rhs);
inline bool operator<(const BigInteger& lhs, const BigInteger& rhs);
inline bool operator>(const BigInteger& lhs, const BigInteger& rhs);
inline bool operator<=(const BigInteger& lhs, const BigInteger& rhs);
inline bool operator>=(const BigInteger& lhs, const BigInteger& rhs);

class BigInteger
{
public:
	// constructors
	BigInteger() {
		number = { 0 };
	}
	BigInteger(int64_t n) {
		sign = (n < 0) ? -1 : 1;
		n = std::abs(n);
		if (n == 0) number.push_back(0);
		while (n != 0)
		{
			number.push_back(n % 10);
			n /= 10;
		}
		std::reverse(number.begin(), number.end());
	}
	explicit BigInteger(const std::string& str) {
		std::string s = str;
		if (s.empty()) throw std::invalid_argument("empty string");
		//only sign
		if (s.size() == 1 && s[0] > 'a') throw std::invalid_argument("received bad formatted string - only sign");
		if (s[0] == '+') {
			sign = 1;
			s.erase(0, 1);
		}
		else if (s[0] == '-') {
			sign = -1;
			s.erase(0, 1);
		}
		else if (s[0] != '0') throw std::invalid_argument("received bad formatted string");

		//remove leading zeroes but preserve last one
		while (s[0] == '0') s.erase(0, 1);
		if (s.empty()) {
			number = { 0 };
			sign = 1;
		}
		else {
			std::cout << s << std::endl;
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

		double numAsDouble = 0;
		for (size_t i = 0; i < number.size(); ++i) {
			numAsDouble += number[i] * std::pow(10, i);
		}

		// Check for overflow
		if (!std::isfinite(numAsDouble)) {
			throw std::runtime_error("Number is too large to compute its square root as a double.");
		}

		return std::sqrt(numAsDouble);
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
	friend bool isdigit(char ch);
	friend int getSign(const BigInteger& bigInt);
	friend void setSign(BigInteger& bigInt, int sign);
	friend const std::vector<int>& getNumber(const BigInteger& bigInt);
	friend void setNumber(BigInteger& bigInt, const std::vector<int>& num);
	friend BigInteger abs(const BigInteger& bigInt);
	friend std::vector<int> add(const std::vector<int>& lhs, const std::vector<int>& rhs);
	friend std::vector<int> subtract(const std::vector<int>& lhs, const std::vector<int>& rhs);
};
std::vector<int> add(const std::vector<int>& lhs, const std::vector<int>& rhs);
std::vector<int> subtract(const std::vector<int>& lhs, const std::vector<int>& rhs);

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
	std::vector<int> resultNum(ln.size() + rn.size(), 0);
	for (size_t i = 0; i < ln.size(); ++i) {
		int carry = 0;
		for (size_t j = 0; j < rn.size() || carry; ++j) {
			int rhs_digit = j < rn.size() ? rn[j] : 0;
			int sum = resultNum[i + j] + ln[i] * rhs_digit + carry;
			resultNum[i + j] = sum % 10;
			carry = sum / 10;
		}
	}

	while (!resultNum.empty() && resultNum.back() == 0) {
		resultNum.pop_back();
	}

	if (resultNum.empty()) {
		resultNum.push_back(0);
	}

	setNumber(result, resultNum);
	setSign(result, rs * ls);

	return result;
}
inline BigInteger operator/(BigInteger lhs, const BigInteger& rhs) {
	if (getNumber(rhs) == std::vector<int>{0}) {
		throw std::runtime_error("Division by zero");
	}

	BigInteger result;
	setNumber(result, std::vector<int>());
	setSign(result, getSign(lhs) * getSign(rhs));

	BigInteger current;
	setSign(current, 1);
	auto currentNum = getNumber(current);
	auto resultNum = getNumber(result);
	auto& lhsNum = getNumber(lhs);

	for (auto i = lhsNum.size() - 1; i >= 0; i--) {
		currentNum.insert(currentNum.begin(), lhsNum[i]);
		while (!currentNum.empty() && currentNum.back() == 0) {
			currentNum.pop_back();
		}
		int count = 0;
		while (current >= rhs) {
			current -= rhs;
			count++;
		}
		resultNum.insert(resultNum.begin(), count);
	}

	while (!resultNum.empty() && resultNum.back() == 0) {
		resultNum.pop_back();
	}
	if (resultNum.empty()) {
		resultNum.push_back(0);
	}
	std::reverse(resultNum.begin(), resultNum.end());
	return result;
}
inline BigInteger operator%(BigInteger lhs, const BigInteger& rhs) {
	BigInteger quotient = lhs / rhs;
	BigInteger product = quotient * rhs;
	return lhs - product;
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
	if (rhs.sign == -1)  lhs << '-';
	for (int digit : rhs.number) {
		lhs << digit;
	}
	return lhs;
}

#if SUPPORT_IFSTREAM == 1
// this should behave exactly the same as reading int with respect to 
// whitespace, consumed characters etc...
inline std::istream& operator>>(std::istream& lhs, BigInteger& rhs); // bonus
#endif


class BigRational
{
public:
	// constructors
	BigRational();
	BigRational(int64_t a, int64_t b);
	BigRational(const std::string& a, const std::string& b);
	// copy
	BigRational(const BigRational& other);
	BigRational& operator=(const BigRational& rhs);
	// unary operators
	const BigRational& operator+() const;
	BigRational operator-() const;
	// binary arithmetics operators
	BigRational& operator+=(const BigRational& rhs);
	BigRational& operator-=(const BigRational& rhs);
	BigRational& operator*=(const BigRational& rhs);
	BigRational& operator/=(const BigRational& rhs);

	double sqrt() const;
#if SUPPORT_ISQRT == 1
	BigInteger isqrt() const;
#endif
private:
	// here you can add private data and members, but do not add stuff to 
	// public interface, also you can declare friends here if you want

};

inline BigRational operator+(BigRational lhs, const BigRational& rhs);
inline BigRational operator-(BigRational lhs, const BigRational& rhs);
inline BigRational operator*(BigRational lhs, const BigRational& rhs);
inline BigRational operator/(BigRational lhs, const BigRational& rhs);

// alternatively you can implement 
// std::strong_ordering operator<=>(const BigRational& lhs, const BigRational& rhs);
// idea is, that all comparison should work, it is not important how you do it
inline bool operator==(const BigRational& lhs, const BigRational& rhs);
inline bool operator!=(const BigRational& lhs, const BigRational& rhs);
inline bool operator<(const BigRational& lhs, const BigRational& rhs);
inline bool operator>(const BigRational& lhs, const BigRational& rhs);
inline bool operator<=(const BigRational& lhs, const BigRational& rhs);
inline bool operator>=(const BigRational& lhs, const BigRational& rhs);

inline std::ostream& operator<<(std::ostream& lhs, const BigRational& rhs);

#if SUPPORT_IFSTREAM == 1
// this should behave exactly the same as reading int with respect to 
// whitespace, consumed characters etc...
inline std::istream& operator>>(std::istream& lhs, BigRational& rhs); // bonus
#endif

#if SUPPORT_EVAL == 1
inline BigInteger eval(const std::string&);
#endif

std::vector<int> add(const std::vector<int>& lhs, const std::vector<int>& rhs) {
	std::vector<int> result;
	int carry = 0;
	size_t n = std::max(lhs.size(), rhs.size());

	for (size_t i = 0; i < n || carry; ++i) {
		int lhs_digit = i < lhs.size() ? lhs[i] : 0;
		int rhs_digit = i < rhs.size() ? rhs[i] : 0;
		int sum = lhs_digit + rhs_digit + carry;
		result.push_back(sum % 10);
		carry = sum / 10;
}

	std::reverse(result.begin(), result.end());
	return result;
}

std::vector<int> subtract(const std::vector<int>& lhs, const std::vector<int>& rhs) {
	std::vector<int> result;
	int borrow = 0;
	size_t n = lhs.size();

	for (size_t i = 0; i < n; ++i) {
		int lhs_digit = i < lhs.size() ? lhs[i] : 0;
		int rhs_digit = i < rhs.size() ? rhs[i] : 0;
		int diff = lhs_digit - borrow - rhs_digit;
		borrow = 0;
		if (diff < 0) {
			diff += 10;
			borrow = 1;
		}
		result.push_back(diff);
	}

	// Remove leading zeros
	while (!result.empty() && result.back() == 0) {
		result.pop_back();
	}

	// In case the result is zero
	if (result.empty()) {
		result.push_back(0);
	}

	std::reverse(result.begin(), result.end());
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
